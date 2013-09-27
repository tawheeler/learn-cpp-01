/*
========================================================================

	PropertySet - A set of properties bound in a HashTable

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

    Portions Copyright (C) Charles Cafrelli, 2001

========================================================================
*/

#pragma once

#include <string>
#include "HashTable.h"
#include "Property.h"
#include "assert.h"

namespace MysticDave {
    
    class PropertySet {

	    //----- Properties -----//
    protected:
	    HashTable<Property>	m_properties;

	    //----- Methods -----//
    private:
	    // declared to prevent unintentional use...
	    // (Don't forget to move to public access if you declare them!)
	    PropertySet& Copy(const PropertySet& source_object);
	    PropertySet& operator= (const PropertySet& source_object);

    public:
	    PropertySet();
	    PropertySet(const PropertySet& source)
	    {
		    Copy(source);
	    }

	    ~PropertySet();

	    void Register(std::string const& name, int* value); 
	    void Register(std::string const& name, float* value); 
	    void Register(std::string const& name, std::string* value); 
	    void Register(std::string const& name, bool* value); 

	    Property* Lookup(std::string const& name);

	    // use this for generic access when the data type is unknown
	    // this will convert to the proper format.
	    bool SetValue(std::string const& name, std::string const& value);

	    // use these if you know the data type
	    bool Set(std::string const& name, std::string const& value);
	    bool Set(std::string const& name, int value);
	    bool Set(std::string const& name, float value);
	    bool Set(std::string const& name, bool value);
	    bool Set(std::string const& name, char* value);

        // get a list of available properties
        std::list< std::string > GetKeys();
    };
}