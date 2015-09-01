/*
GY80 - sensor module.
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

#ifndef GY80_h
#define GY80_h

#include <BMP085.h>
#include <ADXL345.h>
#include <HMC5883.h>
#include <L3G4200D.h>


class GY80
{
private:
	BMP085		sensor1_;
	ADXL345		sensor2_;
	HMC5883		sensor3_;
	L3G4200D	sensor4_;

public:

	GY80();


	void setup();
	void update();

	BMP085& sensor1() {return sensor1_;}
	ADXL345& sensor2() {return sensor2_;}
	HMC5883& sensor3() {return sensor3_;}
	L3G4200D& sensor4() {return sensor4_;}

};

#endif
