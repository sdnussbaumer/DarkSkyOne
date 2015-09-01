/*
I2C Sensor base class.
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

#include "I2CSensor.h"
#include <Wire.h>

I2CSensor::I2CSensor()
:
	wire_(0),
	device_(-1)
{
}

bool I2CSensor::writeToDevice(byte adr, int cnt, byte* buff)
{
	switch (wire_) {
	case 0:
		Wire.beginTransmission(device_);
		Wire.write(adr);
		Wire.write(buff, cnt);
		Wire.endTransmission();
		return true;

	case 1:
		Wire1.beginTransmission(device_);
		Wire1.write(adr);
		Wire1.write(buff, cnt);
		Wire1.endTransmission();
		return true;

	default:;
	}
	return false;
}

bool I2CSensor::writeToDevice(byte adr, byte data)
{
	writeToDevice(adr, 1, &data);
}


int I2CSensor::readFromDevice(byte adr, int cnt, byte* buff)
{
	int avail;
	switch (wire_) {
	case 0:
		Wire.beginTransmission(device_);
		Wire.write(adr);
		Wire.endTransmission();
		Wire.beginTransmission(device_);
		Wire.requestFrom(device_, cnt);
		avail = Wire.available();
		if (avail >= cnt) {
			for (int i=0; i<cnt; ++i) {
				buff[i] = Wire.read();
			}
			return cnt;
		}
		break;

	case 1:
		Wire1.beginTransmission(device_);
		Wire1.write(adr);
		Wire1.endTransmission();
		Wire1.beginTransmission(device_);
		Wire1.requestFrom(device_, cnt);
		avail = Wire1.available();
		if (avail >= cnt) {
			for (int i=0; i<cnt; ++i) {
				buff[i] = Wire1.read();
			}
			return cnt;
		}
		break;

	default:;
	}
	return 0;
}

int I2CSensor::readSigned8(byte adr)
{
	byte data;
	if (readFromDevice(adr, 1, &data) == 1) {
		signed char res = data;
		return res;
	}
	return SENSOR_ERROR;
}

int I2CSensor::readUnsigned8(byte adr)
{
	byte data;
	if (readFromDevice(adr, 1, &data) == 1) {
		return data;
	}
	return SENSOR_ERROR;
}

int I2CSensor::readSigned16Big(byte adr)
{
	byte data[2];
	if (readFromDevice(adr, 2, data) == 2) {
		short res = data[0];
		res <<= 8;
		res |= data[1];
		return res;
	}
	return SENSOR_ERROR;
}

int I2CSensor::readUnsigned16Big(byte adr)
{
	byte data[2];
	if (readFromDevice(adr, 2, data) == 2) {
		int res = data[0];
		res <<= 8;
		res |= data[1];
		return res;
	}
	return SENSOR_ERROR;
}

int I2CSensor::readSigned16Little(byte adr)
{
	byte data[2];
	if (readFromDevice(adr, 2, data) == 2) {
		short res = data[1];
		res <<= 8;
		res |= data[0];
		return res;
	}
	return SENSOR_ERROR;
}

int I2CSensor::readUnsigned16Little(byte adr)
{
	byte data[2];
	if (readFromDevice(adr, 2, data) == 2) {
		int res = data[1];
		res <<= 8;
		res |= data[0];
		return res;
	}
	return SENSOR_ERROR;
}



int I2CSensor::readSigned32Big(byte adr)
{
	byte data[4];
	if (readFromDevice(adr, 4, data) == 4) {
		short res = data[0];
		res <<= 8;
		res |= data[1];
		res <<= 8;
		res |= data[2];
		res <<= 8;
		res |= data[3];
		return res;
	}
	return SENSOR_ERROR;
}

unsigned int I2CSensor::readUnsigned32Big(byte adr)
{
	byte data[4];
	if (readFromDevice(adr, 4, data) == 4) {
		unsigned int res = data[0];
		res <<= 8;
		res |= data[1];
		res <<= 8;
		res |= data[2];
		res <<= 8;
		res |= data[3];
		return res;
	}
	return SENSOR_ERROR;
}

int I2CSensor::readSigned32Little(byte adr)
{
	byte data[4];
	if (readFromDevice(adr, 4, data) == 4) {
		short res = data[3];
		res <<= 8;
		res |= data[2];
		res <<= 8;
		res |= data[1];
		res <<= 8;
		res |= data[0];
		return res;
	}
	return SENSOR_ERROR;
}

unsigned int I2CSensor::readUnsigned32Little(byte adr)
{
	byte data[4];
	if (readFromDevice(adr, 4, data) == 4) {
		unsigned int res = data[3];
		res <<= 8;
		res |= data[2];
		res <<= 8;
		res |= data[1];
		res <<= 8;
		res |= data[0];
		return res;
	}
	return SENSOR_ERROR;
}



