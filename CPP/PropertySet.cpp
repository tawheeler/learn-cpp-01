/*
========================================================================

	PropertySet - A set of properties bound in a HashTable

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

    Portions Copyright (C) Charles Cafrelli, 2001

========================================================================
*/

#include "PropertySet.h"
#include "assert.h"

using namespace MysticDave;

PropertySet::PropertySet() {}

PropertySet::~PropertySet() {}

void PropertySet::Register(std::string const& name, int* value) {
	Property* new_property = new Property(name,value);
	m_properties[name] = new_property;
}

void PropertySet::Register(std::string const& name, float* value) {
	Property* new_property = new Property(name,value);
	m_properties[name] = new_property;
}

void PropertySet::Register(std::string const& name, std::string* value) {
	Property* new_property = new Property(name,value);
	m_properties[name] = new_property;
}

void PropertySet::Register(std::string const& name, bool* value) {
	Property* new_property = new Property(name,value);
    m_properties[name] = new_property;
}

Property* PropertySet::Lookup(std::string const& name) {
    std::map< std::string, Property *>::iterator pos = m_properties.find(name);
    assert(pos != m_properties.end());
    return pos->second;
}

bool PropertySet::HasProperty( std::string const& name ) {
    std::map< std::string, Property *>::iterator pos = m_properties.find(name);
    return pos != m_properties.end();
}

bool PropertySet::SetValue(std::string const& name, std::string const& value) {
	bool return_value = false;
	Property* property = Lookup(name);
	if(property)
	{
		return_value = property->SetUnknownValue(value);
	}

	return return_value;

}

bool PropertySet::Set(std::string const& name, std::string const& value) {
	bool return_value = false;
	Property* property = Lookup(name);
	if(property)
	{
		return_value = property->Set(value);
	}

	return return_value;
}

bool PropertySet::Set(std::string const& name, int value) {
	bool return_value = false;
	Property* property = Lookup(name);
	if(property)
	{
		return_value = property->Set(value);
	}

	return return_value;

}

bool PropertySet::Set(std::string const& name, float value) {
	bool return_value = false;
	Property* property = Lookup(name);
	if(property)
	{
		return_value = property->Set(value);
	}

	return return_value;
}

bool PropertySet::Set(std::string const& name, bool value) {
	bool return_value = false;
	Property* property = Lookup(name);
	if(property)
	{
		return_value = property->Set(value);
	}

	return return_value;
}

bool PropertySet::Set(std::string const& name, char* value) {
	bool return_value = false;
	Property* property = Lookup(name);
	if(property)
	{
		return_value = property->Set(std::string(value));
	}

	return return_value;
}

std::list< std::string > PropertySet::GetKeys() {
    std::list< std::string > retval;
    for ( std::map< std::string, Property * >::iterator iter = m_properties.begin(); iter != m_properties.end(); ++iter) {
      retval.push_back( iter->first );
    }
    return retval;
}





