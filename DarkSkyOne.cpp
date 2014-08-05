// Do not remove the include below
#include "DarkSkyOne.h"
#include "SCoop.h"
#include "LogUtils.h"
#include "Wdt.h"

// Global variables
int led = 13;
LogUtils* logutils;

defineTask(LogTask)

// LogTask Thread
void LogTask::setup()
{
}

void LogTask::loop()
{
	logutils->processLogs();
}

defineTask(XBeeTask)

// XBee Thread
void XBeeTask::setup()
{
	logutils->logTrace(logutils->trace3, "Enter XBeeTask::setup()");

	Serial1.begin(115200);
	while (!Serial1) {
	  ; // wait for serial port to connect. Needed for Leonardo only
	}

	logutils->logTrace(logutils->trace3, "Exit XBeeTask::setup()");
}

void XBeeTask::loop()
{
	logutils->logTrace(logutils->trace3, "Enter XBeeTask::loop()");

	Serial1.println("Dark Sky One");

	sleep(1000);

	logutils->logTrace(logutils->trace3, "Exit XBeeTask::loop()");
}

defineTask(HeartBeatTask)

// HeartBeat Thread
void HeartBeatTask::setup()
{
	logutils->logTrace(logutils->trace3, "Enter HeartBeatTask::setup()");

	pinMode(led, OUTPUT);

	logutils->logTrace(logutils->trace3, "Exit HeartBeatTask::setup()");
}

void HeartBeatTask::loop()
{
	logutils->logTrace(logutils->trace3, "Enter HeartBeatTask::loop()");

	digitalWrite(led, HIGH);
    sleep(500);
	digitalWrite(led, LOW);
	sleep(500);

	logutils->logTrace(logutils->trace3, "Exit HeartBeatTask::loop()");
}

//The setup function is called once at startup of the sketch
void setup()
{
	// Initialize Watchdog

	// You have to edit the variants.cpp file in the Arduino core and comment the line "WDT_disable(WDT);"
	// inside the init function. Else it's not possible to set WDT_Enable again.

	#define __WDP_MS 2048
	WDT_Enable ( WDT, 0x2000 | __WDP_MS | ( __WDP_MS << 16 ) );

	// Initialize Log class
	logutils = new LogUtils;
	logutils->setLogLevel(logutils->trace3);

	logutils->logTrace(logutils->trace3, "Main::setup()");

	// Add your initialization code here
	mySCoop.start();
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here
	yield();

	// Reset Watchdog HW
	WDT_Restart( WDT );
}
