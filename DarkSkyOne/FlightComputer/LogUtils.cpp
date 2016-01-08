/*
Trace Logging class.
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

#include "LogUtils.h"
#include "Time.h"
#include "rtc_clock.h"
#include "QueueList.h"
#include "SPI.h"
#include "SD.h"

// Global variables
RTC_clock rtc_clock(XTAL);
QueueList <String> queue;

// Initialize static variable of Singleton
LogUtils* LogUtils::_instance = 0;

LogUtils::LogUtils() {

	loglevel = error;

	// Open serial communications and wait for port to open:
	Serial.begin(9600);

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
	if (!queue.isEmpty())
	{
		String StrTime = leadingZero(rtc_clock.get_days()) +"."+ leadingZero(rtc_clock.get_months()) +"."+ leadingZero(rtc_clock.get_years());
		StrTime += "\t" + leadingZero(rtc_clock.get_hours()) +":"+ leadingZero(rtc_clock.get_minutes()) +":"+ leadingZero(rtc_clock.get_seconds());

		String msg = queue.pop ();

		Serial.print(StrTime + "\t" + msg + "\n");

		// open the file. note that only one file can be open at a time,
		// so you have to close this one before opening another.
		File dataFile = SD.open("syslog.txt", FILE_WRITE);

		// if the file is available, write to it:
		if (dataFile) {
			dataFile.println(StrTime + "\t" + msg);
			dataFile.close();
		}
		// if the file isn't open, pop up an error:
		else {
			logTrace(error, "error opening syslog.txt");
		}
	}
}

void LogUtils::logTrace(LogLevel level, const char* msg)
{
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

void LogUtils::logTrace(LogLevel level, const String msg)
{
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
