/*
========================================================================

	Handles all chambers.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "Chamber.h"
#include <map>

namespace MysticDave {
    class ChamberManager {
    public:
	
	    void												StartUp();
	    void												ShutDown();
	    static ChamberManager&								GetInstance();	

        Chamber *                                           GetChamber( const int uid ); // obtain the Chamber with the given id
        Chamber *                                           GetCurrentChamber();
        void                                                SetCurrentChamber( Chamber * C );  // TODO: change this to (const int uid)

    private:
														    ChamberManager() {};
														    ChamberManager( ChamberManager const& );  //do not implement
	    void operator = ( ChamberManager const& ); // don't implement

	    std::map < int, Chamber * >			                chamberMap;

        Chamber *                                           curChamber; // the currently active chamber
	
    };
}