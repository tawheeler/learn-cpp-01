/*
========================================================================

	Handles all chambers.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "Chamber.h"
#include "PlayerEntity.h"
#include <map>

namespace MysticDave {
    class ChamberManager {
    public:
	
	    void												StartUp();
	    void												ShutDown();
	    static ChamberManager&								GetInstance();	

        Chamber *                                           GetChamber( const int uid ); // obtain the Chamber with the given id
        Chamber *                                           GetCurrentChamber();
        void                                                SetCurrentChamber( const int uid );
        bool                                                HasChamber( const int uid );

        void                                                AddChamber( Chamber * chamber ); // add the chamber to the set

        PlayerEntity *                                      GetPlayer();

    private:
														    ChamberManager() {};
														    ChamberManager( ChamberManager const& );  //do not implement
	    void operator = ( ChamberManager const& ); // don't implement

	    std::map < int, Chamber * >			                chamberMap;

        Chamber *                                           curChamber; // the currently active chamber
        PlayerEntity *                                      player;
	
    };
}