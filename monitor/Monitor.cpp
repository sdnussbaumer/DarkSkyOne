/*
 * Monitor.cpp
 *
 *  Created on: 17.10.2014
 *      Author: san
 */

#include "Monitor.h"
#include "TinyGPS++.h"
#include "LogUtils.h"

// Global Variables
MonitorHandler::State state_g;
TinyGPSPlus tinyGPS;
unsigned long timebase_g;
String gpsstring = "";

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

void MonitorHandler::setGPS(TinyGPSPlus& gps)
{
	tinyGPS = gps;
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
	while (Serial2.available())
	{
		int data = Serial2.read();
		gpsstring += (char)data;

		//Serial.print(char(data));
		if (tinyGPS.encode(data))
		{  // new data has arived
//	    	Serial.print("long: ");
//	    	Serial.print(tinyGPS.location.rawLng().negative ? "-" : "+");
//	        Serial.print(tinyGPS.location.lng(),6);
//	        Serial.println(" deg");
//	        Serial.print("lat : ");
//	        Serial.print(tinyGPS.location.rawLat().negative ? "-" : "+");
//	        Serial.print(tinyGPS.location.lat(),6);
//	        Serial.println(" deg");

			//LogUtils::instance()->logTrace(LogUtils::trace3, "MonitorHandler::handleGPS NMEA: " + gpsstring);
			gpsstring = "";

		}
	}
}

void MonitorHandler::clear()
{
  //Serial1.write(27);       // ESC command
  //Serial1.print("[2J");    // clear screen command
  //Serial1.write(27);
  //Serial1.print("[H");     // cursor to home command
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
