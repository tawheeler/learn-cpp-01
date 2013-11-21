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
#include "OutputStruct.h"
#include "PropertySet.h"

namespace MysticDave {
    class Entity : public PropertySet {
    public:

						                        Entity();
                                                Entity( jsoncons::json jobj );
		virtual                                 ~Entity();

	    std::string			                    GetName() const { return name; }
        std::string                             GetType() const { return type; }
        int                                     GetUID() const { return uid; }
        void                                    SetUID( int uid ) { Entity::uid = uid; }

	    virtual void		                    Update();
	    virtual void		                    Cleanup();

        virtual void                            OnInput( const std::string I );
        void                                    AddOutput( OutputStruct os );
        void                                    TriggerOutput( const std::string outputName );

        bool                                    ShouldBeRemoved() { return shouldBeRemoved; }

        virtual jsoncons::json  				GetJSON();
        
    protected:
	    std::string								name;
        std::string                             type;
        int                                     uid;

        bool                                    shouldBeRemoved;

        std::map< std::string, std::list<OutputStruct> * >  outputMap;
        std::set< std::string >                           inputs;

        void                                    Init();
	
    };
}