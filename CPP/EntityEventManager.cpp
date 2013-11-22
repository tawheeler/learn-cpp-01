/*
========================================================================

	A singleton class which manages the events which entities create.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "EntityEventManager.h"
#include "ChamberManager.h"
#include "LogManager.h"
#include <assert.h>

using namespace MysticDave;

void EntityEventManager::StartUp() {
	
}

void EntityEventManager::ShutDown() {
	
	// Free what is on the stack
    std::list< MessageStruct * >::iterator iter;
    for ( iter = eventList.begin(); iter != eventList.end(); ) {
        delete (*iter); // free the Input
        iter = eventList.erase(iter);
    }
}

EntityEventManager& EntityEventManager::GetInstance() {
	static EntityEventManager* lmSingleton = NULL;
	if ( lmSingleton == NULL ) {
		lmSingleton = new EntityEventManager();
	}
	assert( lmSingleton );
	return *lmSingleton;
}

void EntityEventManager::AddEvent( MessageStruct * ms ) {
    bool inserted = false;

    std::list< MessageStruct * >::iterator iter;
    for ( iter = eventList.begin(); iter != eventList.end(); ++iter ) {
        if ( (*iter)->timeDelay > ms->timeDelay ) {
            eventList.insert( iter, ms );
            inserted = true;
            break;
        }
    }
    if ( !inserted ) {
        eventList.push_back( ms );
    }
}

void EntityEventManager::Update() { 
    // decrement all time delays by 1.
    // fire off any that have expired

    std::list< MessageStruct * >::iterator iter;
    for ( iter = eventList.begin(); iter != eventList.end(); ) {
        (*iter)->timeDelay --;
        if ( (*iter)->timeDelay <= 0 ) {

            // fire it off!
            Chamber * curChamber = (ChamberManager::GetInstance()).GetCurrentChamber();
            Entity * entity = curChamber->GetEntity( (*iter)->targetEntityID );
            if ( entity != 0 ) {
                entity->OnInput( (*iter)->inputName );
            }

            // remove it
            delete (*iter); // free the MessageStruct
            iter = eventList.erase(iter);
        } else {
            ++iter;
        }
    }
}