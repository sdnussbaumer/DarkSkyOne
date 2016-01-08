/*
GY80 Task class.
Copyright (C) 2016 Sascha Nussbaumer
All rights reserved.

Parts of this class are implemented based on the examples of
Adafruit Industries.

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

#ifndef GY80TASK_h
#define GY80TASK_h

class GY80Task
{
private:
	//singleton variable
	static GY80Task* _instance;

	void setupBMP085();
	void setupADXL345();
	void setupHMC5883();

public:

	GY80Task();

	static GY80Task* instance ()
    {
	   if (!_instance)
		   _instance = new GY80Task ();
	   return _instance;
    }

	GY80Task& getGY80Task() {return *_instance;}

	void setup();
	void handleGY80();

    void printPressure();
	void printAccelerator();
	void printGyroscope();
	void printCompass();

};

#endif
