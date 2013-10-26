/*
========================================================================

	A transition screen which causes the map to scroll laterally over
    to the next chamber. Dave is moved to the corresponding edge-tile
    of the next chamber depending on direction

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "TransitionScrollScreen.h"
#include "LogManager.h"
#include "ScreenManager.h"
#include "ChamberManager.h"
#include "Globals.h"
#include "Utils.h"
#include "PlayerEntity.h"

using namespace MysticDave;

TransitionScrollScreen::TransitionScrollScreen( int targetChamberUID, int transitionDuration, int direction ) : 
    transitionDuration(transitionDuration),
    transitionCounter(transitionDuration),
    direction(direction),
    dx(0),
    dy(0),
    dx_player(0),
    dy_player(0)
{ 
    sourceChamber = (ChamberManager::GetInstance()).GetCurrentChamber();
    destChamber = (ChamberManager::GetInstance()).GetChamber( targetChamberUID );
    player = (ChamberManager::GetInstance()).GetPlayer();

    int playerX = player->GetPos()->GetTileX();
    int playerY = player->GetPos()->GetTileY();
    
    switch (direction) {
        case UTIL::DIR_NORTH:
            dy = -SCREEN_HEIGHT;
            dy_player = -(SCREEN_HEIGHT - TILE_DIM);
            targetTile = Chamber::GetTileNumFromPos( playerX, Chamber::CHAMBER_TILE_HEIGHT - 1 );
            break;
        case UTIL::DIR_EAST:
            dx = SCREEN_WIDTH;
            dx_player = SCREEN_WIDTH - TILE_DIM;
            targetTile = Chamber::GetTileNumFromPos( 0, playerY );
            break;
        case UTIL::DIR_SOUTH:
            dy = SCREEN_HEIGHT;
            dy_player = SCREEN_HEIGHT - TILE_DIM;
            targetTile = Chamber::GetTileNumFromPos( playerX, 0 );
            break;
        case UTIL::DIR_WEST:
            dx = -SCREEN_WIDTH;
            dx_player = -(SCREEN_WIDTH - TILE_DIM);
            targetTile = Chamber::GetTileNumFromPos( Chamber::CHAMBER_TILE_WIDTH - 1, playerY );
            break;
        default:
            break;
    }
}

void TransitionScrollScreen::Init() {
    this->SetBlockUpdate( true );
    this->SetBlockRender( true );
}

void TransitionScrollScreen::Cleanup() {
	// do nothing
}

void TransitionScrollScreen::Update() {
    --transitionCounter;

    if (transitionCounter <= 0) {

        // switch to the new chamber
        (ChamberManager::GetInstance()).SetCurrentChamber( destChamber->GetUID() );

        // add player to the new chamber
        player->GetPos()->SetPosFromTile( targetTile );
        destChamber->RegisterTileEntityInTile( player, targetTile );

        this->SetDead();
    }
}

void TransitionScrollScreen::Render() const {

    float u = 1.0f - ((float) transitionCounter) / transitionDuration;  //linear interpolation
    float cubicLerp = 3*(1.0f-u)*u*u + u*u*u;
    //float paraLerp = UTIL::Quadlerp( u, 0.0f, 1.0f, 1.0f );
    int pix_x = (int) (dx * cubicLerp);
    int pix_y = (int) (dy * cubicLerp);
    
    int player_x = (int)(dx_player * cubicLerp);
    int player_y = (int)(dy_player * cubicLerp);

    sourceChamber->Render( pix_x, pix_y );
    destChamber->Render( pix_x - dx, pix_y - dy );
    player->Render( player_x, player_y );

}