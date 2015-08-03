/*
GPS handler class.
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

#include "GPSTask.h"
#include "TinyGPS++.h"
#include "LogUtils.h"
#include "SCoop.h"

// Initialize static variable of Singleton
GPSTask* GPSTask::_instance = 0;

GPSTask::GPSTask() {
	nmeaTerm = "";
	nmeaTestMode = false;
	tinyGPS = new TinyGPSPlus();

	Serial2.begin(9600);
}

GPSTask::~GPSTask() {
	// TODO Auto-generated destructor stub
	Serial2.end();
}

void GPSTask::handleGPS()
{
	if (nmeaTestMode)
	{
		// Test NMEA Strings
		const char *gpsStream =
			"$GPRMC,160359.000,V,4711.7778,N,00723.2357,E,,,231114,,,N*73\r\n"
			"$GPGGA,160400.000,4711.7778,N,00723.2357,E,0,00,,458.8,M,48.0,M,,0000*74\r\n"
			"$GPGSA,A,1,,,,,,,,,,,,,,,*1E\r\n"
			"$GPRMC,160400.000,V,4711.7778,N,00723.2357,E,,,231114,,,N*78\r\n"
			"$GPGGA,160401.000,4711.7778,N,00723.2357,E,0,00,,458.8,M,48.0,M,,0000*75\r\n"
			"$GPGSA,A,1,,,,,,,,,,,,,,,*1E\r\n"
			"$GPRMC,160401.000,V,4711.7778,N,00723.2357,E,,,231114,,,N*79\r\n"
			"$GPGGA,160402.000,4711.7778,N,00723.2357,E,0,00,,458.8,M,48.0,M,,0000*76\r\n"
			"$GPGSA,A,1,,,,,,,,,,,,,,,*1E\r\n"
			"$GPRMC,160402.000,V,4711.7778,N,00723.2357,E,,,231114,,,N*7A\r\n"
			"$GPGGA,160403.000,4711.7778,N,00723.2357,E,0,00,,458.8,M,48.0,M,,0000*77\r\n"
			"$GPGSA,A,1,,,,,,,,,,,,,,,*1E\r\n"
			"$GPGSV,3,1,11,09,82,255,,23,62,058,,06,59,268,,10,44,294,*7A\r\n"
			"$GPGSV,3,2,11,20,37,108,20,07,30,169,20,02,27,310,,13,14,235,*7B\r\n"
			"$GPGSV,3,3,11,17,04,221,21,16,04,080,,30,03,187,17*4A\r\n"
			"$GPRMC,160403.000,V,4711.7778,N,00723.2357,E,,,231114,,,N*7B\r\n"
			"$GPGGA,160404.000,4711.7778,N,00723.2357,E,0,00,,458.8,M,48.0,M,,0000*70\r\n"
			"$GPGSA,A,1,,,,,,,,,,,,,,,*1E\r\n"
			"$GPRMC,160404.000,V,4711.7778,N,00723.2357,E,,,231114,,,N*7C\r\n"
			"$GPGGA,160405.000,4711.7782,N,00723.2208,E,1,03,2.9,458.8,M,48.0,M,,0000*58\r\n"
			"$GPGSA,A,2,07,20,09,,,,,,,,,,4.3,2.9,3.2*32\r\n"
			"$GPRMC,160405.000,A,4711.7782,N,00723.2208,E,1.90,80.96,231114,,,A*54\r\n"
			"$GPGGA,160406.000,4711.7671,N,00723.2274,E,1,03,2.9,458.8,M,48.0,M,,0000*5D\r\n"
			"$GPGSA,A,2,07,20,09,,,,,,,,,,4.3,2.9,3.2*32\r\n"
			"$GPRMC,160406.000,A,4711.7671,N,00723.2274,E,1.66,171.85,231114,,,A*65\r\n"
			"$GPGSA,A,2,07,20,09,,,,,,,,,,4.3,2.9,3.2*32\r\n"
			"$GPRMC,160452.000,A,4711.7618,N,00723.2602,E,4.09,28.80,231114,,,A*5A\r\n"
			"$GPGGA,160453.000,4711.7546,N,00723.2499,E,1,03,2.9,458.8,M,48.0,M,,0000*5F\r\n"
			"$GPGSA,A,2,07,20,09,,,,,,,,,,4.3,2.9,3.2*32\r\n"
			"$GPGSV,3,1,11,09,82,255,16,23,62,058,,06,59,268,,10,44,294,*7D\r\n"
			"$GPGSV,3,2,11,20,37,108,21,07,30,169,17,02,27,310,,13,14,235,*7E\r\n"
			"$GPGSV,3,3,11,17,04,221,18,16,04,080,,30,03,187,15*42\r\n";

		// Test Encoding procedure
		while (*gpsStream)
		{
			if (tinyGPS->encode(*gpsStream++))
			{
				yield();
			}
		}
	}
	else
	{
		while (Serial2.available() > 0) {

			int gpsChar = Serial2.read();

			if (gpsChar >= 0 && gpsChar <= 255)
			{
				if (gpsChar > 32)
				{
					nmeaTerm += (char)gpsChar;
				}

				if (tinyGPS->encode((char)gpsChar)) {
					LogUtils::instance()->logTrace(LogUtils::trace1, nmeaTerm);
					nmeaTerm = "";
				}
			}
		}
		if (millis() > 5000 && tinyGPS->charsProcessed() < 10)
		{
			LogUtils::instance()->logTrace(LogUtils::error, "No GPS detected: check wiring.");
		}
	}

	yield();
}
