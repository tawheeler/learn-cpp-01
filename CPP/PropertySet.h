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
#include <map>
#include <list>
#include "Property.h"
#include "assert.h"
#include "Uncopyable.h"

namespace MysticDave {
    
    class PropertySet : private Uncopyable {

	    //----- Properties -----//
    protected:
	    std::map< std::string, Property * >	m_properties;

    public:
	    PropertySet();

	    ~PropertySet();

	    void Register( std::string const& name, int* value,         bool save ); 
	    void Register( std::string const& name, float* value,       bool save ); 
	    void Register( std::string const& name, std::string* value, bool save ); 
	    void Register( std::string const& name, bool* value,        bool save ); 

	    Property* Lookup( std::string const& name );
        bool      HasProperty( std::string const& name );

	    // use this for generic access when the data type is unknown
	    // this will convert to the proper format.
	    bool SetValue( std::string const& name, std::string const& value );

	    // use these if you know the data type
	    bool Set( std::string const& name, std::string const& value );
	    bool Set( std::string const& name, int value );
	    bool Set( std::string const& name, float value );
	    bool Set( std::string const& name, bool value );
	    bool Set( std::string const& name, char* value );

        // get a list of available properties
        std::list< std::string > GetKeys();
    };
}