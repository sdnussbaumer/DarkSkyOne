/*
L3G4200D - gyro module.
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

#ifndef L3G4200D_h
#define L3G4200D_h
#include <SCoop.h>
#include <I2CSensor.h>

// register addresses
#define L3G4200D_WHO_AM_I 0x0F
#define L3G4200D_CTRL_REG1 0x20
#define L3G4200D_CTRL_REG2 0x21
#define L3G4200D_CTRL_REG3 0x22
#define L3G4200D_CTRL_REG4 0x23
#define L3G4200D_CTRL_REG5 0x24
#define L3G4200D_REFERENCE 0x25
#define L3G4200D_OUT_TEMP 0x26
#define L3G4200D_STATUS_REG 0x27
#define L3G4200D_OUT_X_L 0x28
#define L3G4200D_OUT_X_H 0x29
#define L3G4200D_OUT_Y_L 0x2A
#define L3G4200D_OUT_Y_H 0x2B
#define L3G4200D_OUT_Z_L 0x2C
#define L3G4200D_OUT_Z_H 0x2D
#define L3G4200D_FIFO_CTRL_REG 0x2E
#define L3G4200D_FIFO_SRC_REG 0x2F
#define L3G4200D_INT1_CFG 0x30
#define L3G4200D_INT1_SRC 0x31
#define L3G4200D_INT1_THS_XH 0x32
#define L3G4200D_INT1_THS_XL 0x33
#define L3G4200D_INT1_THS_YH 0x34
#define L3G4200D_INT1_THS_YL 0x35
#define L3G4200D_INT1_THS_ZH 0x36
#define L3G4200D_INT1_THS_ZL 0x37
#define L3G4200D_INT1_DURATION 0x38

class L3G4200D : public I2CSensor
{
private:
	double data_[3];
	double gain_[3];
	double temp_;

	void enableDefault(void);
	//void writeReg(byte reg, byte value);
	//byte readReg(byte reg);
	void read(void);

public:
	L3G4200D();

	void setup();
	void update();

	double* getData() {return data_;}
	
	double getTemperature() {return temp_;}
};
#endif
