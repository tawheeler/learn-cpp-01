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
#include "LogManager.h"
#include "EntityEventManager.h"

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

    // add the outputs
    json outputsJSON = jobj["outputs"];
    
    for (auto it_obj = outputsJSON.begin_members(); it_obj != outputsJSON.end_members(); ++it_obj ) {
        json outputsListJSON = it_obj->second;

        for (auto it_arr = outputsListJSON.begin_elements(); it_arr != outputsListJSON.end_elements(); ++it_arr) {

            OutputStruct os = OutputStruct();
            os.fireOnceOnly   = (*it_arr)[ "fireOnceOnly" ].as_bool();
            os.inputName      = (*it_arr)[ "inputName" ].as_string();
            os.outputName     = (*it_arr)[ "outputName" ].as_string();
            os.targetEntityID = (*it_arr)[ "targetEntityID" ].as_int();
            os.timeDelay      = (*it_arr)[ "timeDelay" ].as_int();
            AddOutput( os );
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
    // free the Outputs list
    std::map< std::string, std::list<OutputStruct> * >::iterator iter;
    for( iter = outputMap.begin(); iter != outputMap.end(); ) {
        delete ((*iter).second);
        iter = outputMap.erase(iter);
    }
}

void Entity::OnInput( const std::string I ) {

    // KILL - set entity to be removed
    if ( I.compare( "Kill" ) == 0 ) {
        shouldBeRemoved = true;
        TriggerOutput( "OnKilled" );
    }
}

void Entity::AddOutput( OutputStruct os ) {
    std::map< std::string, std::list< OutputStruct > * >::iterator it = outputMap.find( os.outputName );
    if ( it != outputMap.end() ) {
        // the output name exists, add the output to the end of the list
        (it->second)->push_back( os );
    } else {
        // the output name does not exist. Add the output to a new list
        std::list< OutputStruct > * mylist = new std::list< OutputStruct> ();
        mylist->push_back( os );
        outputMap[ os.outputName ] = mylist;
    }
}

void Entity::TriggerOutput( const std::string outputName ) {
    std::map< std::string, std::list< OutputStruct > * >::iterator map_it = outputMap.find( outputName );
    if ( map_it != outputMap.end() ) {
       // the output name exists, fire all in it
       std::list< OutputStruct > * outputList = (map_it->second);
       std::list< OutputStruct >::iterator iter;
       for ( iter = outputList->begin(); iter != outputList->end(); ) {

            MessageStruct * ms = new MessageStruct();
            ms->inputName = (*iter).inputName;
            ms->targetEntityID = (*iter).targetEntityID;
            ms->timeDelay = (*iter).timeDelay;
 
            (EntityEventManager::GetInstance()).AddEvent( ms );
 
            // remove if fireOnceOnly
            if ( (*iter).fireOnceOnly ) {
                iter = outputList->erase(iter);
            } else {
                ++iter;
            }
        }

        if ( outputList->empty() ) {
            delete outputList;
            outputMap.erase( map_it );
        }
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
    json outputsJSON(json::an_object);
    std::map< std::string, std::list<OutputStruct> * >::iterator iter2;
    for ( iter2 = outputMap.begin(); iter2 != outputMap.end(); ++iter2 ) {
        std::string key = iter2->first;
        std::list<OutputStruct> * list = iter2->second;

        json outputsListJSON(json::an_array);
        std::list<OutputStruct>::iterator iter3;
        for ( iter3 = list->begin(); iter3 != list->end(); ++iter3 ) {

            json osJSON( json::an_object );

            osJSON[ "outputName" ]     = (*iter3).outputName;
            osJSON[ "targetEntityID" ] = (*iter3).targetEntityID;
            osJSON[ "inputName" ]      = (*iter3).inputName;
            osJSON[ "timeDelay" ]      = (*iter3).timeDelay;
            osJSON[ "fireOnceOnly" ]   = (*iter3).fireOnceOnly;

            outputsListJSON.add( osJSON );
        }

        outputsJSON[ key ] = outputsListJSON;
    }
    obj["outputs"] = outputsJSON;
    
    return obj;
}