/*
DarkSkyOne Board Computer main unit.
Copyright (C) 2014 Sascha Nussbaumer
All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

// Do not remove the include below
#include "DarkSkyOne.h"
#include "SCoop.h"
#include "LogUtils.h"
#include "Wdt.h"
#include "SPI.h"
#include "SD.h"
#include "GY80.h"
#include "GY80Task.h"
#include "Wire.h"
#include "FlightUser.h"
#include "GPSTask.h"

// Global variables
int led = 13;
const int chipSelect = 4;

static FlightUser *user_g;

defineTask(LogTask)

// LogTask Thread
void LogTask::setup()
{
}

void LogTask::loop()
{
	LogUtils::instance()->processLogs();

	mySCoop.sleep(10);
}

defineTask(HeartBeatTask)

// HeartBeat Thread
void HeartBeatTask::setup()
{
	LogUtils::instance()->logTrace(LogUtils::trace3, "Enter HeartBeatTask::setup()");

	pinMode(led, OUTPUT);

	LogUtils::instance()->logTrace(LogUtils::trace3, "Exit HeartBeatTask::setup()");
}

void HeartBeatTask::loop()
{
	LogUtils::instance()->logTrace(LogUtils::trace3, "Enter HeartBeatTask::loop()");

	digitalWrite(led, HIGH);
	mySCoop.sleep(500);
	digitalWrite(led, LOW);
	mySCoop.sleep(500);

	LogUtils::instance()->logTrace(LogUtils::trace3, "Exit HeartBeatTask::loop()");
}

defineTask(MonitorTask)

void MonitorTask::setup()
{
	user_g = new FlightUser(GY80Task::instance()->getGY80Task(), GPSTask::instance()->getGPS());
	user_g->setup();
}

void MonitorTask::loop()
{
    user_g->loop();

	mySCoop.sleep(10);
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
	LogUtils::instance()->setLogLevel(LogUtils::information);

	LogUtils::instance()->logTrace(LogUtils::information, "Booting DarkSky One ....");

	// Add your initialization code here
	mySCoop.start();

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

	LogUtils::instance()->logTrace(LogUtils::information, "Booting DarkSky One done!");
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here
	yield();

	GPSTask::instance()->handleGPS();

	GY80Task::instance()->handleGY80();

	// Reset Watchdog
	WDT_Restart( WDT );
}
