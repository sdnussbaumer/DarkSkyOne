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

#include "BMP085.h"
#include <Wire.h>

//#define BMP085_ADDRESS 0x77 // I2C address of BMP085

const unsigned char OSS = 0; // Oversampling Setting

BMP085::BMP085()
:
	calibrated_(false)
{
	setDevice(0x77);
}


void BMP085::setup()
{
	calibrate();
}

void BMP085::update()
{
	calibrate();
	temperature_ = calcTemp(readUT());
	pressure_ = calcPressure(readUP());
	temperature_ *= 0.1;
}
/*
void loop()
{
temperature = bmp085GetTemperature(bmp085ReadUT());
pressure = bmp085GetPressure(bmp085ReadUP());
Serial.print("Temperature: ");
Serial.print(temperature, DEC);
Serial.println(" *0.1 deg C");
Serial.print("Pressure: ");
Serial.print(pressure, DEC);
Serial.println(" Pa");
Serial.println();
delay(1000);
}
*/
// Stores all of the bmp085's calibration values into global variables
// Calibration values are required to calculate temp and pressure
// This function should be called at the beginning of the program
void BMP085::calibrate()
{
	if (calibrated_) {return;}
	//ac1 = readUnsigned8(0xAA);
	//ac1 <<= 8;
	//ac1 |= readUnsigned8(0xAB);
	ac1 = readSigned16Big(0xAA);
	ac2 = readSigned16Big(0xAC);
	ac3 = readSigned16Big(0xAE);
	ac4 = readUnsigned16Big(0xB0);
	ac5 = readUnsigned16Big(0xB2);
	ac6 = readUnsigned16Big(0xB4);
	b1 = readSigned16Big(0xB6);
	b2 = readSigned16Big(0xB8);
	mb = readSigned16Big(0xBA);
	mc = readSigned16Big(0xBC);
	md = readSigned16Big(0xBE);

	calibrated_ = true;
	if (ac1 == 0) {calibrated_ = false;}
	if (ac2 == 0) {calibrated_ = false;}
	if (ac3 == 0) {calibrated_ = false;}
	if (ac4 == 0) {calibrated_ = false;}
	if (ac5 == 0) {calibrated_ = false;}
	if (ac6 == 0) {calibrated_ = false;}
	if (b1 == 0) {calibrated_ = false;}
	if (b2 == 0) {calibrated_ = false;}
	if (mb == 0) {calibrated_ = false;}
	if (mc == 0) {calibrated_ = false;}
	if (md == 0) {calibrated_ = false;}
	//Serial.print(" dev: "); Serial.print(device_);
	//Serial.print(" ac1: "); Serial.print(ac1);
	//Serial.print(" ac2: "); Serial.print(ac2);
	//Serial.print(" ac3: "); Serial.print(ac3);
	//Serial.print(" ac4: "); Serial.print(ac4);
	//Serial.print(" ac5: "); Serial.print(ac5);
	//Serial.print(" ac6: "); Serial.print(ac6);
	//Serial.print(" b1: "); Serial.print(b1);
	//Serial.print(" b2: "); Serial.print(b2);
	//Serial.print(" mb: "); Serial.print(mb);
	//Serial.print(" mc: "); Serial.print(mc);
	//Serial.print(" md: "); Serial.println(md);
}

// Calculate temperature given ut.
// Value returned will be in units of 0.1 deg C
short BMP085::calcTemp(unsigned int ut)
{
	long x1, x2;
	x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;
	x2 = ((long)mc << 11)/(x1 + md);
	b5 = x1 + x2;


	return ((b5 + 8)>>4);
}

// Calculate pressure given up
// calibration values must be known
// b5 is also required so bmp085GetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
long BMP085::calcPressure(unsigned long up)
{
	long x1, x2, x3, b3, b6, p;
	unsigned long b4, b7;
	b6 = b5 - 4000;
	// Calculate B3
	x1 = (b2 * (b6 * b6)>>12)>>11;
	x2 = (ac2 * b6)>>11;
	x3 = x1 + x2;
	b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;
	// Calculate B4
	x1 = (ac3 * b6)>>13;
	x2 = (b1 * ((b6 * b6)>>12))>>16;
	x3 = ((x1 + x2) + 2)>>2;
	b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;
	b7 = ((unsigned long)(up - b3) * (50000>>OSS));
	if (b7 < 0x80000000)
	p = (b7<<1)/b4;
	else
	p = (b7/b4)<<1;
	x1 = (p>>8) * (p>>8);
	x1 = (x1 * 3038)>>16;
	x2 = (-7357 * p)>>16;
	p += (x1 + x2 + 3791)>>4;
	return p;
}

// Read 1 byte from the BMP085 at 'address'
//char BMP085::readByte(unsigned char adr)
//{
//	return (byte)readUnsigned8(adr);
//
//	//unsigned char data;
//	//Wire.beginTransmission(BMP085_ADDRESS);
//	//Wire.write(address);
//	//Wire.endTransmission();
//	//Wire.requestFrom(BMP085_ADDRESS, 1);
//	//while(!Wire.available()) {yield();};
//	//return Wire.read();
//}

// Read 2 bytes from the BMP085
// First byte will be from 'address'
// Second byte will be from 'address'+1
//int BMP085::readInt(unsigned char adr)
//{
//	return readSigned16Big(adr);
//
//	//unsigned char msb, lsb;
//	//Wire.beginTransmission(BMP085_ADDRESS);
//	//Wire.write(address);
//	//Wire.endTransmission();
//	//Wire.requestFrom(BMP085_ADDRESS, 2);
//	//while(Wire.available()<2) {yield();};
//	//msb = Wire.read();
//	//lsb = Wire.read();
//	//return (int) msb<<8 | lsb;
//}
// Read the uncompensated temperature value
unsigned int BMP085::readUT()
{
	unsigned int ut;
	// Write 0x2E into Register 0xF4
	// This requests a temperature reading
	writeToDevice(0xf4, 0x2e);
	// Wait at least 4.5ms
	sleep(5);
	int res = readUnsigned16Big(0xf6);

 //   Serial.print(" UT: "); Serial.print(res);

	return res;

	//Wire.beginTransmission(BMP085_ADDRESS);
	//Wire.write(0xF4);
	//Wire.write(0x2E);
	//Wire.endTransmission();
	//// Wait at least 4.5ms
	//sleep(5);
	//// Read two bytes from registers 0xF6 and 0xF7
	//ut = readInt(0xF6);
	//return ut;
}

// Read the uncompensated pressure value
unsigned long BMP085::readUP()
{
	unsigned char msb, lsb, xlsb;
	unsigned long up = 0;
	// Write 0x34+(OSS<<6) into register 0xF4
	// Request a pressure reading w/ oversampling setting
	writeToDevice(0xf4, 0x34 + (OSS<<6));
	// Wait for conversion, delay time dependent on OSS
	sleep(2 + (3<<OSS));

	byte data[3];
	readFromDevice(0xF6, 3, data);
	unsigned long res = data[0];
	res <<= 8;
	res |= data[1];
	res <<= 8;
	res |= data[2];
	res >>= 8-OSS;

 //   Serial.print(" UP: "); Serial.println(res);

	return res;

	//Wire.beginTransmission(BMP085_ADDRESS);
	//Wire.write(0xF4);
	//Wire.write(0x34 + (OSS<<6));
	//Wire.endTransmission();
	//// Wait for conversion, delay time dependent on OSS
	//sleep(2 + (3<<OSS));
	//// Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
	//Wire.beginTransmission(BMP085_ADDRESS);
	//Wire.write(0xF6);
	//Wire.endTransmission();
	//Wire.requestFrom(BMP085_ADDRESS, 3);
	//// Wait for data to become available
	//while(Wire.available() < 3) {yield();};
	//msb = Wire.read();
	//lsb = Wire.read();
	//xlsb = Wire.read();
	//up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);
	//return up;
}


