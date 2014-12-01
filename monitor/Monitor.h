/*
 * Monitor.h
 *
 *  Created on: 17.10.2014
 *      Author: san
 */

#ifndef MONITOR_H_
#define MONITOR_H_

#include "Arduino.h"
#include "TinyGPS++.h"

class MonitorHandler {
public:
	enum State {
	  State_main_display,
	  State_main_input,
	  State_inflight_display,
	  State_inflight_input,
	  State_gps_display,
	  State_gps_input
	};

	MonitorHandler();
	virtual ~MonitorHandler();

	static MonitorHandler* instance ()
    {
	   if (!_instance)
		   _instance = new MonitorHandler ();
	   return _instance;
    }

	void handleState();
	void handleGPS();
private:
	State state_g;
	TinyGPSPlus *tinyGPS;
	unsigned long timebase_g;
	String nmeaTerm;
	bool nmeaTestMode;

	void clear();
	void inflight_display();
	void inflight_input();
	void gps_display();
	void gps_input();
	void main_display();
	void main_input();
	static MonitorHandler* _instance;
};

#endif /* MONITOR_H_ */
