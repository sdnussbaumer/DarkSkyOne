/*
 * LogUtils.cpp
 *
 *  Created on: 23.06.2014
 *      Author: san
 */

#include "LogUtils.h"
#include "Time.h"
#include "rtc_clock.h"
#include "QueueList.h"
#include "SCoop.h"

RTC_clock rtc_clock(XTAL);
LogUtils::LogLevel loglevel;
QueueList <String> queue;

LogUtils::LogUtils() {

	loglevel = error;

	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
	  ; // wait for serial port to connect. Needed for Leonardo only
	}

	// set the printer of the queue.
	queue.setPrinter (Serial);

	rtc_clock.init();

	// Temporary until GPS Time is available
	rtc_clock.set_time(13, 51, 0);
	rtc_clock.set_date(19, 07, 2014);
}

LogUtils::~LogUtils() {
	Serial.end();
}

void LogUtils::setLogLevel(LogLevel level){
	loglevel = level;
}

LogUtils::LogLevel LogUtils::getLogLevel(){

	return loglevel;
}

void LogUtils::processLogs()
{
	// pop all the string messages from the queue.
	while (!queue.isEmpty ()) {

		String StrTime = leadingZero(rtc_clock.get_days()) +"."+ leadingZero(rtc_clock.get_months()) +"."+ leadingZero(rtc_clock.get_years());
		StrTime += "\t" + leadingZero(rtc_clock.get_hours()) +":"+ leadingZero(rtc_clock.get_minutes()) +":"+ leadingZero(rtc_clock.get_seconds());

		Serial.print(StrTime + "\t" + queue.pop () + "\n");
	}
}

void LogUtils::logTrace(LogLevel level, const char* msg)
{
	SCoopATOMIC {
		if (level <= loglevel)
		{
			String levelStr = "";

			switch (level) {
				case error : levelStr = "E"; break;
				case warning : levelStr = "W"; break;
				case information : levelStr = "I"; break;
				case trace1 : levelStr = "1"; break;
				case trace2 : levelStr = "2"; break;
				case trace3 : levelStr = "3"; break;
			}

    		queue.push(levelStr + "\t" + msg);
		}
	}
}

String LogUtils::leadingZero(int nr)
{
	String StrNr = "";
	StrNr = String(nr);
	if (nr < 10 && nr > -10)
	{
		StrNr =  "0" + StrNr;
	}
	return StrNr;
}
