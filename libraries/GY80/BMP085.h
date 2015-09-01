/*
BMP085 - pressure & temperature sensor.
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

#ifndef BMP085_h
#define BMP085_h

#include <SCoop.h>
#include <I2CSensor.h>


class BMP085 : public I2CSensor
{
private:
	// Calibration values
	int ac1;
	int ac2;
	int ac3;
	unsigned int ac4;
	unsigned int ac5;
	unsigned int ac6;
	int b1;
	int b2;
	int mb;
	int mc;
	int md;
	// b5 is calculated in calcTemp(...), this variable is also used in calcPressure(...)
	// so ...Temperature(...) must be called before ...Pressure(...).
	long b5;
	double temperature_;
	double pressure_;
	bool calibrated_;

	void calibrate();
	short calcTemp(unsigned int ut);
	long calcPressure(unsigned long up);
	//char readByte(unsigned char address);
	//int readInt(unsigned char address);
	unsigned int readUT();
	unsigned long readUP();


public:

	BMP085();

	void setup();
	void update();

	double getTemp() {return temperature_;}
	double getPressure() {return pressure_;}

};

#endif
