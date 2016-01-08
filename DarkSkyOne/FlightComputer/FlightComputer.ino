#include <Scheduler.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <TinyGPS++.h>
#include <QueueList.h>
#include <rtc_clock.h>
#include <ComUDP.h>
#include <ComTCP.h>
#include <ComStack.h>
#include <ComNetwork.h>
#include <ComDataLink.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_ADXL345_U.h>

#include "FlightUser.h";
#include "GPSTask.h";
#include "GY80Task.h";
#include "LogUtils.h";

// Global variables
int led = 13;
const int chipSelect = 4;

static FlightUser *user_g;

//The setup function is called once at startup of the sketch
void setup()
{
	// Initialize Watchdog

	// You have to edit the variants.cpp file in the Arduino core and comment the line "WDT_disable(WDT);"
	// inside the init function. Else it's not possible to set WDT_Enable again.
    // #define __WDP_MS 2048
	// WDT_Enable(WDT, 0x2000 | __WDP_MS | (__WDP_MS << 16));

	// Initialize Log class
	LogUtils::instance()->setLogLevel(LogUtils::information);
	LogUtils::instance()->logTrace(LogUtils::information, "Booting DarkSky One ....");

	// Initialize SD card
	LogUtils::instance()->logTrace(LogUtils::information, "Initializing SD card...");

	// make sure that the default chip select pin is set to
	// output, even if you don't use it:
	pinMode(10, OUTPUT);

	// see if the card is present and can be initialized:
	if (!SD.begin(chipSelect)) {
		LogUtils::instance()->logTrace(LogUtils::error, "Card failed, or not present");
		// don't do anything more:
		return;
	}
	LogUtils::instance()->logTrace(LogUtils::information, "card initialized");

	// Initialize Heart-Beat LED
	pinMode(led, OUTPUT);

	// Initialize FlightUser Monitor Task
	user_g = new FlightUser(GY80Task::instance()->getGY80Task(), GPSTask::instance()->getGPS());
	user_g->setup();

	// Initialize Scheduler
	Scheduler.startLoop(heartBeat);
	Scheduler.startLoop(procLogs);
	Scheduler.startLoop(procUser);
	Scheduler.startLoop(readGPS);
	Scheduler.startLoop(readGY80);

	LogUtils::instance()->logTrace(LogUtils::information, "Booting DarkSky One done!");
}

// Heart-Beat Scheduler loop
void heartBeat() {
	digitalWrite(led, HIGH);
	delay(300);
	digitalWrite(led, LOW);
	delay(300);
}

// Log processor Scheduler loop
void procLogs() {
	LogUtils::instance()->processLogs();

	delay(30);
	yield();
}

// FlightUser Monitor Scheduler loop
void procUser() {
	user_g->loop();

	delay(30);
	yield();
}

// GPS Scheduler loop
void readGPS() {
	GPSTask::instance()->handleGPS();

	delay(20);
	yield();

}

// GY80 Sensor Scheduler loop
void readGY80() {
	GY80Task::instance()->handleGY80();

	delay(20);
	yield();
}

// The loop function is called in an endless loop
void loop()
{
	// delay and processing for other Scheduler tasks
	yield();
	delay(100);

	// Reset Watchdog
	// WDT_Restart(WDT);
}
