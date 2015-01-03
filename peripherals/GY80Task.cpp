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

// Initialize static variable of Singleton
GY80Task* GY80Task::_instance = 0;

GY80Task::GY80Task()
:
	sensor_read_delay_(0)
{
	gy80_.setup();
}

void GY80Task::handleGY80()
{
  unsigned long t0 = millis();
  gy80_.update();
  unsigned long t1 = millis();
  sensor_read_delay_ = (sensor_read_delay_ + t1 - t0) >> 1;
}

void GY80Task::printPressure()
{
	Serial1.print(" Temp: "); Serial1.print(gy80_.sensor1().getTemp()); Serial1.println(" C");
	Serial1.print(" Pres: "); Serial1.print(gy80_.sensor1().getPressure()); Serial1.println(" Pa");

}

void GY80Task::printAccelerator()
{
	Serial1.print(" x: "); Serial1.print(gy80_.sensor2().getData()[0]); Serial1.println(" g");
	Serial1.print(" y: "); Serial1.print(gy80_.sensor2().getData()[1]); Serial1.println(" g");
	Serial1.print(" z: "); Serial1.print(gy80_.sensor2().getData()[2]); Serial1.println(" g");
}

void GY80Task::printGyroscope()
{
	Serial1.print(" x: "); Serial1.print(gy80_.sensor4().getData()[0]); Serial1.println(" d/s");
	Serial1.print(" y: "); Serial1.print(gy80_.sensor4().getData()[1]); Serial1.println(" d/s");
	Serial1.print(" z: "); Serial1.print(gy80_.sensor4().getData()[2]); Serial1.println(" d/s");
	Serial1.print(" t: "); Serial1.print(gy80_.sensor4().getTemperature()); Serial1.println(" C");
}

void GY80Task::printCompass()
{
	Serial1.print(" x: "); Serial1.print(gy80_.sensor3().getData()[0]); Serial1.println(" G");
	Serial1.print(" y: "); Serial1.print(gy80_.sensor3().getData()[1]); Serial1.println(" G");
	Serial1.print(" z: "); Serial1.print(gy80_.sensor3().getData()[2]); Serial1.println(" G");
	Serial1.print(" Stat: "); Serial1.println(gy80_.sensor3().getStatus());
	Serial1.print(" Id:   "); Serial1.println(gy80_.sensor3().getId());
}




