/*
========================================================================

	A BaseScreen which runs the standard game mode

========================================================================
*/

#include "MainScreen.h"
#include "ResourceManager.h"
#include "ChamberManager.h"
#include "ScreenManager.h"
#include "LogManager.h"
#include "Globals.h"
#include "Motion.h"
#include "Utils.h"
#include "TileBitmapVisual.h"
#include "Entity.h"
#include "jsoncons/json.hpp"
#include "CampFire.h"
#include "PlayerEntity.h"
#include "StoneBlock.h"
#include "SygaldryScreen.h"
#include "InputManager.h"

using jsoncons::json;
using namespace MysticDave;

void MainScreen::Init() {

    keysPressed = (InputManager::GetInstance()).GetKeysPressed();
    keysToggled = (InputManager::GetInstance()).GetKeysToggled();

    //curChamber = new Chamber( json::parse_file("./saves/chamber.json") );
    
    curChamber = new Chamber(1);

    CampFire * cf1 = new CampFire( "campFire1", 2 );
    CampFire * cf2 = new CampFire( "campFire2", 3 );
    CampFire * cf3 = new CampFire( "campFire2", 4 );
    CampFire * cf4 = new CampFire( "campFire2", 5 );
    cf1->SetPosTile( 2, 2 );
    curChamber->AddTileEntity( cf1 );
    curChamber->RegisterTileEntityInTile( cf1, 2, 2 );
    cf2->SetPosTile( 10, 2 );
    curChamber->AddTileEntity( cf2 );
    curChamber->RegisterTileEntityInTile( cf2, 10, 2 );
    cf3->SetPosTile( 2, 8 );
    curChamber->AddTileEntity( cf3 );
    curChamber->RegisterTileEntityInTile( cf3, 2, 8 );
    cf4->SetPosTile( 10, 8 );
    curChamber->AddTileEntity( cf4 );
    curChamber->RegisterTileEntityInTile( cf4, 10, 8 );

    StoneBlock * sb1 = new StoneBlock( "stoneBlock1", 6 );
    sb1->SetPosTile( 3, 3 );
    curChamber->AddTileEntity( sb1 );
    curChamber->RegisterTileEntityInTile( sb1, 3, 3 );

    StoneBlock * sb2 = new StoneBlock( "stoneBlock2", 7 );
    sb2->SetPosTile( 9, 3 );
    curChamber->AddTileEntity( sb2 );
    curChamber->RegisterTileEntityInTile( sb2, 9, 3 );

    StoneBlock * sb3 = new StoneBlock( "stoneBlock3", 8 );
    sb3->SetPosTile( 3, 7 );
    curChamber->AddTileEntity( sb3 );
    curChamber->RegisterTileEntityInTile( sb3, 3, 7 );

    StoneBlock * sb4 = new StoneBlock( "stoneBlock4", 9 );
    sb4->SetPosTile( 9, 7 );
    curChamber->AddTileEntity( sb4 );
    curChamber->RegisterTileEntityInTile( sb4, 9, 7 );
    
    using namespace std;
    using jsoncons::json;
    using jsoncons::pretty_print;

    jsoncons::json jobj_out = curChamber->GetJSON();

    ofstream myfile;
    myfile.open ("./saves/chamber.json");
    myfile << pretty_print(jobj_out) << std::endl;
    myfile.close();

    player = new PlayerEntity();
    player->SetPosTile( 6, 4 );

    (ChamberManager::GetInstance()).SetCurrentChamber( curChamber ); // set the current chamber
    curChamber->CalcForceNets();
}

void MainScreen::Cleanup() {
	delete curChamber;
	player->Cleanup();
	delete player;
}

void MainScreen::Update() {

	if ( player != 0 ) {

        if ( !(player->IsInMotion() ) ) {

            int numDirsPressed = (keysPressed[DOWN] ? 1 : 0) + (keysPressed[UP] ? 1 : 0) + (keysPressed[LEFT] ? 1 : 0) + (keysPressed[RIGHT] ? 1 : 0);

            // interaction with environment
            if ( keysToggled[INTERACT] && keysPressed[INTERACT] ) {
                
                int dx = UTIL::DirToXAdjustment( player->GetDir() );
                int dy = UTIL::DirToYAdjustment( player->GetDir() );
                int curx = player->GetClosestTileX();
                int cury = player->GetClosestTileY();

                // check to see if there is an entity with the sygaldry property in the tile we are facing
                TileEntity * sygaldryAble = curChamber->GetEntityWithPropertyInTile( "SygaldryA", Chamber::GetTileNumFromPos(curx + dx, cury + dy) );
                if ( sygaldryAble != 0 ) {
                    // open the SygaldryScreen on that object
                    BaseScreen * bs = new SygaldryScreen( sygaldryAble );
                    bs->Init();
                    (ScreenManager::GetInstance()).PushGameScreen( bs );
                }
                
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
                    int curx = player->GetClosestTileX();
                    int cury = player->GetClosestTileY();
                    int tx = curx + dx;
                    int ty = cury + dy;

				    // check if target is free
                    if ( curChamber->CanTileBeEntered( tx, ty ) ) {
                        curChamber->RegisterTileEntityInTile( player, tx, ty );
                        player->MoveDir( desDir, Chamber::GetTileNumFromPos( curx, cury ), 24 );
                        switch ( desDir ) {
                            case ( UTIL::DIR_NORTH ): player->PlayAnimation( "walkNorth" ); break;
                            case ( UTIL::DIR_EAST ):  player->PlayAnimation( "walkEast" );  break;
                            case ( UTIL::DIR_SOUTH ): player->PlayAnimation( "walkSouth" ); break;
                            case ( UTIL::DIR_WEST ):  player->PlayAnimation( "walkWest" );  break;
                        }
                    }
                    else {
                        TileEntity * pushable = curChamber->GetEntityWithPropertyInTile( "MoveType", Chamber::GetTileNumFromPos( tx, ty) );
                        if ( pushable != 0 ) {
                            // we are pushing something
                            ForceNet * fnet = curChamber->GetForceNetContaining( pushable->GetUID() );
                            if ( fnet != 0 ) {
                                // handle pushing a force net

                                if ( fnet->CanMove( desDir, curChamber ) ) {
                                    curChamber->RegisterTileEntityInTile( player, tx, ty );
                                    player->MoveDir( desDir, Chamber::GetTileNumFromPos( curx, cury ), 36 );
                                    switch ( desDir ) {
                                        case ( UTIL::DIR_NORTH ): player->PlayAnimation( "pushNorth" ); break;
                                        case ( UTIL::DIR_EAST ):  player->PlayAnimation( "pushEast" );  break;
                                        case ( UTIL::DIR_SOUTH ): player->PlayAnimation( "pushSouth" ); break;
                                        case ( UTIL::DIR_WEST ):  player->PlayAnimation( "pushWest" );  break;
                                    }
                                    fnet->Move( desDir, curChamber );
                                }

                            } else {
                                // handle pushing a single tile entity
                                if ( curChamber->CanTileBeEntered( tx + dx, ty + dy ) ) { //if we can push through into next space
                                    curChamber->RegisterTileEntityInTile( player, tx, ty );
                                    player->MoveDir( desDir, Chamber::GetTileNumFromPos( curx, cury ), 36 );
                                    switch ( desDir ) {
                                        case ( UTIL::DIR_NORTH ): player->PlayAnimation( "pushNorth" ); break;
                                        case ( UTIL::DIR_EAST ):  player->PlayAnimation( "pushEast" );  break;
                                        case ( UTIL::DIR_SOUTH ): player->PlayAnimation( "pushSouth" ); break;
                                        case ( UTIL::DIR_WEST ):  player->PlayAnimation( "pushWest" );  break;
                                    }
                                    curChamber->RegisterTileEntityInTile( pushable, tx + dx, ty + dy );
                                    pushable->MoveDir( desDir, Chamber::GetTileNumFromPos( tx, ty ), 36 );
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
	curChamber->Render( 0, 0 );
	player->GetVisual()->Render( 0, 0 );
}