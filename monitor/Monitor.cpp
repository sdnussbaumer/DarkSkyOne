/*
 * Monitor.cpp
 *
 *  Created on: 17.10.2014
 *      Author: san
 */

#include "Monitor.h"
#include "TinyGPS++.h"
#include "LogUtils.h"
#include "SCoop.h"

// Global Variables
MonitorHandler::State state_g;
TinyGPSPlus tinyGPS;
unsigned long timebase_g;
String nmeaTerm = "";
bool nmeaTestMode = true;

MonitorHandler::MonitorHandler() {
	// TODO Auto-generated constructor stub
	state_g = State_main_input;

	Serial1.begin(115200);
	Serial2.begin(4800);

	main_display();
}

MonitorHandler::~MonitorHandler() {
	// TODO Auto-generated destructor stub
	Serial1.end();
	Serial2.end();
}

void MonitorHandler::handleState()
{
	switch (state_g)
	{
	case State_main_display: main_display(); break;
	case State_main_input: main_input(); break;
	case State_inflight_display: inflight_display(); break;
	case State_inflight_input: inflight_input(); break;
	case State_gps_display: gps_display(); break;
	case State_gps_input: gps_input(); break;
	}
}

void MonitorHandler::handleGPS()
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
		SCoopATOMIC {
			while (*gpsStream)
			{
				tinyGPS.encode(*gpsStream++);
			}
		}
	}
	else
	{
		SCoopATOMIC {
			while (Serial2.available() > 0) {

				int gpsChar = Serial2.read();

				if (gpsChar >= 0 && gpsChar <= 255)
				{
					if (gpsChar > 32)
					{
						nmeaTerm += (char)gpsChar;
					}

					if (tinyGPS.encode((char)gpsChar)) {
						yield();

						LogUtils::instance()->logTrace(LogUtils::trace1, nmeaTerm);
						nmeaTerm = "";
					}
				}
			}
		}
		if (millis() > 5000 && tinyGPS.charsProcessed() < 10)
		{
			LogUtils::instance()->logTrace(LogUtils::error, "No GPS detected: check wiring.");
		}
	}

	yield();
}

void MonitorHandler::clear()
{
  Serial1.println();
  Serial1.println();
}

void MonitorHandler::inflight_display()
{
  clear();
  Serial1.println("Inflight");
  Serial1.println();
  Serial1.println("Flight time ................ 1");
  Serial1.println("Flight time reset .......... h");
  Serial1.println("Return to main ............. 0");
  state_g = State_inflight_input;
}

void MonitorHandler::inflight_input()
{
  int data = Serial1.read();
  if (data > 0)
  {
    switch (data)
    {
      case '1':
      {
    	Serial1.print("inflight time: ");
    	Serial1.print(millis() - timebase_g);
    	Serial1.println(" ms");
      }
      break;

      case '0': state_g = State_main_display; break;
      case 'h': timebase_g = millis(); break;
      default: state_g = State_inflight_display;
    }
  }
}


void MonitorHandler::gps_display()
{
  clear();
  Serial1.println("GPS");
  Serial1.println();
  Serial1.println("Location ................... 1");
  Serial1.println("Height ..................... 2");
  Serial1.println("Speed & course ............. 3");
  Serial1.println("Date & time ................ 4");
  if (nmeaTestMode)
  {
	  Serial1.println("Disable NMEA TestMode....... 5");
  }
  else
  {
	  Serial1.println("Enable NMEA TestMode........ 5");
  }
  Serial1.println("Return to main ............. 0");
  state_g = State_gps_input;
}

void MonitorHandler::gps_input()
{
  int data = Serial1.read();
  if (data > 0)
  {
    switch (data)
    {
      case '1':
      {
		Serial1.print("long: ");
		Serial1.print(tinyGPS.location.rawLng().negative ? "-" : "+");
		Serial1.print(tinyGPS.location.lng(),6);
		Serial1.println(" deg");
		Serial1.print("lat : ");
		Serial1.print(tinyGPS.location.rawLat().negative ? "-" : "+");
		Serial1.print(tinyGPS.location.lat(),6);
		Serial1.println(" deg");
      }
      break;

      case '2':
      {
		Serial1.print("height: ");
		Serial1.print(tinyGPS.altitude.meters());
		Serial1.println("m");
      }
      break;

      case '3':
      {
		Serial1.print("speed : ");
		Serial1.print(tinyGPS.speed.kmph());
		Serial1.println(" km/h");
		Serial1.print("course: ");
		Serial1.print(tinyGPS.course.deg());
		Serial1.println(" deg");
      }
      break;

      case '4':
      {
		int y,m,d,hr,mi,sc;
		y = tinyGPS.date.year();
		m = tinyGPS.date.month();
		d = tinyGPS.date.day();
		hr = tinyGPS.time.hour();
		mi = tinyGPS.time.minute();
		sc = tinyGPS.time.second();
		Serial1.print("date: ");
		Serial1.print(y); Serial1.print("-");
		if (m < 10) {Serial1.print("0");}
		Serial1.print(m); Serial1.print("-");
		if (d < 10) {Serial1.print("0");}
		Serial1.print(d); Serial1.print(" T ");
		if (hr < 10) {Serial1.print("0");}
		Serial1.print(hr); Serial1.print(":");
		if (mi < 10) {Serial1.print("0");}
		Serial1.print(mi); Serial1.print(":");
		if (sc < 10) {Serial1.print("0");}
		Serial1.print(sc); Serial1.println(" UT");
      }
      break;

      case '5':
      {
   		  nmeaTestMode = !nmeaTestMode;
      }
      break;

      case '0': state_g = State_main_display; break;
      default: state_g = State_gps_display;
    }
  }
}

void MonitorHandler::main_display()
{
  clear();
  Serial1.println("DarkSky Inflight Control v 0.1");
  Serial1.println();
  Serial1.println("Inflight info .............. 1");
  Serial1.println("GPS ........................ 2");
  state_g = State_main_input;
}

void MonitorHandler::main_input()
{
  int data = Serial1.read();
  if (data > 0)
  {
    switch (data)
    {
      case '1': state_g = State_inflight_display; break;
      case '2': state_g = State_gps_display; break;
      default: state_g = State_main_display;
    }
  }
}
