/*
========================================================================

	PropertySet - A set of properties bound in a HashTable

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

    Portions Copyright (C) Charles Cafrelli, 2001

========================================================================
*/

#include "PropertySet.h"
#include "HashTable.h"

using namespace MysticDave;

PropertySet::PropertySet() {}

PropertySet::~PropertySet() {}

void PropertySet::Register(std::string const& name, int* value) {
	Property* new_property = new Property(name,value);
	m_properties.Insert(name,new_property);
}

void PropertySet::Register(std::string const& name, float* value) {
	Property* new_property = new Property(name,value);
	m_properties.Insert(name,new_property);
}

void PropertySet::Register(std::string const& name, std::string* value) {
	Property* new_property = new Property(name,value);
	m_properties.Insert(name,new_property);
}

void PropertySet::Register(std::string const& name, bool* value) {
	Property* new_property = new Property(name,value);
	m_properties.Insert(name,new_property);
}

Property* PropertySet::Lookup(std::string const& name) {
	return m_properties.Lookup(name);
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
    return m_properties.GetKeys();
}





