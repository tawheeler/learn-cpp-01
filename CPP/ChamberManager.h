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
#include <string>

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

        void                                                ReloadChamber( const int uid ); // reload the chamber from json

        void                                                AddChamber( Chamber * chamber ); // add the chamber to the set

        PlayerEntity *                                      GetPlayer();

    private:
		std::map < int, Chamber * >			                chamberMap;
        std::map < int, std::string >                    chamberFileLocMap;

        Chamber *                                           curChamber; // the currently active chamber
        PlayerEntity *                                      player;
                                                            
                                                            ChamberManager() {};
														    ChamberManager( ChamberManager const& );  //do not implement
	    void operator = ( ChamberManager const& ); // don't implement

        void                                                LoadChamberSet();
    };
}