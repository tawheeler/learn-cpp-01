/*
========================================================================

	Handles error and standard system output 
	outputs to several different log files

========================================================================
*/

#pragma once

#include <iostream>
#include <fstream>

class LogManager {
public:
	// LOG_APP    - Kernel-level messages and other misc messages
	// LOG_CLIENT - video, sound, and player end tasks
	// LOG_SERVER - connections being opened and closed, and games being started and stopped, and ai/physics messages
	// LOG_USER   - used to display the errors to a user in a dialog box
							
	enum KEYS{LOG_APP, LOG_CLIENT, LOG_SERVER, LOG_USER};

	void					StartUp();
	void					ShutDown();
	static LogManager&	    GetInstance();
	int						Write( int target, const char* format, ... );

protected:
	std::ofstream			appLog;
	std::ofstream			clientLog;
	std::ofstream			serverLog;

private:
							LogManager() {};
							LogManager( LogManager const& );  //do not implement
	void operator = (LogManager const&); // don't implement

	bool					debug;      //if true, write all messages to the screen as well
	int						DebugPrintF( int target, const char* format, va_list argList );
};