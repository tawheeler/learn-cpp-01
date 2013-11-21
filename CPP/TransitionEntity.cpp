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
#include "TransitionScrollScreen.h"

using jsoncons::json;
using namespace MysticDave;

TransitionEntity::TransitionEntity( int transitionType, int targetChamberUID, int param ) : TileEntity( name ) {
    InitTransitionEntity();
    
    TransitionEntity::transitionType = transitionType;
    TransitionEntity::targetChamberUID = targetChamberUID;
    TransitionEntity::transitionDuration = 50;
    TransitionEntity::param = param;

    name = type;
}

TransitionEntity::TransitionEntity( jsoncons::json jobj ) : TileEntity( jobj ) {
    InitTransitionEntity();

    json jPropertiesArr = jobj["properties"];
    transitionType      = jPropertiesArr["TransitionType"].as_int();
    targetChamberUID    = jPropertiesArr["TargetChamberUID"].as_int();
    transitionDuration  = 50;
    param               = jPropertiesArr["Param"].as_int();
}

TransitionEntity::~TransitionEntity() {
    // do nothing
}

void TransitionEntity::InitTransitionEntity() {
    type = "TransitionEntity";

    Register( "TransitionType", &transitionType, true );
    Register( "TargetChamberUID", &targetChamberUID, true );
    Register( "TransitionDuration", &transitionDuration, false );
    Register( "Param", &param, true );

    renderZ = -1;
    blocksOccupation = false;
    flammable = false;
}

void TransitionEntity::OnEntered( TileEntity * actor ) {
    
    // if Dave was the one who entered
    if ( actor->GetUID() == 1 ) {

        // remove Dave from the currentChamber
        (ChamberManager::GetInstance()).GetCurrentChamber()->UnregisterTileEntityInTile( actor, actor->GetPos()->GetTileNum() );

        BaseScreen * bs = 0;

        switch ( transitionType ) {
        case ( Transition::TRANSITION_BLACKOUT ):
            bs = new BlackoutScreen( targetChamberUID, transitionDuration, param );
            break;
        case ( Transition::TRANSITION_SCROLL ):
            bs = new TransitionScrollScreen( targetChamberUID, transitionDuration, param );
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
