/*
Flight Display - user interface.
Copyright (C) 2014 Stefan Mauerhofer
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

#include "Arduino.h"
#include "FlightUser.h"
#include "GPSTask.h"

FlightUser::FlightUser(GY80Task &gy80, TinyGPSPlus &gps)
:
	gy80_(gy80),
	gps_(gps)
{
	state_ = main_input;
	timebase_ = millis();
	sensor_read_delay_ = 0;
}

void FlightUser::setup()
{
	state_ = main_input;
	timebase_ = millis();
	Serial1.begin(115200);
}

void FlightUser::clearScreen()
{
	Serial1.println();
	Serial1.println();
}

void FlightUser::loop()
{
  switch (state_)
  {
    case main_display: mainDisplay(); break;
    case main_input: mainInput(); break;
    case inflight_display: inflightDisplay(); break;
    case inflight_input: inflightInput(); break;
    case gps_display: gpsDisplay(); break;
    case gps_input: gpsInput(); break;
    case sensor_display: sensorDisplay(); break;
    case sensor_input: sensorInput(); break;
  }
}

void FlightUser::inflightDisplay()
{
	clearScreen();
	Serial1.println("Inflight");
	Serial1.println();
	Serial1.println("Flight time ................ 1");
	Serial1.println("Flight time reset .......... h");
	Serial1.println("Return to main ............. 0");
	state_ = inflight_input;
}

void FlightUser::inflightInput()
{
  int data = Serial1.read();
  if (data > 0)
  {
    switch (data)
    {
      case '1':
      {
        Serial1.print("inflight time: ");
        Serial1.print(millis() - timebase_);
        Serial1.println(" ms");
        Serial1.print("sensor loop delay: ");
        Serial1.print(sensor_read_delay_);
        Serial1.println(" ms");
      }
      break;

      case '0': state_ = main_display; break;
      case 'h': timebase_ = millis(); break;
      default: state_ = inflight_display;
    }
  }
}

void FlightUser::gpsDisplay()
{
	clearScreen();
	Serial1.println("GPS");
	Serial1.println();
	Serial1.println("Location ................... 1");
	Serial1.println("Height ..................... 2");
	Serial1.println("Speed & course ............. 3");
	Serial1.println("Date & time ................ 4");
	if (GPSTask::instance()->getTestMode())
	{
	  Serial1.println("Disable NMEA TestMode....... 5");
	}
	else
	{
	  Serial1.println("Enable NMEA TestMode........ 5");
	}
	Serial1.println("Return to main ............. 0");
	state_ = gps_input;
}

void FlightUser::gpsInput()
{
  int data = Serial1.read();
  if (data > 0)
  {
    switch (data)
    {
      case '1':
      {
        Serial1.print("long: ");
        Serial1.print(gps_.location.rawLng().negative ? "-" : "+");
        Serial1.print(gps_.location.lng(),6);
        Serial1.println(" deg");
        Serial1.print("lat : ");
        Serial1.print(gps_.location.rawLat().negative ? "-" : "+");
        Serial1.print(gps_.location.lat(),6);
        Serial1.println(" deg");
      }
      break;

      case '2':
      {
        Serial1.print("height: ");
        Serial1.print(gps_.altitude.meters());
        Serial1.println("m");
      }
      break;

      case '3':
      {
        Serial1.print("speed : ");
        Serial1.print(gps_.speed.kmph());
        Serial1.println(" km/h");
        Serial1.print("course: ");
        Serial1.print(gps_.course.deg());
        Serial1.println(" deg");
      }
      break;

      case '4':
      {
        int y,m,d,hr,mi,sc;
        y = gps_.date.year();
        m = gps_.date.month();
        d = gps_.date.day();
        hr = gps_.time.hour();
        mi = gps_.time.minute();
        sc = gps_.time.second();
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
    	  GPSTask::instance()->setTestMode(!GPSTask::instance()->getTestMode());
   		  if (GPSTask::instance()->getTestMode())
   		  {
   			  Serial1.println("NMEA Test Mode activated!");
   		  }
   		  else
   		  {
   			  Serial1.println("NMEA Test Mode deactivated!");
   		  }
      }
      break;

      case '0': state_ = main_display; break;
      default: state_ = gps_display;
    }
  }
}

void FlightUser::mainDisplay()
{
	clearScreen();
	Serial1.println("DarkSky Inflight Control V0.5.1");
	Serial1.println();
	Serial1.println("Inflight info .............. 1");
	Serial1.println("GPS ........................ 2");
	Serial1.println("Sensor ..................... 3");
	state_ = main_input;
}

void FlightUser::mainInput()
{
  int data = Serial1.read();
  if (data > 0)
  {
    switch (data)
    {
      case '1': state_ = inflight_display; break;
      case '2': state_ = gps_display; break;
      case '3': state_ = sensor_display; break;
      default: state_ = main_display;
    }
  }
}


void FlightUser::sensorDisplay()
{
	clearScreen();
	Serial1.println("Sensor");
	Serial1.println();
	Serial1.println("Temp & Pressure ........... 1");
	Serial1.println("Accel ..................... 2");
	Serial1.println("Gyro ...................... 3");
	Serial1.println("Compass ................... 4");
	Serial1.println("Trace Temp & Pressure ..... 5");
	Serial1.println("Trace Accel ............... 6");
	Serial1.println("Trace Gyro ................ 7");
	Serial1.println("Trace Compass ............. 8");
	Serial1.println("Return to main ............ 0");
	state_ = sensor_input;
}

void FlightUser::sensorInput()
{
  int data = Serial1.read();
  if (data > 0)
  {
    switch (data)
    {
      case '1':
      {
        Serial1.println("Temp & Humidity");
        gy80_.printPressure();
      }
      break;

      case '2':
      {
        Serial1.println("Accel");
        gy80_.printAccelerator();
      }
      break;

      case '3':
      {
        Serial1.println("Gyro");
        gy80_.printGyroscope();
      }
      break;

      case '4':
      {
        Serial1.println("Compass");
        gy80_.printCompass();
     }
      break;

      case '5':
      {
        while (Serial1.read()<= 0) {
          gy80_.printPressure();
          delay(200);
        }
      }
      break;

      case '6':
      {
        while (Serial1.read()<= 0) {
          gy80_.printAccelerator();
          delay(200);
        }
      }
      break;

      case '7':
      {
        while (Serial1.read()<= 0) {
          gy80_.printGyroscope();
          delay(200);
        }
      }
      break;

      case '8':
      {
        while (Serial1.read()<= 0) {
          gy80_.printCompass();
		  delay(200);
        }
      }
      break;

      case '0': state_ = main_display; break;
      default: state_ = sensor_display;
    }
  }
}






