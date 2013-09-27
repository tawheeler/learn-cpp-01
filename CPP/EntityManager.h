/*
========================================================================

	Holds the list of entities

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include <map>
#include <list>
#include <string>
#include "Entity.h"

namespace MysticDave {
    class EntityManager {
    public:

	    void					StartUp();
	    void					ShutDown();
	    static EntityManager&	GetInstance();

        void                    Update();

        void                    AddEntity( Entity * e );

    private:
							    EntityManager() {};
							    EntityManager( EntityManager const& );  //do not implement
	    void operator = (EntityManager const&); // don't implement

        std::list< Entity * >             entityList;
        std::map< std::string, Entity * > entityStringMap;
        std::map< long,        Entity * > entityUIDMap;

    };
}