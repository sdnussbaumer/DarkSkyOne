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

#ifndef I2CSENSOT_h
#define I2CSENSOT_h
#include <Arduino.h>

#define	SENSOR_ERROR	0x80000000

class I2CSensor
{
protected:
	int	wire_;
	int	device_;

public:
	I2CSensor();

	void setInterface(int w) {wire_ = w;}
	int getInterface() {return wire_;}

	void setDevice(int d) {device_ = d;}
	int getDevice() {return device_;}

	bool writeToDevice(byte adr, int cnt, byte* buff);
	bool writeToDevice(byte adr, byte data);
	int readFromDevice(byte adr, int cnt, byte* buff);

	int readSigned8(byte adr);
	int readUnsigned8(byte adr);

	int readSigned16Big(byte adr);
	int readUnsigned16Big(byte adr);
	int readSigned16Little(byte adr);
	int readUnsigned16Little(byte adr);

	int readSigned32Big(byte adr);
	unsigned int readUnsigned32Big(byte adr);
	int readSigned32Little(byte adr);
	unsigned int readUnsigned32Little(byte adr);

};

#endif
