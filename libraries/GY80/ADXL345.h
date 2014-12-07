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
#ifndef ADXL345_h
#define ADXL345_h
#include <I2CSensor.h>

class ADXL345 : public I2CSensor
{
private:
	byte	buff_[6] ; //6 bytes buffer for saving data read from the device
	int		offset_[3];
	double	data_[3];
	double	gains_[3]; // counts to Gs
	bool	status; // set when error occurs
	// see error code for details
	byte	error_code; // Initial state

	//void writeTo(byte address, byte val);
	//void readFrom(byte address, int num, byte buff[]);
	void setRegisterBit(byte regAdress, int bitPos, bool state);
	bool getRegisterBit(byte regAdress, int bitPos);

	void powerOn();
	void readAccel(short* xyx);
	void get_Gxyz(double *xyz);
	void setTapThreshold(int tapThreshold);
	int getTapThreshold();
	void setAxisGains(double *_gains);
	void getAxisGains(double *_gains);
	void setAxisOffset(int x, int y, int z);
	void getAxisOffset(int* x, int* y, int*z);
	void setTapDuration(int tapDuration);
	int getTapDuration();
	void setDoubleTapLatency(int doubleTapLatency);
	int getDoubleTapLatency();
	void setDoubleTapWindow(int doubleTapWindow);
	int getDoubleTapWindow();
	void setActivityThreshold(int activityThreshold);
	int getActivityThreshold();
	void setInactivityThreshold(int inactivityThreshold);
	int getInactivityThreshold();
	void setTimeInactivity(int timeInactivity);
	int getTimeInactivity();
	void setFreeFallThreshold(int freeFallthreshold);
	int getFreeFallThreshold();
	void setFreeFallDuration(int freeFallDuration);
	int getFreeFallDuration();
	bool isActivityXEnabled();
	bool isActivityYEnabled();
	bool isActivityZEnabled();
	bool isInactivityXEnabled();
	bool isInactivityYEnabled();
	bool isInactivityZEnabled();
	bool isActivityAc();
	bool isInactivityAc();
	void setActivityAc(bool state);
	void setInactivityAc(bool state);
	bool getSuppressBit();
	void setSuppressBit(bool state);
	bool isTapDetectionOnX();
	void setTapDetectionOnX(bool state);
	bool isTapDetectionOnY();
	void setTapDetectionOnY(bool state);
	bool isTapDetectionOnZ();
	void setTapDetectionOnZ(bool state);
	void setActivityX(bool state);
	void setActivityY(bool state);
	void setActivityZ(bool state);
	void setInactivityX(bool state);
	void setInactivityY(bool state);
	void setInactivityZ(bool state);
	bool isActivitySourceOnX();
	bool isActivitySourceOnY();
	bool isActivitySourceOnZ();
	bool isTapSourceOnX();
	bool isTapSourceOnY();
	bool isTapSourceOnZ();
	bool isAsleep();
	bool isLowPower();
	void setLowPower(bool state);
	double getRate();
	void setRate(double rate);
	void set_bw(byte bw_code);
	byte get_bw_code();
	bool triggered(byte interrupts, int mask);
	byte getInterruptSource();
	bool getInterruptSource(byte interruptBit);
	bool getInterruptMapping(byte interruptBit);
	void setInterruptMapping(byte interruptBit, bool interruptPin);
	bool isInterruptEnabled(byte interruptBit);
	void setInterrupt(byte interruptBit, bool state);
	void getRangeSetting(byte* rangeSetting);
	void setRangeSetting(int val);
	bool getSelfTestBit();
	void setSelfTestBit(bool selfTestBit);
	bool getSpiBit();
	void setSpiBit(bool spiBit);
	bool getInterruptLevelBit();
	void setInterruptLevelBit(bool interruptLevelBit);
	bool getFullResBit();
	void setFullResBit(bool fullResBit);
	bool getJustifyBit();
	void setJustifyBit(bool justifyBit);
	void printAllRegister();

	void print_byte(byte val);

public:
	ADXL345();

	void setup();
	void update();

	int getStatus();
	int getId();

	double* getData() {return data_;}
};
#endif