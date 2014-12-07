/*
GY80 - sensor task.
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

#include "GY80Task.h"
#include <Arduino.h>


GY80Task::GY80Task()
:
	sensor_read_delay_(0)
{
}

void GY80Task::setup()
{
  gy80_.setup();
}

void GY80Task::loop()
{
  unsigned long t0 = millis();
  gy80_.update();
  unsigned long t1 = millis();
  sensor_read_delay_ = (sensor_read_delay_ + t1 - t0) >> 1;
}

void GY80Task::printPressure()
{
	Serial.print(" Temp: "); Serial.print(gy80_.sensor1().getTemp()); Serial.println(" C");
	Serial.print(" Pres: "); Serial.print(gy80_.sensor1().getPressure()); Serial.println(" Pa");

}

void GY80Task::printAccelerator()
{
	Serial.print(" x: "); Serial.print(gy80_.sensor2().getData()[0]); Serial.println(" g");
	Serial.print(" y: "); Serial.print(gy80_.sensor2().getData()[1]); Serial.println(" g");
	Serial.print(" z: "); Serial.print(gy80_.sensor2().getData()[2]); Serial.println(" g");
}

void GY80Task::printGyroscope()
{
	Serial.print(" x: "); Serial.print(gy80_.sensor4().getData()[0]); Serial.println(" d/s");
	Serial.print(" y: "); Serial.print(gy80_.sensor4().getData()[1]); Serial.println(" d/s");
	Serial.print(" z: "); Serial.print(gy80_.sensor4().getData()[2]); Serial.println(" d/s");
	Serial.print(" t: "); Serial.print(gy80_.sensor4().getTemperature()); Serial.println(" C");
}

void GY80Task::printCompass()
{
	Serial.print(" x: "); Serial.print(gy80_.sensor3().getData()[0]); Serial.println(" G");
	Serial.print(" y: "); Serial.print(gy80_.sensor3().getData()[1]); Serial.println(" G");
	Serial.print(" z: "); Serial.print(gy80_.sensor3().getData()[2]); Serial.println(" G");
	Serial.print(" Stat: "); Serial.println(gy80_.sensor3().getStatus());
	Serial.print(" Id:   "); Serial.println(gy80_.sensor3().getId());
}




