/*
ADXL345 - accelerator module.
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

/**************************************************************************
* *
* ADXL345 Driver for Arduino *
* *
***************************************************************************
* *
* This program is free software; you can redistribute it and/or modify *
* it under the terms of the GNU License. *
* This program is distributed in the hope that it will be useful, *
* but WITHOUT ANY WARRANTY; without even the implied warranty of *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the *
* GNU License V2 for more details. *
* *
***************************************************************************/
#include "Arduino.h"
#include "ADXL345.h"
#include <Wire.h>
//#define ADXL345_DEVICE (0x53) // ADXL345 device address
#define ADXL345_TO_READ (6) // num of bytes we are going to read each time (two bytes for each axis)

/* ------- Register names ------- */
#define ADXL345_DEVID 0x00
#define ADXL345_RESERVED1 0x01
#define ADXL345_THRESH_TAP 0x1d
#define ADXL345_OFSX 0x1e
#define ADXL345_OFSY 0x1f
#define ADXL345_OFSZ 0x20
#define ADXL345_DUR 0x21
#define ADXL345_LATENT 0x22
#define ADXL345_WINDOW 0x23
#define ADXL345_THRESH_ACT 0x24
#define ADXL345_THRESH_INACT 0x25
#define ADXL345_TIME_INACT 0x26
#define ADXL345_ACT_INACT_CTL 0x27
#define ADXL345_THRESH_FF 0x28
#define ADXL345_TIME_FF 0x29
#define ADXL345_TAP_AXES 0x2a
#define ADXL345_ACT_TAP_STATUS 0x2b
#define ADXL345_BW_RATE 0x2c
#define ADXL345_POWER_CTL 0x2d
#define ADXL345_INT_ENABLE 0x2e
#define ADXL345_INT_MAP 0x2f
#define ADXL345_INT_SOURCE 0x30
#define ADXL345_DATA_FORMAT 0x31
#define ADXL345_DATAX0 0x32
#define ADXL345_DATAX1 0x33
#define ADXL345_DATAY0 0x34
#define ADXL345_DATAY1 0x35
#define ADXL345_DATAZ0 0x36
#define ADXL345_DATAZ1 0x37
#define ADXL345_FIFO_CTL 0x38
#define ADXL345_FIFO_STATUS 0x39
#define ADXL345_BW_1600 0xF // 1111
#define ADXL345_BW_800 0xE // 1110
#define ADXL345_BW_400 0xD // 1101
#define ADXL345_BW_200 0xC // 1100
#define ADXL345_BW_100 0xB // 1011
#define ADXL345_BW_50 0xA // 1010
#define ADXL345_BW_25 0x9 // 1001
#define ADXL345_BW_12 0x8 // 1000
#define ADXL345_BW_6 0x7 // 0111
#define ADXL345_BW_3 0x6 // 0110
/*
Interrupt PINs
INT1: 0
INT2: 1
*/
#define ADXL345_INT1_PIN 0x00
#define ADXL345_INT2_PIN 0x01
/*
Interrupt bit position
*/
#define ADXL345_INT_DATA_READY_BIT 0x07
#define ADXL345_INT_SINGLE_TAP_BIT 0x06
#define ADXL345_INT_DOUBLE_TAP_BIT 0x05
#define ADXL345_INT_ACTIVITY_BIT 0x04
#define ADXL345_INT_INACTIVITY_BIT 0x03
#define ADXL345_INT_FREE_FALL_BIT 0x02
#define ADXL345_INT_WATERMARK_BIT 0x01
#define ADXL345_INT_OVERRUNY_BIT 0x00
#define ADXL345_DATA_READY 0x07
#define ADXL345_SINGLE_TAP 0x06
#define ADXL345_DOUBLE_TAP 0x05
#define ADXL345_ACTIVITY 0x04
#define ADXL345_INACTIVITY 0x03
#define ADXL345_FREE_FALL 0x02
#define ADXL345_WATERMARK 0x01
#define ADXL345_OVERRUNY 0x00
#define ADXL345_OK 1 // no error
#define ADXL345_ERROR 0 // indicates error is predent
#define ADXL345_NO_ERROR 0 // initial state
#define ADXL345_READ_ERROR 1 // problem reading accel
#define ADXL345_BAD_ARG 2 // bad method argument

ADXL345::ADXL345()
{
	setDevice(0x53);

	status = ADXL345_OK;
	error_code = ADXL345_NO_ERROR;
	gains_[0] = 0.00376390;
	gains_[1] = 0.00376009;
	gains_[2] = 0.00349265;

	offset_[0] = 0;
	offset_[1] = 0;
	offset_[2] = 0;

	gains_[0] = 0.004;
	gains_[1] = 0.004;
	gains_[2] = 0.004;

}

void ADXL345::setup()
{
	powerOn();
}

void ADXL345::update()
{
	get_Gxyz(data_);
}

int ADXL345::getStatus()
{
}

int ADXL345::getId()
{
	byte data;
	readFromDevice(ADXL345_DEVID, 1, &data);
	return data;
}

void ADXL345::powerOn()
{
	Wire.begin(); // join i2c bus (address optional for master)
	// define rate
	writeToDevice(ADXL345_BW_RATE, 0x09);	// 50 Hz

	//Turning on the ADXL345
	//writeTo(ADXL345_POWER_CTL, 0x00);
	//writeTo(ADXL345_POWER_CTL, 0x10);
	writeToDevice(ADXL345_POWER_CTL, 0x08);
}

void ADXL345::readAccel(short* xyz)
{
	readFromDevice(ADXL345_DATAX0, ADXL345_TO_READ, buff_); //read the acceleration data from the ADXL345
	// each axis reading comes in 10 bit resolution, ie 2 bytes. Least Significat Byte first!!
	// thus we are converting both bytes in to one int
	xyz[0] = (((short)buff_[1]) << 8) | buff_[0];
	xyz[1] = (((short)buff_[3]) << 8) | buff_[2];
	xyz[2] = (((short)buff_[5]) << 8) | buff_[4];
}

void ADXL345::get_Gxyz(double *xyz)
{
	int i;
	short xyz_int[3];
	readAccel(xyz_int);
	for(i=0; i<3; i++) {
		xyz[i] = ((int)xyz_int[i] + offset_[i]) * gains_[i];
	}
}

// Writes val to address register on device
//void ADXL345::writeTo(byte address, byte val)
//{
//	Wire.beginTransmission(ADXL345_DEVICE); // start transmission to device
//	Wire.write(address); // send register address
//	Wire.write(val); // send value to write
//	Wire.endTransmission(); // end transmission
//}
//
//// Reads num bytes starting from address register on device in to buff_ array
//void ADXL345::readFrom(byte address, int num, byte buff_[])
//{
//	Wire.beginTransmission(ADXL345_DEVICE); // start transmission to device
//	Wire.write(address); // sends address to read from
//	Wire.endTransmission(); // end transmission
//	Wire.beginTransmission(ADXL345_DEVICE); // start transmission to device
//	Wire.requestFrom(ADXL345_DEVICE, num); // request 6 bytes from device
//	if (Wire.available() >= num) // device may send less than requested (abnormal)
//	{
//		for (int i=0; i<num; ++i) {
//			buff_[i] = Wire.read(); // receive a byte
//		}
//	}
//	else {
//		status = ADXL345_ERROR;
//		error_code = ADXL345_READ_ERROR;
//	}
//	Wire.endTransmission(); // end transmission
//}

// Gets the range setting and return it into rangeSetting
// it can be 2, 4, 8 or 16
void ADXL345::getRangeSetting(byte* rangeSetting)
{
	byte _b;
	readFromDevice(ADXL345_DATA_FORMAT, 1, &_b);
	*rangeSetting = _b & B00000011;
}

// Sets the range setting, possible values are: 2, 4, 8, 16
void ADXL345::setRangeSetting(int val)
{
	byte _s;
	byte _b;
	switch (val) {
	case 2:
		_s = B00000000;
		break;
	case 4:
		_s = B00000001;
		break;
	case 8:
		_s = B00000010;
		break;
	case 16:
		_s = B00000011;
		break;
	default:
		_s = B00000000;
	}
	readFromDevice(ADXL345_DATA_FORMAT, 1, &_b);
	_s |= (_b & B11101100);
	writeToDevice(ADXL345_DATA_FORMAT, _s);
}

// gets the state of the SELF_TEST bit
bool ADXL345::getSelfTestBit()
{
	return getRegisterBit(ADXL345_DATA_FORMAT, 7);
}

// Sets the SELF-TEST bit
// if set to 1 it applies a self-test force to the sensor causing a shift in the output data
// if set to 0 it disables the self-test force
void ADXL345::setSelfTestBit(bool selfTestBit)
{
	setRegisterBit(ADXL345_DATA_FORMAT, 7, selfTestBit);
}

// Gets the state of the SPI bit
bool ADXL345::getSpiBit()
{
	return getRegisterBit(ADXL345_DATA_FORMAT, 6);
}

// Sets the SPI bit
// if set to 1 it sets the device to 3-wire mode
// if set to 0 it sets the device to 4-wire SPI mode
void ADXL345::setSpiBit(bool spiBit)
{
	setRegisterBit(ADXL345_DATA_FORMAT, 6, spiBit);
}

// Gets the state of the INT_INVERT bit
bool ADXL345::getInterruptLevelBit()
{
	return getRegisterBit(ADXL345_DATA_FORMAT, 5);
}

// Sets the INT_INVERT bit
// if set to 0 sets the interrupts to active high
// if set to 1 sets the interrupts to active low
void ADXL345::setInterruptLevelBit(bool interruptLevelBit)
{
	setRegisterBit(ADXL345_DATA_FORMAT, 5, interruptLevelBit);
}

// Gets the state of the FULL_RES bit
bool ADXL345::getFullResBit()
{
	return getRegisterBit(ADXL345_DATA_FORMAT, 3);
}

// Sets the FULL_RES bit
// if set to 1, the device is in full resolution mode, where the output resolution increases with the
// g range set by the range bits to maintain a 4mg/LSB scal factor
// if set to 0, the device is in 10-bit mode, and the range buts determine the maximum g range
// and scale factor
void ADXL345::setFullResBit(bool fullResBit)
{
	setRegisterBit(ADXL345_DATA_FORMAT, 3, fullResBit);
}

// Gets the state of the justify bit
bool ADXL345::getJustifyBit()
{
	return getRegisterBit(ADXL345_DATA_FORMAT, 2);
}

// Sets the JUSTIFY bit
// if sets to 1 selects the left justified mode
// if sets to 0 selects right justified mode with sign extension
void ADXL345::setJustifyBit(bool justifyBit)
{
	setRegisterBit(ADXL345_DATA_FORMAT, 2, justifyBit);
}

// Sets the THRESH_TAP byte value
// it should be between 0 and 255
// the scale factor is 62.5 mg/LSB
// A value of 0 may result in undesirable behavior
void ADXL345::setTapThreshold(int tapThreshold)
{
	tapThreshold = constrain(tapThreshold,0,255);
	byte _b = byte (tapThreshold);
	writeToDevice(ADXL345_THRESH_TAP, _b);
}

// Gets the THRESH_TAP byte value
// return value is comprised between 0 and 255
// the scale factor is 62.5 mg/LSB
int ADXL345::getTapThreshold()
{
	byte _b;
	readFromDevice(ADXL345_THRESH_TAP, 1, &_b);
	return int (_b);
}

// set/get the gain for each axis in Gs / count
void ADXL345::setAxisGains(double *data)
{
	int i;
	for(i = 0; i < 3; i++) {
		gains_[i] = data[i];
	}
}

void ADXL345::getAxisGains(double *data)
{
	int i;
	for(i = 0; i < 3; i++){
		data[i] = gains_[i];
	}
}

// Sets the OFSX, OFSY and OFSZ bytes
// OFSX, OFSY and OFSZ are user offset adjustments in twos complement format with
// a scale factor of 15,6mg/LSB
// OFSX, OFSY and OFSZ should be comprised between
void ADXL345::setAxisOffset(int x, int y, int z)
{
	writeToDevice(ADXL345_OFSX, byte (x));
	writeToDevice(ADXL345_OFSY, byte (y));
	writeToDevice(ADXL345_OFSZ, byte (z));
}

// Gets the OFSX, OFSY and OFSZ bytes
void ADXL345::getAxisOffset(int* x, int* y, int*z)
{
	byte _b;
	readFromDevice(ADXL345_OFSX, 1, &_b);
	*x = int (_b);
	readFromDevice(ADXL345_OFSY, 1, &_b);
	*y = int (_b);
	readFromDevice(ADXL345_OFSZ, 1, &_b);
	*z = int (_b);
}

// Sets the DUR byte
// The DUR byte contains an unsigned time value representing the maximum time
// that an event must be above THRESH_TAP threshold to qualify as a tap event
// The scale factor is 625µs/LSB
// A value of 0 disables the tap/double tap funcitons. Max value is 255.
void ADXL345::setTapDuration(int tapDuration)
{
	tapDuration = constrain(tapDuration,0,255);
	byte _b = byte (tapDuration);
	writeToDevice(ADXL345_DUR, _b);
}

// Gets the DUR byte
int ADXL345::getTapDuration()
{
	byte _b;
	readFromDevice(ADXL345_DUR, 1, &_b);
	return int (_b);
}

// Sets the latency (latent register) which contains an unsigned time value
// representing the wait time from the detection of a tap event to the start
// of the time window, during which a possible second tap can be detected.
// The scale factor is 1.25ms/LSB. A value of 0 disables the double tap function.
// It accepts a maximum value of 255.
void ADXL345::setDoubleTapLatency(int doubleTapLatency)
{
	byte _b = byte (doubleTapLatency);
	writeToDevice(ADXL345_LATENT, _b);
}

// Gets the Latent value
int ADXL345::getDoubleTapLatency()
{
	byte _b;
	readFromDevice(ADXL345_LATENT, 1, &_b);
	return int (_b);
}

// Sets the Window register, which contains an unsigned time value representing
// the amount of time after the expiration of the latency time (Latent register)
// during which a second valud tap can begin. The scale factor is 1.25ms/LSB. A
// value of 0 disables the double tap function. The maximum value is 255.
void ADXL345::setDoubleTapWindow(int doubleTapWindow)
{
	doubleTapWindow = constrain(doubleTapWindow,0,255);
	byte _b = byte (doubleTapWindow);
	writeToDevice(ADXL345_WINDOW, _b);
}

// Gets the Window register
int ADXL345::getDoubleTapWindow()
{
	byte _b;
	readFromDevice(ADXL345_WINDOW, 1, &_b);
	return int (_b);
}

// Sets the THRESH_ACT byte which holds the threshold value for detecting activity.
// The data format is unsigned, so the magnitude of the activity event is compared
// with the value is compared with the value in the THRESH_ACT register. The scale
// factor is 62.5mg/LSB. A value of 0 may result in undesirable behavior if the
// activity interrupt is enabled. The maximum value is 255.
void ADXL345::setActivityThreshold(int activityThreshold)
{
	activityThreshold = constrain(activityThreshold,0,255);
	byte _b = byte (activityThreshold);
	writeToDevice(ADXL345_THRESH_ACT, _b);
}

// Gets the THRESH_ACT byte
int ADXL345::getActivityThreshold()
{
	byte _b;
	readFromDevice(ADXL345_THRESH_ACT, 1, &_b);
	return int (_b);
}

// Sets the THRESH_INACT byte which holds the threshold value for detecting inactivity.
// The data format is unsigned, so the magnitude of the inactivity event is compared
// with the value is compared with the value in the THRESH_INACT register. The scale
// factor is 62.5mg/LSB. A value of 0 may result in undesirable behavior if the
// inactivity interrupt is enabled. The maximum value is 255.
void ADXL345::setInactivityThreshold(int inactivityThreshold)
{
	inactivityThreshold = constrain(inactivityThreshold,0,255);
	byte _b = byte (inactivityThreshold);
	writeToDevice(ADXL345_THRESH_INACT, _b);
}

// Gets the THRESH_INACT byte
int ADXL345::getInactivityThreshold()
{
	byte _b;
	readFromDevice(ADXL345_THRESH_INACT, 1, &_b);
	return int (_b);
}

// Sets the TIME_INACT register, which contains an unsigned time value representing the
// amount of time that acceleration must be less thant the value in the THRESH_INACT
// register for inactivity to be declared. The scale factor is 1sec/LSB. The value must
// be between 0 and 255.
void ADXL345::setTimeInactivity(int timeInactivity)
{
	timeInactivity = constrain(timeInactivity,0,255);
	byte _b = byte (timeInactivity);
	writeToDevice(ADXL345_TIME_INACT, _b);
}

// Gets the TIME_INACT register
int ADXL345::getTimeInactivity()
{
	byte _b;
	readFromDevice(ADXL345_TIME_INACT, 1, &_b);
	return int (_b);
}

// Sets the THRESH_FF register which holds the threshold value, in an unsigned format, for
// free-fall detection. The root-sum-square (RSS) value of all axes is calculated and
// compared whith the value in THRESH_FF to determine if a free-fall event occured. The
// scale factor is 62.5mg/LSB. A value of 0 may result in undesirable behavior if the free-fall
// interrupt is enabled. The maximum value is 255.
void ADXL345::setFreeFallThreshold(int freeFallThreshold)
{
	freeFallThreshold = constrain(freeFallThreshold,0,255);
	byte _b = byte (freeFallThreshold);
	writeToDevice(ADXL345_THRESH_FF, _b);
}

// Gets the THRESH_FF register.
int ADXL345::getFreeFallThreshold()
{
	byte _b;
	readFromDevice(ADXL345_THRESH_FF, 1, &_b);
	return int (_b);
}

// Sets the TIME_FF register, which holds an unsigned time value representing the minimum
// time that the RSS value of all axes must be less than THRESH_FF to generate a free-fall
// interrupt. The scale factor is 5ms/LSB. A value of 0 may result in undesirable behavior if
// the free-fall interrupt is enabled. The maximum value is 255.
void ADXL345::setFreeFallDuration(int freeFallDuration)
{
	freeFallDuration = constrain(freeFallDuration,0,255);
	byte _b = byte (freeFallDuration);
	writeToDevice(ADXL345_TIME_FF, _b);
}

// Gets the TIME_FF register.
int ADXL345::getFreeFallDuration()
{
	byte _b;
	readFromDevice(ADXL345_TIME_FF, 1, &_b);
	return int (_b);
}

bool ADXL345::isActivityXEnabled()
{
	return getRegisterBit(ADXL345_ACT_INACT_CTL, 6);
}

bool ADXL345::isActivityYEnabled()
{
	return getRegisterBit(ADXL345_ACT_INACT_CTL, 5);
}

bool ADXL345::isActivityZEnabled()
{
	return getRegisterBit(ADXL345_ACT_INACT_CTL, 4);
}

bool ADXL345::isInactivityXEnabled()
{
	return getRegisterBit(ADXL345_ACT_INACT_CTL, 2);
}

bool ADXL345::isInactivityYEnabled()
{
	return getRegisterBit(ADXL345_ACT_INACT_CTL, 1);
}

bool ADXL345::isInactivityZEnabled()
{
	return getRegisterBit(ADXL345_ACT_INACT_CTL, 0);
}

void ADXL345::setActivityX(bool state)
{
	setRegisterBit(ADXL345_ACT_INACT_CTL, 6, state);
}

void ADXL345::setActivityY(bool state)
{
	setRegisterBit(ADXL345_ACT_INACT_CTL, 5, state);
}

void ADXL345::setActivityZ(bool state)
{
	setRegisterBit(ADXL345_ACT_INACT_CTL, 4, state);
}

void ADXL345::setInactivityX(bool state)
{
	setRegisterBit(ADXL345_ACT_INACT_CTL, 2, state);
}

void ADXL345::setInactivityY(bool state)
{
	setRegisterBit(ADXL345_ACT_INACT_CTL, 1, state);
}

void ADXL345::setInactivityZ(bool state)
{
	setRegisterBit(ADXL345_ACT_INACT_CTL, 0, state);
}

bool ADXL345::isActivityAc()
{
	return getRegisterBit(ADXL345_ACT_INACT_CTL, 7);
}

bool ADXL345::isInactivityAc()
{
	return getRegisterBit(ADXL345_ACT_INACT_CTL, 3);
}

void ADXL345::setActivityAc(bool state)
{
	setRegisterBit(ADXL345_ACT_INACT_CTL, 7, state);
}

void ADXL345::setInactivityAc(bool state)
{
	setRegisterBit(ADXL345_ACT_INACT_CTL, 3, state);
}

bool ADXL345::getSuppressBit()
{
	return getRegisterBit(ADXL345_TAP_AXES, 3);
}

void ADXL345::setSuppressBit(bool state)
{
	setRegisterBit(ADXL345_TAP_AXES, 3, state);
}

bool ADXL345::isTapDetectionOnX()
{
	return getRegisterBit(ADXL345_TAP_AXES, 2);
}

void ADXL345::setTapDetectionOnX(bool state)
{
	setRegisterBit(ADXL345_TAP_AXES, 2, state);
}

bool ADXL345::isTapDetectionOnY()
{
	return getRegisterBit(ADXL345_TAP_AXES, 1);
}

void ADXL345::setTapDetectionOnY(bool state)
{
	setRegisterBit(ADXL345_TAP_AXES, 1, state);
}

bool ADXL345::isTapDetectionOnZ()
{
	return getRegisterBit(ADXL345_TAP_AXES, 0);
}

void ADXL345::setTapDetectionOnZ(bool state)
{
	setRegisterBit(ADXL345_TAP_AXES, 0, state);
}

bool ADXL345::isActivitySourceOnX()
{
	return getRegisterBit(ADXL345_ACT_TAP_STATUS, 6);
}

bool ADXL345::isActivitySourceOnY()
{
	return getRegisterBit(ADXL345_ACT_TAP_STATUS, 5);
}

bool ADXL345::isActivitySourceOnZ()
{
	return getRegisterBit(ADXL345_ACT_TAP_STATUS, 4);
}

bool ADXL345::isTapSourceOnX()
{
	return getRegisterBit(ADXL345_ACT_TAP_STATUS, 2);
}

bool ADXL345::isTapSourceOnY()
{
	return getRegisterBit(ADXL345_ACT_TAP_STATUS, 1);
}

bool ADXL345::isTapSourceOnZ()
{
	return getRegisterBit(ADXL345_ACT_TAP_STATUS, 0);
}

bool ADXL345::isAsleep()
{
	return getRegisterBit(ADXL345_ACT_TAP_STATUS, 3);
}

bool ADXL345::isLowPower()
{
	return getRegisterBit(ADXL345_BW_RATE, 4);
}

void ADXL345::setLowPower(bool state)
{
	setRegisterBit(ADXL345_BW_RATE, 4, state);
}

double ADXL345::getRate()
{
	byte _b;
	readFromDevice(ADXL345_BW_RATE, 1, &_b);
	_b &= B00001111;
	return (pow(2,((int) _b)-6)) * 6.25;
}

void ADXL345::setRate(double rate)
{
	byte _b,_s;
	int v = (int) (rate / 6.25);
	int r = 0;
	while (v >>= 1)
	{
		r++;
	}
	if (r <= 9) {
		readFromDevice(ADXL345_BW_RATE, 1, &_b);
		_s = (byte) (r + 6) | (_b & B11110000);
		writeToDevice(ADXL345_BW_RATE, _s);
	}
}

void ADXL345::set_bw(byte bw_code)
{
	if((bw_code < ADXL345_BW_3) || (bw_code > ADXL345_BW_1600)){
		status = false;
		error_code = ADXL345_BAD_ARG;
	}
	else{
		writeToDevice(ADXL345_BW_RATE, bw_code);
	}
}

byte ADXL345::get_bw_code()
{
	byte bw_code;
	readFromDevice(ADXL345_BW_RATE, 1, &bw_code);
	return bw_code;
}

//Used to check if action was triggered in interrupts
//Example triggered(interrupts, ADXL345_SINGLE_TAP);
bool ADXL345::triggered(byte interrupts, int mask)
{
	return ((interrupts >> mask) & 1);
}

/*
ADXL345_DATA_READY
ADXL345_SINGLE_TAP
ADXL345_DOUBLE_TAP
ADXL345_ACTIVITY
ADXL345_INACTIVITY
ADXL345_FREE_FALL
ADXL345_WATERMARK
ADXL345_OVERRUNY
*/
byte ADXL345::getInterruptSource()
{
	byte _b;
	readFromDevice(ADXL345_INT_SOURCE, 1, &_b);
	return _b;
}

bool ADXL345::getInterruptSource(byte interruptBit)
{
	return getRegisterBit(ADXL345_INT_SOURCE,interruptBit);
}

bool ADXL345::getInterruptMapping(byte interruptBit)
{
	return getRegisterBit(ADXL345_INT_MAP,interruptBit);
}

// Set the mapping of an interrupt to pin1 or pin2
// eg: setInterruptMapping(ADXL345_INT_DOUBLE_TAP_BIT,ADXL345_INT2_PIN);
void ADXL345::setInterruptMapping(byte interruptBit, bool interruptPin)
{
	setRegisterBit(ADXL345_INT_MAP, interruptBit, interruptPin);
}

bool ADXL345::isInterruptEnabled(byte interruptBit)
{
	return getRegisterBit(ADXL345_INT_ENABLE,interruptBit);
}

void ADXL345::setInterrupt(byte interruptBit, bool state)
{
	setRegisterBit(ADXL345_INT_ENABLE, interruptBit, state);
}

void ADXL345::setRegisterBit(byte regAdress, int bitPos, bool state)
{
	byte _b;
	readFromDevice(regAdress, 1, &_b);
	if (state) {
		_b |= (1 << bitPos); // forces nth bit of _b to be 1. all other bits left alone.
	}
	else {
		_b &= ~(1 << bitPos); // forces nth bit of _b to be 0. all other bits left alone.
	}
	writeToDevice(regAdress, _b);
}

bool ADXL345::getRegisterBit(byte regAdress, int bitPos)
{
	byte _b;
	readFromDevice(regAdress, 1, &_b);
	return ((_b >> bitPos) & 1);
}

// print all register value to the serial ouptut, which requires it to be setup
// this can be used to manually to check the current configuration of the device
void ADXL345::printAllRegister()
{
	byte _b;
	Serial.print("0x00: ");
	readFromDevice(0x00, 1, &_b);
	print_byte(_b);
	Serial.println("");
	int i;
	for (i=29;i<=57;i++){
		Serial.print("0x");
		Serial.print(i, HEX);
		Serial.print(": ");
		readFromDevice(i, 1, &_b);
		print_byte(_b);
		Serial.println("");
	}
}

void ADXL345::print_byte(byte val)
{
	int i;
	Serial.print("B");
	for(i=7; i>=0; i--){
		Serial.print(val >> i & 1, BIN);
	}
}






/*


#include <Wire.h>
#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37
int ADXAddress = 0xA7 >> 1; // the default 7-bit slave address
int reading = 0;
int val=0;
int X0,X1,X_out;
int Y0,Y1,Y_out;
int Z1,Z0,Z_out;
double Xg,Yg,Zg;
void setup()
{
Wire.begin();
Serial.begin(9600);
delay(100);
// enable to measute g data
Wire.beginTransmission(ADXAddress);
Wire.write(Register_2D);
Wire.write(8); //measuring enable
Wire.endTransmission(); // stop transmitting
}
void loop()
{
//--------------X
Wire.beginTransmission(ADXAddress); // transmit to device
Wire.write(Register_X0);
Wire.write(Register_X1);
Wire.endTransmission();
Wire.requestFrom(ADXAddress,2);
if(Wire.available()<=2)
{
X0 = Wire.read();
X1 = Wire.read();
X1=X1<<8;
X_out=X0+X1;
}
//------------------Y
Wire.beginTransmission(ADXAddress); // transmit to device
Wire.write(Register_Y0);
Wire.write(Register_Y1);
Wire.endTransmission();
Wire.requestFrom(ADXAddress,2);
if(Wire.available()<=2)
{
Y0 = Wire.read();
Y1 = Wire.read();
Y1=Y1<<8;
Y_out=Y0+Y1;
}
//------------------Z
Wire.beginTransmission(ADXAddress); // transmit to device
Wire.write(Register_Z0);
Wire.write(Register_Z1);
Wire.endTransmission();
Wire.requestFrom(ADXAddress,2);
if(Wire.available()<=2)
{
Z0 = Wire.read();
Z1 = Wire.read();
Z1=Z1<<8;
Z_out=Z0+Z1;
}
//
Xg=X_out/256.0;
Yg=Y_out/256.0;
Zg=Z_out/256.0;
Serial.print("X= ");
Serial.print(Xg);
Serial.print(" ");
Serial.print("Y= ");
Serial.print(Yg);
Serial.print(" ");
Serial.print("Z= ");
Serial.print(Zg);
Serial.println(" ");
delay(200);
Serial.print(Xg);
delay(200);
}







//Arduino 1.0+ Only!
//Arduino 1.0+ Only!
#include <Wire.h>
#include <ADXL345.h>
ADXL345 adxl; //variable adxl is an instance of the ADXL345 library
void setup(){
Serial.begin(9600);
adxl.powerOn();
//set activity/ inactivity thresholds (0-255)
adxl.setActivityThreshold(75); //62.5mg per increment
adxl.setInactivityThreshold(75); //62.5mg per increment
adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
//look of activity movement on this axes - 1 == on; 0 == off
adxl.setActivityX(1);
adxl.setActivityY(1);
adxl.setActivityZ(1);
//look of inactivity movement on this axes - 1 == on; 0 == off
adxl.setInactivityX(1);
adxl.setInactivityY(1);
adxl.setInactivityZ(1);
//look of tap movement on this axes - 1 == on; 0 == off
adxl.setTapDetectionOnX(1);
adxl.setTapDetectionOnY(1);
adxl.setTapDetectionOnZ(1);
//set values for what is a tap, and what is a double tap (0-255)
adxl.setTapThreshold(50); //62.5mg per increment
adxl.setTapDuration(15); //625µs per increment
adxl.setDoubleTapLatency(80); //1.25ms per increment
adxl.setDoubleTapWindow(200); //1.25ms per increment
//set values for what is considered freefall (0-255)
//adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
//adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
//setting all interupts to take place on int pin 1
//I had issues with int pin 2, was unable to reset it
adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT, ADXL345_INT1_PIN );
adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT, ADXL345_INT1_PIN );
adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT, ADXL345_INT1_PIN );
adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT, ADXL345_INT1_PIN );
adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT, ADXL345_INT1_PIN );
//register interupt actions - 1 == on; 0 == off
adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT, 1);
adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT, 1);
adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);
}
void loop(){
//Boring accelerometer stuff
int x,y,z;
adxl.readAccel(&x, &y, &z); //read the accelerometer values and store them in variables x,y,z
// Output x,y,z values - Commented out
//Serial.print(x);
//Serial.print(y);
//Serial.println(z);
//Fun Stuff!
//read interrupts source and look for triggerd actions
//getInterruptSource clears all triggered actions after returning value
//so do not call again until you need to recheck for triggered actions
byte interrupts = adxl.getInterruptSource();
// freefall
if(adxl.triggered(interrupts, ADXL345_FREE_FALL)){
Serial.println("freefall");
//add code here to do when freefall is sensed
}
//inactivity
if(adxl.triggered(interrupts, ADXL345_INACTIVITY)){
Serial.println("inactivity");
//add code here to do when inactivity is sensed
}
//activity
if(adxl.triggered(interrupts, ADXL345_ACTIVITY)){
Serial.println("activity");
//add code here to do when activity is sensed
}
//double tap
if(adxl.triggered(interrupts, ADXL345_DOUBLE_TAP)){
Serial.println("double tap");
//add code here to do when a 2X tap is sensed
}
//tap
if(adxl.triggered(interrupts, ADXL345_SINGLE_TAP)){
if(adxl.isTapSourceOnX()){
Serial.println("tap X");
}
if(adxl.isTapSourceOnY()){
Serial.println("tap Y");
}
if(adxl.isTapSourceOnZ()){
Serial.println("tap Z");
}
//add code here to do when a tap is sensed
}
}























*/













