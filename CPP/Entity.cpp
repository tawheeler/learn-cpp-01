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

using namespace MysticDave;

Entity::Entity( std::string name, long uid ) {
	Entity::name = name;
    Entity::uid  = uid;
}

Entity::~Entity() {
	// do nothing
}

void Entity::Update() {
	// do nothing
}

void Entity::Cleanup() {
    // free the Outputs list
    //std::list< Output * >::iterator iter;
    //for ( iter = outputs.begin(); iter != outputs.end(); ) {
    //    delete (*iter);
    //    iter = outputs.erase(iter);
    //}
}

void Entity::AddOutput( OutputStruct os ) {
    std::map< std::string, std::list< OutputStruct > >::iterator it = outputs.find( os.outputName );
    if ( it != outputs.end() ) {
       // the output name exists, add the output to the end of the list
       std::list< OutputStruct > mylist = (it->second);
       mylist.push_back( os );
    } else {
        // the output name does not exist. Add the output to a new list
        std::list< OutputStruct > mylist = std::list< OutputStruct> ();
        mylist.push_back( os );
        outputs[ os.outputName ] = mylist;
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

    return  0;

    /*using jsoncons::json;

    json obj(json::an_object);
    obj["name"] = name;
    obj["uid"]  = uid;
    
    json propertiesJSON(json::an_object);
    std::map< std::string, Property >::iterator iter;
    for ( iter = properties.begin(); iter != properties.end(); ++iter ) {
        std::string key = iter->first;
        Property p      = iter->second;

        if ( p.IsBool() )        propertiesJSON[ key ] = p.GetBool();
        else if ( p.IsFloat() )  propertiesJSON[ key ] = p.GetFloat();
        else if ( p.IsString() ) propertiesJSON[ key ] = p.GetString();
        else if ( p.IsInt() )    propertiesJSON[ key ] = p.GetInt();
    }
    obj["properties"] = propertiesJSON;

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

    return obj;*/
}