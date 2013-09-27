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
#include "jsoncons/json.hpp"
#include "Property.h"
#include "Input.h"
#include "OutputStruct.h"
#include "PropertySet.h"

namespace MysticDave {
    class Entity : public PropertySet {
    public:

						                        Entity( std::string name, long uid );
						                        ~Entity();

	    std::string			                    GetName() { return name; }
        long                                    GetUID() { return uid; }

	    virtual void		                    Update();
	    virtual void		                    Cleanup();

        virtual void                            OnInput( Input * I ) {};

        virtual bool                            ShouldBeRemoved() { return false; }

        void                                    AddOutput( OutputStruct os );

        virtual jsoncons::json  				GetJSON();

    protected:
	    std::string								name;
        int                                     uid;

	    std::map< std::string, Property >	              properties;
        std::map< std::string, std::list<OutputStruct> >  outputs;
	
    };
}