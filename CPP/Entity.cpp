/*
========================================================================

	An abstract game object
	Grants fundamental ability to receive messages, update, 
	posseses a uid, and a type

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "Entity.h"

using jsoncons::json;
using namespace MysticDave;

Entity::Entity( std::string name, int uid ) {
	Entity::name = name;
    Entity::uid  = uid;
    Init();
}

Entity::Entity( jsoncons::json jobj ) {
    Entity::name = std::string(jobj["name"].as_string().c_str());
    Entity::uid  = jobj["uid"].as_int();

    json jPropertiesArr = jobj["properties"];
    for (auto it = jPropertiesArr.begin_members(); it != jPropertiesArr.end_members(); ++it) {
        if ( it->second.is_bool() ) {
            bool b = it->second.as_bool();
            Register( std::string(it->first.c_str()), &b );
        } else if ( it->second.is_double() ) {
            float f = (float)(it->second.as_double());
            Register( std::string(it->first.c_str()), &f );
        } else if ( it->second.is_string() ) {
            std::string str = std::string(it->second.as_string().c_str());
            Register( std::string(it->first.c_str()), &str );
        } else if ( it->second.is_number() ) {
            int i = it->second.as_int();
            Register( std::string(it->first.c_str()), &i );
        }
    }

    Init();
}

Entity::~Entity() {
	// do nothing
}

void Entity::Init() {
    shouldBeRemoved = false;
    type = "Entity";
}

void Entity::Update() {
	// do nothing
}

void Entity::Cleanup() {
    // free the Outputs list TODO
    //std::list< Output * >::iterator iter;
    //for ( iter = outputs.begin(); iter != outputs.end(); ) {
    //    delete (*iter);
    //    iter = outputs.erase(iter);
    //}
    //
    // TODO: clear out the properties list
}

void Entity::OnInput( Input * I ) {

    // KILL - set entity to be removed
    if ( I->inputName.compare( "Kill" ) ) {
        shouldBeRemoved = true;
        // TODO: call output OnKilled
        // trigger all OnKilled outputs
    }
}

void Entity::AddOutput( OutputStruct os ) {
    std::map< std::string, std::list< OutputStruct > >::iterator it = outputMap.find( os.outputName );
    if ( it != outputMap.end() ) {
       // the output name exists, add the output to the end of the list
       std::list< OutputStruct > mylist = (it->second);
       mylist.push_back( os );
    } else {
        // the output name does not exist. Add the output to a new list
        std::list< OutputStruct > mylist = std::list< OutputStruct> ();
        mylist.push_back( os );
        outputMap[ os.outputName ] = mylist;
    }
}

jsoncons::json Entity::GetJSON() {
    //
    // name - string
    // uid - number
    // 
    // properties - json object
    // outputs    - json object
    //

    json obj(json::an_object);
    obj["name"] = name;
    obj["type"] = type;
    obj["uid"]  = uid;
    
    // add the properties
    json propertiesJSON( json::an_object );
    std::list< std::string > keys = GetKeys();
    std::list< std::string >::iterator iter;
    for ( iter = keys.begin(); iter != keys.end(); ++iter ) {
        std::string key = (*iter);
        Property * p    = Lookup(key);

        if ( p->IsOfType(Property::BOOL) )        propertiesJSON[ key ] = p->GetBool();
        else if ( p->IsOfType(Property::FLOAT) )  propertiesJSON[ key ] = p->GetFloat();
        else if ( p->IsOfType(Property::STRING) ) propertiesJSON[ key ] = p->GetString();
        else if ( p->IsOfType(Property::INT) )    propertiesJSON[ key ] = p->GetInt();
    }
    obj["properties"] = propertiesJSON;

    // add the outputs
    /*
    json outputsJSON(json::an_object);
    std::map< std::string, std::list<OutputStruct> >::iterator iter2;
    for ( iter2 = outputs.begin(); iter2 != outputs.end(); ++iter2 ) {
        std::string key = iter2->first;
        std::list<OutputStruct> list = iter2->second;

        json outputsListJSON(json::an_array);
        std::list<OutputStruct>::iterator iter3;
        for ( iter3 = list.begin(); iter3 != list.end(); ++iter3 ) {

            json osJSON( json::an_object );

            osJSON[ "outputName" ] = (*iter3).outputName;
            osJSON[ "targetEntity" ] = (*iter3).targetEntity;
            osJSON[ "inputName" ] = (*iter3).inputName;
            osJSON[ "timeDelay" ] = (*iter3).timeDelay;
            osJSON[ "fireOnceOnly" ] = (*iter3).fireOnceOnly;

            outputsListJSON.add( osJSON );
        }

        outputsJSON[ key ] = outputsListJSON;
    }
    obj["outputs"] = outputsJSON;
    */
    return obj;
}