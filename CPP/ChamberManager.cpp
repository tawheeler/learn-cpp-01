/*
========================================================================

	Handles all chambers.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "ChamberManager.h"
#include "LogManager.h"
#include "jsoncons/json.hpp"
#include <assert.h>

using jsoncons::json;
using namespace MysticDave;

void ChamberManager::StartUp() {
    curChamber = 0;
    LoadChamberSet();
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
        curChamber = (iter->second); // set this so entities can refer to themselves in deletion
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
    assert( HasChamber( uid ) );
	std::map < int, Chamber * >::iterator iter = chamberMap.find( uid );
    if ( iter == chamberMap.end() ) {
        // Load the chamber from file
        Chamber * C = new Chamber( json::parse_file(chamberFileLocMap[ uid ]) );
        // add it to the list
        chamberMap[uid] = C;
        return C;
    } else {
	    return iter->second;
    }
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
    std::map < int, std::string >::iterator iter = chamberFileLocMap.find( uid );
    return ( iter != chamberFileLocMap.end() );
}

PlayerEntity * ChamberManager::GetPlayer() {
    return player;
}

void ChamberManager::LoadChamberSet() {
    json chamberSet = json::parse_file("./saves/chamberSet.json");

    for (auto it_obj = chamberSet.begin_members(); it_obj != chamberSet.end_members(); ++it_obj ) {
        std::string fileLoc = it_obj->first;
        int chamberID = it_obj->second.as_int();
        chamberFileLocMap[ chamberID ] = fileLoc; // insert into map!
    }
}