/*
========================================================================

	Handles all chambers.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "ChamberManager.h"
#include <assert.h>

using namespace MysticDave;

void ChamberManager::StartUp() {
    curChamber = 0;
	// TODO: load chambers from JSON file or something
}

void ChamberManager::ShutDown() {
	
	// free chambers
	std::map < int, Chamber * >::iterator iter;
	for ( iter = chamberMap.begin(); iter != chamberMap.end(); ) {
        (iter->second)->Cleanup();
		delete (iter->second);
		iter = chamberMap.erase(iter);
	}
	chamberMap.clear();
}

ChamberManager& ChamberManager::GetInstance() {
	static ChamberManager* lmSingleton = NULL;
	if ( lmSingleton == NULL ) {
		lmSingleton = new ChamberManager();
	}
	assert( lmSingleton );
	return *lmSingleton;
}

Chamber * ChamberManager::GetChamber( const int uid ) {
	std::map < int, Chamber * >::iterator iter = chamberMap.find( uid );
	Chamber * retval;
	if ( iter != chamberMap.end() ) {
	   //element found;
	   retval = iter->second;
	} else { // not found!
		retval = 0;
	}
	return retval;
}

Chamber * ChamberManager::GetCurrentChamber() {
    return curChamber;
}

void ChamberManager::SetCurrentChamber( Chamber * C ) {
    curChamber = C;
}