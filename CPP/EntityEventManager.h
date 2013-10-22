/*
========================================================================

	A singleton class which manages the events which entities create.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "MessageStruct.h"
#include <list>

namespace MysticDave {
    class EntityEventManager {
    public:
	
	    void												StartUp();
	    void												ShutDown();
	    static EntityEventManager&						    GetInstance();	

        void                                                AddEvent( MessageStruct * ms ); // Add the given event to the manager, which inserts it into a list
        void                                                Update(); // Update by one tick. Fire those that need it. 

    private:
														    EntityEventManager() {};
														    EntityEventManager( EntityEventManager const& );  //do not implement
	    void operator = ( EntityEventManager const& ); // don't implement

        std::list< MessageStruct * >                        eventList;
	
    };
}