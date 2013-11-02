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

    public:
	    enum Type {
		    INT,
		    FLOAT,
		    STRING,
		    BOOL,
		    EMPTY
	    };

	    Data	m_data;
	    Type	m_type;
        bool    m_save; // whether this property item should be saved to disk (and correspondingly loaded)
	    std::string m_name;

    private:
	    // declared to prevent unintentional use...
	    // (Don't forget to move to public access if you declare them!)
	    Property& Copy(const Property& source_object) {
		    m_data = source_object.m_data;
		    m_type = source_object.m_type;
            m_save = source_object.m_save;
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
            m_save = false;
	    }

	    void Register(int* value, bool save) {
		    m_type = INT;
		    m_data.m_int = value;
            m_save = save;
	    }

	    void Register(float* value, bool save) {
		    m_type = FLOAT;
		    m_data.m_float = value;
            m_save = save;
	    }

	    void Register(std::string* new_string, bool save) {
		    m_type = STRING;
		    m_data.m_string = new_string;
            m_save = save;
	    }

	    void Register(bool* value, bool save) {
		    m_type = BOOL;
		    m_data.m_bool = value;
            m_save = save;
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
            m_save = false;
	    }

	    Property(std::string const& name, int* value, bool save) {
		    m_name = name;
		    Register(value, save);
	    }

	    Property(std::string const& name, float* value, bool save) {
		    m_name = name;
		    Register(value, save);
	    }

	    Property(std::string const& name, std::string* value, bool save) {
		    m_name = name;
		    Register(value, save);
	    }

	    Property(std::string const& name, bool* value, bool save) {
		    m_name = name;
		    Register(value, save);
	    }

	    bool SetUnknownValue(std::string const& value);
	    bool Set(int value);
	    bool Set(float value);
	    bool Set(bool value);
	    bool Set(std::string const& value);
        
        bool SetSaveToDisk( bool save ) { 
            m_save = save;
        }

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

        bool GetSaveToDisk() {
            return m_save;
        }

	    // generic return...
	    std::string GetValue();

        bool IsOfType( Type t ) {
            return m_type == t;
        }

    };
}