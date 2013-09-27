/*
========================================================================

	Property - holds a value

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

    Portions Copyright (C) Charles Cafrelli, 2001

========================================================================
*/

#pragma once

#include <string>
#include "HashTable.h"
#include "assert.h"

namespace MysticDave {
    class Property {
	
    protected:
	    union Data {
		    int* m_int;
		    float* m_float;
		    std::string* m_string;
		    bool* m_bool;
	    };

	    enum Type {
		    INT,
		    FLOAT,
		    STRING,
		    BOOL,
		    EMPTY
	    };

	    Data	m_data;
	    Type	m_type;
	    std::string m_name;

    private:
	    // declared to prevent unintentional use...
	    // (Don't forget to move to public access if you declare them!)
	    Property& Copy(const Property& source_object) {
		    m_data = source_object.m_data;
		    m_type = source_object.m_type;
		    m_name = source_object.m_name;

		    return *this;
	    }

	    Property& operator= (const Property& source_object) {
		    return Copy(source_object);
	    }

    protected:
	    void EraseType() {
		    m_type = EMPTY;
		    m_data.m_int = 0;
		    m_name = "";
	    }

	    void Register(int* value) {
		    m_type = INT;
		    m_data.m_int = value;
	    }

	    void Register(float* value) {
		    m_type = FLOAT;
		    m_data.m_float = value;
	    }

	    void Register(std::string* new_string) {
		    m_type = STRING;
		    m_data.m_string = new_string;
	    }

	    void Register(bool* value) {
		    m_type = BOOL;
		    m_data.m_bool = value;
	    }

    public:
	    Property() {
		    EraseType();
	    }

	    Property(const Property& source) {
		    Copy(source);
	    }

	    Property(std::string const& name) {
		    EraseType();
		    m_name = name;
	    }

	    Property(std::string const& name, int* value) {
		    m_name = name;
		    Register(value);
	    }

	    Property(std::string const& name, float* value) {
		    m_name = name;
		    Register(value);
	    }

	    Property(std::string const& name, std::string* value) {
		    m_name = name;
		    Register(value);
	    }

	    Property(std::string const& name, bool* value) {
		    m_name = name;
		    Register(value);
	    }

	    bool SetUnknownValue(std::string const& value);
	    bool Set(int value);
	    bool Set(float value);
	    bool Set(bool value);
	    bool Set(std::string const& value);

	    void SetName(std::string const& name) {
		    m_name = name;
	    }

	    std::string GetName() const {
		    return m_name;
	    }

	    int GetInt() {
		    assert(m_type == INT);
		    return *m_data.m_int;
	    }

	    float GetFloat() {
		    assert(m_type == FLOAT);
		    return *m_data.m_float;
	    }

	    std::string GetString() {
		    assert(m_type == STRING);
		    return *m_data.m_string;
	    }

	    bool GetBool() {
		    assert(m_type == BOOL);
		    return *m_data.m_bool;
	    }

	    // generic return...
	    std::string GetValue();

    };
}