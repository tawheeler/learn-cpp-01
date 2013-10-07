/*
========================================================================

	An abstract game object
	Grants fundamental ability to receive messages, update, 
	posseses a uid, and a type

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include <string>
#include <map>
#include <list>
#include <set>
#include "jsoncons/json.hpp"
#include "Property.h"
#include "Input.h"
#include "OutputStruct.h"
#include "PropertySet.h"

namespace MysticDave {
    class Entity : public PropertySet {
    public:

						                        Entity( std::string name, int uid );
                                                Entity( jsoncons::json jobj );
		                                        ~Entity();

	    std::string			                    GetName() { return name; }
        long                                    GetUID() { return uid; }

	    virtual void		                    Update();
	    virtual void		                    Cleanup();

        virtual void                            OnInput( Input * I );
        void                                    AddOutput( OutputStruct os );

        bool                                    ShouldBeRemoved() { return shouldBeRemoved; }

        virtual jsoncons::json  				GetJSON();
        
    protected:
	    std::string								name;
        std::string                             type;
        int                                     uid;

        bool                                    shouldBeRemoved;

        std::map< std::string, std::list<OutputStruct> >  outputMap;
        std::set< std::string >                           inputs;

        void                                   Init();
	
    };
}