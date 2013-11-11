/*
========================================================================

	A BaseScreen which runs the standard game mode

========================================================================
*/

#include "MainScreen.h"
#include "ResourceManager.h"
#include "ScreenManager.h"
#include "LogManager.h"
#include "Globals.h"
#include "Motion.h"
#include "Utils.h"
#include "OutputStruct.h"
#include "TileBitmapVisual.h"
#include "Entity.h"
#include "jsoncons/json.hpp"
#include "PlayerEntity.h"
#include "TransitionEntity.h"
#include "SygaldryScreen.h"
#include "InventoryScreen.h"
#include "InputManager.h"
#include "ForceNet.h"

using jsoncons::json;
using namespace MysticDave;

void MainScreen::Init() {

    keysPressed = (InputManager::GetInstance()).GetKeysPressed();
    keysToggled = (InputManager::GetInstance()).GetKeysToggled();

    CM = &(ChamberManager::GetInstance());
    Chamber * curChamber = CM->GetChamber( 1 );
    
    // TODO: properly place the player into the chamber
    CM->GetPlayer()->GetPos()->SetPosFromTile( 6, 4 );

    (ChamberManager::GetInstance()).SetCurrentChamber( curChamber->GetUID() ); // set the current chamber
    curChamber->CalcForceNets();
}

void MainScreen::Cleanup() {
	// do nothing
}

void MainScreen::Update() {

    Chamber * curChamber = CM->GetCurrentChamber();
    PlayerEntity * player = CM->GetPlayer();

	if ( player != 0 ) {

        if ( !(player->IsInMotion())  ) { // && !(curChamber->HasEntityInMotion())

            int numDirsPressed = (keysPressed[DOWN] ? 1 : 0) + (keysPressed[UP] ? 1 : 0) + (keysPressed[LEFT] ? 1 : 0) + (keysPressed[RIGHT] ? 1 : 0);

            // interaction with environment
            if ( keysToggled[INTERACT] && keysPressed[INTERACT] ) {
                
                int dx = UTIL::DirToXAdjustment( player->GetDir() );
                int dy = UTIL::DirToYAdjustment( player->GetDir() );
                int curx = player->GetPos()->GetTileX();
                int cury = player->GetPos()->GetTileY();

                // check to see if there is an entity with the sygaldry property in the tile we are facing
                TileEntity * sygaldryAble = curChamber->GetEntityWithPropertyInTile( "Sygaldry", Chamber::GetTileNumFromPos(curx + dx, cury + dy) );
                if ( sygaldryAble != 0 ) {
                    // open the SygaldryScreen on that object
                    BaseScreen * bs = new SygaldryScreen( sygaldryAble );
                    bs->Init();
                    (ScreenManager::GetInstance()).PushGameScreen( bs );
                }
                
            } else if ( keysToggled[INVENTORY] && keysPressed[INVENTORY] ) {

                // open up the inventory screen
                BaseScreen * bs = new InventoryScreen();
                bs->Init();
                (ScreenManager::GetInstance()).PushGameScreen( bs );

            } else if ( numDirsPressed == 1 ) {

			    int dx = 0;
			    int dy = 0;
			    if ( keysPressed[DOWN] ) {
				    dy = 1;
			    } else if ( keysPressed[UP] ) {
				    dy = -1;
			    } else if ( keysPressed[RIGHT] ) {
				    dx = 1;
			    } else if ( keysPressed[LEFT] ) {
				    dx = -1;
			    }

			    int desDir = UTIL::DirFromDelta(dx, dy);
			    if ( player->GetDir() != desDir ) {
				    player->SetDir( desDir );
			    } else {
                    int curx = player->GetPos()->GetTileX();
                    int cury = player->GetPos()->GetTileY();
                    int tx = curx + dx;
                    int ty = cury + dy;

				    // check if target is free
                    if ( curChamber->CanTileBeEntered( tx, ty ) ) {
                        curChamber->RegisterTileEntityInTile( player, tx, ty );
                        player->MoveWithAnimation( desDir, 24, PlayerEntity::MOVE::WALK );
                    }
                    else {
                        TileEntity * pushable = curChamber->GetEntityWithPropertyInTile( "MoveType", Chamber::GetTileNumFromPos( tx, ty) );
                        if ( pushable != 0 ) {
                            // we are pushing something
                            ForceNet * fnet = curChamber->GetForceNetContaining( pushable->GetUID() );
                            if ( fnet != 0  ) {
                                // handle pushing a force net
                                if ( fnet->CanMove( desDir, curChamber ) ) {
                                    curChamber->RegisterTileEntityInTile( player, tx, ty );
                                    player->MoveWithAnimation( desDir, 36, PlayerEntity::MOVE::PUSH );
                                    fnet->Move( desDir, curChamber );
                                } else if ( pushable->IsInMotion() && pushable->GetCurrentMotion()->GetDir() == player->GetDir() ) {
                                    // the pushable is moving and it is moving the same direction we want to go

                                    Motion * mot = pushable->GetCurrentMotion();
                                    int ticksLeftInMove = mot->GetTotalMotionTime();
                                    int moveSpeed = (ticksLeftInMove > 24 ? ticksLeftInMove : 24);

                                    // move the player
                                    curChamber->RegisterTileEntityInTile( player, tx, ty );
                                    player->MoveWithAnimation( desDir, moveSpeed, PlayerEntity::MOVE::WALK );

                                } else {
                                    switch ( desDir ) {
                                        case ( UTIL::DIR_NORTH ): player->PlayAnimation( "tryPushNorth" ); break;
                                        case ( UTIL::DIR_EAST ):  player->PlayAnimation( "tryPushEast" );  break;
                                        case ( UTIL::DIR_SOUTH ): player->PlayAnimation( "tryPushSouth" ); break;
                                        case ( UTIL::DIR_WEST ):  player->PlayAnimation( "tryPushWest" );  break;
                                    }
                                }

                            } else {
                                // handle pushing a single tile entity
                                if ( pushable->CanMove( desDir, curChamber ) ) { //if we can push through into next space
                                    curChamber->RegisterTileEntityInTile( player, tx, ty );
                                    player->MoveWithAnimation( desDir, 36, PlayerEntity::MOVE::PUSH );
                                    curChamber->RegisterTileEntityInTile( pushable, tx + dx, ty + dy );
                                    pushable->MoveDir( desDir, 36 );
                                }  else if ( pushable->IsInMotion() && pushable->GetCurrentMotion()->GetDir() == player->GetDir() ) {
                                    // the pushable is moving and it is moving the same direction we want to go

                                    Motion * mot = pushable->GetCurrentMotion();
                                    int ticksLeftInMove = mot->GetTotalMotionTime();
                                    int moveSpeed = min( 36, ticksLeftInMove );

                                    // move the player
                                    curChamber->RegisterTileEntityInTile( player, tx, ty );
                                    player->MoveWithAnimation( desDir, moveSpeed, PlayerEntity::MOVE::WALK );

                                } else {
                                    switch ( desDir ) {
                                        case ( UTIL::DIR_NORTH ): player->PlayAnimation( "tryPushNorth" ); break;
                                        case ( UTIL::DIR_EAST ):  player->PlayAnimation( "tryPushEast" );  break;
                                        case ( UTIL::DIR_SOUTH ): player->PlayAnimation( "tryPushSouth" ); break;
                                        case ( UTIL::DIR_WEST ):  player->PlayAnimation( "tryPushWest" );  break;
                                    }
                                }
                                
                            }
                        }
                    }
			    }

		    }
        }

		player->Update();
	}

	curChamber->Update();

}

void MainScreen::Render() const {
    // TODO: add camera
	CM->GetCurrentChamber()->Render( 0, 0 );
	CM->GetPlayer()->GetVisual()->Render( 0, 0 );
}