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

#include <L3G4200D.h>
#include <Wire.h>
#include <math.h>
// Defines ////////////////////////////////////////////////////////////////
// The Arduino two-wire interface uses a 7-bit number for the address,
// and sets the last bit correctly based on reads and writes

//#define GYR_ADDRESS (0xD2 >> 1)


L3G4200D::L3G4200D()
{
	setDevice(0x69);

	gain_[0] = 1;
	gain_[1] = 1;
	gain_[2] = 1;
}



// Public Methods //////////////////////////////////////////////////////////////
// Turns on the L3G4200D's gyro and places it in normal mode.


void L3G4200D::enableDefault()
{
	// 0x0F = 0b00001111
	// Normal power mode, all axes enabled
	writeToDevice(L3G4200D_CTRL_REG1, 0x0F);
}

//// Writes a gyro register
//void L3G4200D::writeReg(byte reg, byte value)
//{
//	Wire.beginTransmission(GYR_ADDRESS);
//	Wire.write(reg);
//	Wire.write(value);
//	Wire.endTransmission();
//}
//
//// Reads a gyro register
//byte L3G4200D::readReg(byte reg)
//{
//	byte value;
//	Wire.beginTransmission(GYR_ADDRESS);
//	Wire.write(reg);
//	Wire.endTransmission();
//	Wire.requestFrom(GYR_ADDRESS, 1);
//	value = Wire.read();
//	Wire.endTransmission();
//	return value;
//}

// Reads the 3 gyro channels and stores them in vector g
void L3G4200D::read()
{
	short val;
	byte data[6];
	readFromDevice(L3G4200D_OUT_X_L | (1 << 7), 6, data);

	val = data[1];
	val <<= 8;
	val |= data[0];
	data_[0] = val * gain_[0];

	val = data[3];
	val <<= 8;
	val |= data[2];
	data_[1] = val * gain_[1];

	val = data[5];
	val <<= 8;
	val |= data[4];
	data_[2] = val * gain_[2];

	//Wire.beginTransmission(GYR_ADDRESS);
	//// assert the MSB of the address to get the gyro
	//// to do slave-transmit subaddress updating.
	//Wire.write(L3G4200D_OUT_X_L | (1 << 7));
	//Wire.endTransmission();
	//Wire.requestFrom(GYR_ADDRESS, 6);
	//if (Wire.available() < 6) {
	//	int low, high;
	//	low = Wire.read();
	//	high = Wire.read();
	//	data_[0] = ((high << 8) | low) * gain_[0];
	//	low = Wire.read();
	//	high = Wire.read();
	//	data_[1] = ((high << 8) | low) * gain_[1];
	//	low = Wire.read();
	//	high = Wire.read();
	//	data_[2] = ((high << 8) | low) * gain_[2];
	//}
}

void L3G4200D::setup()
{
	enableDefault();
}

void L3G4200D::update()
{
	read();

	int temp = readSigned8(0x26);
	temp_ = temp;
}

