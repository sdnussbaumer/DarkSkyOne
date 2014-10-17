// Do not remove the include below
#include "DarkSkyOne.h"
#include "SCoop.h"
#include "LogUtils.h"
#include "Wdt.h"
#include "TinyGPS++.h"
#include "Monitor.h"

// Global variables
int led = 13;
LogUtils* logutils;
TinyGPSPlus gpsp_g;
MonitorHandler* monitorhandler;

defineTask(LogTask)

// LogTask Thread
void LogTask::setup()
{
}

void LogTask::loop()
{
	logutils->processLogs();
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

defineTask(MonitorTask)

void MonitorTask::setup()
{
	logutils->logTrace(logutils->trace3, "Enter MonitorTask::setup()");

	monitorhandler = new MonitorHandler();
	monitorhandler->setGPS(gpsp_g);

	logutils->logTrace(logutils->trace3, "Exit MonitorTask::setup()");
}

void MonitorTask::loop()
{
	monitorhandler->handleState();
}

defineTask(GPSReceiverTask)

void GPSReceiverTask::setup()
{
	logutils->logTrace(logutils->trace3, "Enter GPSReceiverTask::setup()");

	Serial2.begin(4800);

	logutils->logTrace(logutils->trace3, "Exit GPSReceiverTask::setup()");
}

void GPSReceiverTask::loop()
{
	while (Serial2.available())
	{
		int data = Serial2.read();
		if (gpsp_g.encode(data))
		{  // new data has arived
			yield();
		}
	}
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

	// Reset Watchdog
	WDT_Restart( WDT );
}
