/*
 * LogUtils.h
 *
 *  Created on: 23.06.2014
 *      Author: san
 */

#ifndef LOGUTILS_H_
#define LOGUTILS_H_

#include "Arduino.h"

class LogUtils {

public:
	enum LogLevel { error, warning, information, trace1, trace2, trace3 };

	LogUtils();
	virtual ~LogUtils();

	void setLogLevel(LogLevel level);
	LogLevel getLogLevel();

	void processLogs();
	void logTrace(LogLevel level, const char* msg);

private:
	String leadingZero(int nr);

};

#endif /* LOGUTILS_H_ */
