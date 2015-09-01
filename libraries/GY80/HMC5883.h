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

#ifndef HMC5883_h
#define HMC5883_h
#include <I2CSensor.h>



class HMC5883 : public I2CSensor
{
private:
	short idata_[3];
	double data_[3];
	double gain_[3];

public:

	HMC5883();

	void setup();
	void update();

	int getStatus();
	int getId();

	double* getData() {return data_;}

};

#endif
