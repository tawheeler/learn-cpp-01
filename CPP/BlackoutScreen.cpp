/*
========================================================================

	A transition screen which pushes everything to black and swaps the
    underlying chambers

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "BlackoutScreen.h"
#include "LogManager.h"
#include "ScreenManager.h"
#include "ChamberManager.h"
#include "Globals.h"
#include "PlayerEntity.h"

using namespace MysticDave;

BlackoutScreen::BlackoutScreen( int targetChamberUID, int blackoutDuration, int targetTile ) : 
    targetChamberUID(targetChamberUID),
    blackoutCounter(blackoutDuration),
    targetTile(targetTile)
{ }

void BlackoutScreen::Init() {
    this->SetBlockUpdate( true );
    this->SetBlockRender( true );
}

void BlackoutScreen::Cleanup() {
	// do nothing
}

void BlackoutScreen::Update() {

    --blackoutCounter;
    if ( blackoutCounter <= 0 ) {
        // switch to the new chamber
        (ChamberManager::GetInstance()).SetCurrentChamber( targetChamberUID );

        // add player to the new chamber
        PlayerEntity * player = (ChamberManager::GetInstance()).GetPlayer();
        Chamber * curChamber = (ChamberManager::GetInstance()).GetCurrentChamber();
        player->GetPos()->SetPosFromTile( targetTile );
        curChamber->RegisterTileEntityInTile( player, targetTile );

        this->SetDead();
    } 

}

void BlackoutScreen::Render() const {
    // render nothing!
}