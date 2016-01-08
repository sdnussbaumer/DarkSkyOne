/*
GY80 Task class.
Copyright (C) 2016 Sascha Nussbaumer
All rights reserved.

Parts of this class are implemented based on the examples of 
Adafruit Industries.

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

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_HMC5883_U.h>

#include "GY80Task.h"
#include "LogUtils.h";

// Initialize static variable of Singleton
GY80Task* GY80Task::_instance = 0;

// sensor global variables
Adafruit_BMP085 bmp;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

GY80Task::GY80Task()
{
	setupBMP085();
	setupADXL345();
	setupHMC5883();
}

void GY80Task::handleGY80()
{
	// TODO: Read values asynchronous and save to variables
}

void GY80Task::printPressure()
{
	Serial1.print("Temperature = ");
	Serial1.print(bmp.readTemperature());
	Serial1.println(" *C");

	Serial1.print("Pressure = ");
	Serial1.print(bmp.readPressure());
	Serial1.println(" Pa");

	// Calculate altitude assuming 'standard' barometric
	// pressure of 1013.25 millibar = 101325 Pascal
	Serial1.print("Altitude = ");
	Serial1.print(bmp.readAltitude());
	Serial1.println(" meters");

	Serial1.print("Pressure at sealevel (calculated) = ");
	Serial1.print(bmp.readSealevelPressure());
	Serial1.println(" Pa");
}

void GY80Task::printAccelerator()
{
	/* Get a new sensor event */
	sensors_event_t event;
	accel.getEvent(&event);

	/* Display the results (acceleration is measured in m/s^2) */
	Serial1.print("X: "); Serial1.print(event.acceleration.x); Serial1.print("  ");
	Serial1.print("Y: "); Serial1.print(event.acceleration.y); Serial1.print("  ");
	Serial1.print("Z: "); Serial1.print(event.acceleration.z); Serial1.print("  "); Serial1.println("m/s^2 ");
}

void GY80Task::printGyroscope()
{
	/* Get a new sensor event */
	sensors_event_t event;
	mag.getEvent(&event);

	/* Display the results (magnetic vector values are in micro-Tesla (uT)) */
	Serial1.print("X: "); Serial1.print(event.magnetic.x); Serial1.print("  ");
	Serial1.print("Y: "); Serial1.print(event.magnetic.y); Serial1.print("  ");
	Serial1.print("Z: "); Serial1.print(event.magnetic.z); Serial1.print("  "); Serial1.println("uT");
}

void GY80Task::printCompass()
{
	/* Get a new sensor event */
	sensors_event_t event;
	mag.getEvent(&event);

	// Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
	// Calculate heading when the magnetometer is level, then correct for signs of axis.
	float heading = atan2(event.magnetic.y, event.magnetic.x);

	// Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
	// Find yours here: http://www.magnetic-declination.com/
	// Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
	// If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
	float declinationAngle = 0.22;
	heading += declinationAngle;

	// Correct for when signs are reversed.
	if (heading < 0)
		heading += 2 * PI;

	// Check for wrap due to addition of declination.
	if (heading > 2 * PI)
		heading -= 2 * PI;

	// Convert radians to degrees for readability.
	float headingDegrees = heading * 180 / M_PI;

	Serial1.print("Heading (degrees): "); Serial1.println(headingDegrees);
}


void GY80Task::setupBMP085()
{
	if (!bmp.begin()) {
		LogUtils::instance()->logTrace(LogUtils::error, "Could not find a valid BMP085 sensor, check wiring!");
		while (1) {}
	}
}

void GY80Task::setupADXL345()
{
	/* Initialise the sensor */
	if (!accel.begin())
	{
		/* There was a problem detecting the ADXL345 ... check your connections */
		LogUtils::instance()->logTrace(LogUtils::error, "Ooops, no ADXL345 detected ... Check your wiring!");
		while (1);
	}

	/* Set the range to whatever is appropriate for your project */
	accel.setRange(ADXL345_RANGE_16_G);
}

void GY80Task::setupHMC5883()
{
	/* Initialise the sensor */
	if (!mag.begin())
	{
		/* There was a problem detecting the HMC5883 ... check your connections */
		LogUtils::instance()->logTrace(LogUtils::error, "Ooops, no HMC5883 detected ... Check your wiring!");
		while (1);
	}
}

