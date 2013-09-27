/*
========================================================================

	Property - holds a value

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

    Portions Copyright (C) Charles Cafrelli, 2001

========================================================================
*/

//----- INCLUDES -----------------------------------------------//
#include "Property.h"


//----- CODE ---------------------------------------------------//

using namespace MysticDave;

bool Property::SetUnknownValue(std::string const& value) {
	bool return_value = true;
	switch(m_type)
	{
		case INT:
			*m_data.m_int = atoi(value.c_str());
			break;
		case FLOAT:
			*m_data.m_float = (float)(atof(value.c_str()));
			break;
		case STRING:
			*m_data.m_string = value;
			break;
		case BOOL:
			*m_data.m_bool = (value.compare("true") == 0) || (value.compare("TRUE") == 0);
			break;
		default:
			return_value = false;
			break;
	}

	return return_value;
}

bool Property::Set(int value) {
	bool return_value = false;
	if(m_type == INT)
	{
		*m_data.m_int = value;
		return_value = true;
	}

	return return_value;
}

bool Property::Set(float value) {
	bool return_value = false;
	if(m_type == FLOAT)
	{
		*m_data.m_float = value;
		return_value = true;
	}

	return return_value;
}

bool Property::Set(bool value) {
	bool return_value = false;
	if(m_type == BOOL)
	{
		*m_data.m_bool = value;
		return_value = true;
	}

	return return_value;
}

bool Property::Set(std::string const& value) {
	bool return_value = false;
	if(m_type == STRING)
	{
		*m_data.m_string = value;
		return_value = true;
	}

	return return_value;
}

std::string Property::GetValue() {
	std::string return_value;
	char buffer[64];
	switch(m_type)
	{
		case INT:
			sprintf(buffer,"%d",*m_data.m_int);
			return_value = buffer;
			break;
		case FLOAT:
			sprintf(buffer,"%f",*m_data.m_float);
			return_value = buffer;
			break;
		case STRING:
			return_value = *m_data.m_string;
			break;
		case BOOL:
			if(*m_data.m_bool)
				sprintf(buffer,"true");
			else
				sprintf(buffer,"false");
			return_value = buffer;
			break;
	}

	return return_value;
}