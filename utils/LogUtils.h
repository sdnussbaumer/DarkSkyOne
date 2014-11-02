/*
 * LogUtils.h
 *
 *  Created on: 23.06.2014
 *      Author: san
 */

#ifndef LOGUTILS_H_
#define LOGUTILS_H_

#include "Arduino.h"
#include "SCoop.h"

class LogUtils {

public:
	enum LogLevel { error, warning, information, trace1, trace2, trace3 };

    LogUtils ();
    LogUtils ( const LogUtils& );
    ~LogUtils ();

	static LogUtils* instance ()
    {
	   if (!_instance)
		   _instance = new LogUtils ();
	   return _instance;
    }

	void setLogLevel(LogLevel level);
	LogLevel getLogLevel();

	void processLogs();
	void logTrace(LogLevel level, const char* msg);
	void logTrace(LogLevel level, const String msg);

private:
	static LogUtils* _instance;
    LogLevel loglevel;

	String leadingZero(int nr);
};
#endif /* LOGUTILS_H_ */

