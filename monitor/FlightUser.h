/*
Flight Display - user interface.
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

#ifndef FLIGHTUSER_h
#define FLIGHTUSER_h

#include <GY80Task.h>
#include <TinyGPS++.h>

class FlightUser {
public:
	enum State {
	  main_display,
	  main_input,
	  inflight_display,
	  inflight_input,
	  gps_display,
	  gps_input,
	  sensor_display,
	  sensor_input
	};



private:
	GY80Task&		gy80_;
	TinyGPSPlus&    gps_;
	State			state_;
	unsigned long	timebase_;
	unsigned long 	sensor_read_delay_;

public:
	FlightUser(GY80Task&, TinyGPSPlus&);

	void setup();
	void loop();
	void clearScreen();
	void mainDisplay();
	void mainInput();
	void inflightDisplay();
	void inflightInput();
	void gpsDisplay();
	void gpsInput();
	void sensorDisplay();
	void sensorInput();

};

#endif
