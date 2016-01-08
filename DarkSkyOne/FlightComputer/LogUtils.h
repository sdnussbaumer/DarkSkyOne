/*
Trace Logging class.
Copyright (C) 2014 Sascha Nussbaumer
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

#ifndef LOGUTILS_H_
#define LOGUTILS_H_

#include <Arduino.h>

class LogUtils {

public:
	enum LogLevel { off, error, warning, information, trace1, trace2, trace3 };

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

