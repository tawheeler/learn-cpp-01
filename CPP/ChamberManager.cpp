/*
========================================================================

	Handles all chambers.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "ChamberManager.h"
#include "LogManager.h"
#include <assert.h>

using namespace MysticDave;

void ChamberManager::StartUp() {
    curChamber = 0;
	// TODO: load chambers from JSON file or something
    player = new PlayerEntity();
    // TODO: load last save or something. Move player to a GameManager or something?
}

void ChamberManager::ShutDown() {
	
    // clean up the player
    player->Cleanup();
    delete player;

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
    assert( iter != chamberMap.end() );
	return iter->second;
}

Chamber * ChamberManager::GetCurrentChamber() {
    return curChamber;
}

void ChamberManager::SetCurrentChamber( const int uid ) {
    //curChamber = C;
    
    if ( HasChamber( uid ) ) {
        // TODO: call some sort of reset() function?
        (LogManager::GetInstance()).Write( LogManager::LOG_APP, "ChamberManager::SetCurrentChamber: Switching to chamber %d\n", uid );
        curChamber = GetChamber( uid );
    } else {
        (LogManager::GetInstance()).Write( LogManager::LOG_APP, "ChamberManager::SetCurrentChamber: Failed to switch to chamber %d\n", uid );
    }
}

bool ChamberManager::HasChamber( const int uid ) {
    std::map < int, Chamber * >::iterator iter = chamberMap.find( uid );
    return ( iter != chamberMap.end() );
}

void ChamberManager::AddChamber( Chamber * chamber ) {
    if ( !HasChamber( chamber->GetUID() ) ) {
        chamberMap[ chamber->GetUID() ] = chamber;
    }
}

PlayerEntity * ChamberManager::GetPlayer() {
    return player;
}