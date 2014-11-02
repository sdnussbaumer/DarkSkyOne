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
	void setGPS(TinyGPSPlus& gps);
	void handleState();
	void handleGPS();
private:
	void clear();
	void inflight_display();
	void inflight_input();
	void gps_display();
	void gps_input();
	void main_display();
	void main_input();
};

#endif /* MONITOR_H_ */
