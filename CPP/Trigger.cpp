/*
========================================================================

	A tile entity that can be pushed around and etched on (has 2 spots)
    Standard movement of the block is 1 tile

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "Trigger.h"
#include "MessageStruct.h"
#include "LogManager.h"
#include "EntityEventManager.h"

using jsoncons::json;
using namespace MysticDave;

Trigger::Trigger( std::string name, int uid ) : TileEntity( name, uid ) {
    InitTrigger();
    isEnabled = startDisabled;
}

Trigger::Trigger( jsoncons::json jobj ) : TileEntity( jobj ) {
    InitTrigger();

    json jPropertiesArr = jobj["properties"];
    startDisabled  = jPropertiesArr["StartDisabled"].as_bool();

    isEnabled = !startDisabled;
}

Trigger::~Trigger() {
    // do nothing
}

void Trigger::InitTrigger() {
    type = "Trigger";

    startDisabled = false;

    Register( "StartDisabled", &startDisabled );

    renderZ = -1;
    blocksOccupation = false;
    flammable = false;
}

void Trigger::OnInput( const std::string I ) {

    if ( I.compare( "Enable" ) ) {
        // set to respond to trigger
        isEnabled = true;
    } else if ( I.compare( "Disable" ) ) {
        // set to no longer respond to trigger
        isEnabled = false;
    } else if ( I.compare( "Toggle" ) ) {
        // toggle the relay between enabled and disabled
        isEnabled = !isEnabled;
    } else if ( I.compare( "Trigger" ) ) {
        // trigger the relay, causing its OnTrigger output to fire if it is enabled
        if ( isEnabled ) {
            TriggerOutput( "OnTrigger" );
        }
    } else {
        TileEntity::OnInput( I );
    }
}

void Trigger::OnEntered( TileEntity * actor ) {
    if ( isEnabled ) {
        TriggerOutput( "OnTrigger" );
    }
}
