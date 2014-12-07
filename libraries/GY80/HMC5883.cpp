/*
HMC5883 - compass module.
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

#include "HMC5883.h"
//#include <Wire.h> //I2C Arduino Library

//#define ADDRESS 0x1E //0011110b, I2C 7bit address of HMC5883

HMC5883::HMC5883()
{
	setDevice(0x1E);

	gain_[0] = 1;
	gain_[1] = 1;
	gain_[2] = 1;
}

void HMC5883::setup()
{
	writeToDevice(0x00, 0x10); // 15 Hz default, normal measurement

	writeToDevice(0x02, 0x01); // single measurement mode

	//Wire.begin();
	////Put the HMC5883 IC into the correct operating mode
	//Wire.beginTransmission(ADDRESS); //open communication with HMC5883
	//Wire.write(0x02); //select mode register
	//Wire.write(0x00); //continuous measurement mode
	//Wire.endTransmission();
}

void HMC5883::update()
{
	byte data[6];
	readFromDevice(0x03, 6, data); // read sample
	writeToDevice(0x02, 0x01); // start new measurement

	idata_[0] = data[0];
	idata_[0] <<= 8;
	idata_[0] |= data[1];

	idata_[2] = data[2];
	idata_[2] <<= 8;
	idata_[2] |= data[3];

	idata_[1] = data[4];
	idata_[1] <<= 8;
	idata_[1] |= data[5];

	data_[0] = idata_[0] * gain_[0];
	data_[1] = idata_[1] * gain_[1];
	data_[2] = idata_[2] * gain_[2];

	////Tell the HMC5883 where to begin reading data
	//Wire.beginTransmission(ADDRESS);
	//Wire.write(0x03); //select register 3, X MSB register
	//Wire.endTransmission();
	////Read data from each axis, 2 registers per axis
	//Wire.requestFrom(ADDRESS, 6);
	//if (Wire.available() >= 6) {
	//	idata_[0] = Wire.read()<<8; //X msb
	//	idata_[0] |= Wire.read(); //X lsb
	//	idata_[2] = Wire.read()<<8; //Z msb
	//	idata_[2] |= Wire.read(); //Z lsb
	//	idata_[1] = Wire.read()<<8; //Y msb
	//	idata_[1] |= Wire.read(); //Y lsb
	//	data_[0] = idata_[0] * gain_[0];
	//	data_[1] = idata_[1] * gain_[1];
	//	data_[2] = idata_[2] * gain_[2];
	//}
	//Print out values of each axis
	//Serial.print("x: ");
	//Serial.print(x);
	//Serial.print(" y: ");
	//Serial.print(y);
	//Serial.print(" z: ");
	//Serial.println(z);
}


int HMC5883::getStatus()
{
	return readUnsigned8(0x09);

	//Wire.beginTransmission(ADDRESS);
	//Wire.write(0x09); //select register 3, X MSB register
	//Wire.endTransmission();
	//Wire.requestFrom(ADDRESS, 1);
	//if (Wire.available() >= 1) {
	//	return Wire.read();
	//}
	//return -1;
}

int HMC5883::getId()
{
	byte data[3];
	readFromDevice(0x0a, 3, data);
	int res = data[0];
	res <<= 8;
	res |= data[1];
	res <<= 8;
	res |= data[2];
	return res;

	//Wire.beginTransmission(ADDRESS);
	//Wire.write(0x0a); //select register 3, X MSB register
	//Wire.endTransmission();
	//int res = 0;
	//Wire.requestFrom(ADDRESS, 3);
	//if (Wire.available() >= 3) {
	//	res = Wire.read();
	//	res <<= 8;
	//	res = Wire.read();
	//	res <<= 8;
	//	res = Wire.read();
	//}
	//return res;
}


