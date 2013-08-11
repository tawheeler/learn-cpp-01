/*
========================================================================

	Handles error and standard system output 
	outputs to several different log files

========================================================================
*/

#include "LogManager.h"
#include <assert.h>
#include <stdio.h>   // for va_list et al
#include <windows.h> // for OutputDebugString

void LogManager::StartUp() {
	debug = true;
	appLog.open( "applog.txt" );
	clientLog.open( "clntlog.txt" );
	serverLog.open( "srvrlog.txt" );
	Write( LogManager::LOG_APP, "Log Manager created\n" );
}

void LogManager::ShutDown() {
	appLog.close();
	clientLog.close();
	serverLog.close();
}

LogManager& LogManager::GetInstance() {
	static LogManager* lmSingleton = NULL;
	if ( lmSingleton == NULL ) {
		lmSingleton = new LogManager();
	}
	assert( lmSingleton );
	return *lmSingleton;
}

int LogManager::Write( int target, const char* format, ... ) {
	va_list argList;
	va_start( argList, format );
	int charsWritten = DebugPrintF( target, format, argList );
	va_end( argList );
	return charsWritten;
}

int LogManager::DebugPrintF( int target, const char* format, va_list argList ) {
	const long MAX_CHARS = 1023;
	static char s_buffer[ MAX_CHARS + 1 ];
	int charsWritten = vsnprintf( s_buffer, MAX_CHARS, format, argList );
	int len = charsWritten;
	if ( len > 0 ) {
		if ( len > MAX_CHARS ) {
			len = MAX_CHARS;
		} 
		s_buffer[ len ] = '\0'; // be sure to NIL-terminate

		// Now that we have a formatted string, 
		// write to the appropriate location

		switch (target) {
			case ( LogManager::LOG_APP ):
				appLog.write( s_buffer, len );
				appLog.flush();
				break;
			case ( LogManager::LOG_CLIENT ):
				clientLog.write( s_buffer, len );
				clientLog.flush();
				break;
			case ( LogManager::LOG_SERVER ):
				serverLog.write( s_buffer, len );
				serverLog.flush();
				break;
			case ( LogManager::LOG_USER ):
				//TODO: have a way to display to the user terminal
				break;
			default:
				break;
		}

		if ( debug ) {
			OutputDebugString( s_buffer );
		}
	
	}
	return charsWritten;
}