/*
========================================================================

	A tile entity that triggers on Dave entering and causes the chamber
    to blackout, and then transition to a new chamber, then re-light.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "TransitionEntity.h"
#include "LogManager.h"
#include "ChamberManager.h"
#include "BlackoutScreen.h"
#include "ScreenManager.h"

using jsoncons::json;
using namespace MysticDave;

TransitionEntity::TransitionEntity( std::string name, int uid, int transitionType, int targetChamberUID, int transitionDuration, int param ) : TileEntity( name, uid ) {
    InitTransitionEntity();
    
    TransitionEntity::transitionType = transitionType;
    TransitionEntity::targetChamberUID = targetChamberUID;
    TransitionEntity::transitionDuration = transitionDuration;
    TransitionEntity::param = param;
}

TransitionEntity::TransitionEntity( jsoncons::json jobj ) : TileEntity( jobj ) {
    InitTransitionEntity();

    json jPropertiesArr = jobj["properties"];
    transitionType      = jPropertiesArr["TransitionType"].as_int();
    targetChamberUID    = jPropertiesArr["TargetChamberUID"].as_int();
    transitionDuration  = jPropertiesArr["TransitionDuration"].as_int();
    param               = jPropertiesArr["Param"].as_int();
}

TransitionEntity::~TransitionEntity() {
    // do nothing
}

void TransitionEntity::InitTransitionEntity() {
    type = "TransitionEntity";

    Register( "TransitionType", &transitionType );
    Register( "TargetChamberUID", &targetChamberUID );
    Register( "TransitionDuration", &transitionDuration );
    Register( "Param", &param );

    renderZ = -1;
    blocksOccupation = false;
    flammable = false;
}

void TransitionEntity::OnEntered( TileEntity * actor ) {
    
    // if Dave was the one who entered
    if ( actor->GetUID() == 1 ) {

        // remove Dave from the currentChamber
        (ChamberManager::GetInstance()).GetCurrentChamber()->UnregisterTileEntityInTile( actor, actor->GetClosestTileLoc() );

        BaseScreen * bs = 0;

        switch ( transitionType ) {
        case ( Transition::TRANSITION_BLACKOUT ):
            bs = new BlackoutScreen( targetChamberUID, transitionDuration, param );
            break;
        case ( Transition::TRANSITION_SCROLL ):
            break;
        case ( Transition::TRANSITION_SPIN_TILE ):
            break;
        }

        if ( bs != 0 ) {
            bs->Init();
            (ScreenManager::GetInstance()).PushGameScreen( bs );
        } else {
            (LogManager::GetInstance()).Write( LogManager::LOG_APP, "TransitionEntity::OnEntered: Invalid transition type: %d!\n", transitionType );
        }
    }

}
