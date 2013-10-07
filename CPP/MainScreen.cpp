/*
========================================================================

	A BaseScreen which runs the standard game mode

========================================================================
*/

#include "MainScreen.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "Globals.h"
#include "Motion.h"
#include "Utils.h"
#include "TileBitmapVisual.h"
#include "Entity.h"
#include "jsoncons/json.hpp"
#include "CampFire.h"
#include "PlayerEntity.h"

using jsoncons::json;
using namespace MysticDave;

void MainScreen::Init() {
	keys[UP] = keys[DOWN] = keys[LEFT] = keys[RIGHT] = keys[SPACE] = false;

    //Entity e = Entity("dude", 101);
    //UTIL::WriteJSONToFile( e.GetJSON(), "./saves/dude.json" );

    //json dude_obj = json::parse_file( "./saves/dude.json" );
    //Entity e = Entity( dude_obj );

    //curChamber = new Chamber( json::parse_file("./saves/chamber.json") );
    
    curChamber = new Chamber(1);

    CampFire * cf1 = new CampFire( "campFire1", 2 );
    CampFire * cf2 = new CampFire( "campFire2", 3 );
    CampFire * cf3 = new CampFire( "campFire2", 3 );
    CampFire * cf4 = new CampFire( "campFire2", 3 );
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
}

void MainScreen::Cleanup() {
	delete curChamber;
	player->Cleanup();
	delete player;
}

void MainScreen::HandleEvent( ALLEGRO_EVENT evt ) {
	if( evt.type == ALLEGRO_EVENT_KEY_DOWN ){
		switch ( evt.keyboard.keycode ) {
			case ( ALLEGRO_KEY_DOWN ):  keys[DOWN]  = true; break;
			case ( ALLEGRO_KEY_UP ):    keys[UP]    = true; break;
			case ( ALLEGRO_KEY_LEFT ):  keys[LEFT]  = true; break;
			case ( ALLEGRO_KEY_RIGHT ): keys[RIGHT] = true; break;
			case ( ALLEGRO_KEY_SPACE ): keys[SPACE] = true; break;
		}
	} else if( evt.type == ALLEGRO_EVENT_KEY_UP ){
		switch ( evt.keyboard.keycode ) {
			case ( ALLEGRO_KEY_DOWN ):  keys[DOWN]  = false; break;
			case ( ALLEGRO_KEY_UP ):    keys[UP]    = false; break;
			case ( ALLEGRO_KEY_LEFT ):  keys[LEFT]  = false; break;
			case ( ALLEGRO_KEY_RIGHT ): keys[RIGHT] = false; break;
			case ( ALLEGRO_KEY_SPACE ): keys[SPACE] = false; break;
		}
	}
}

void MainScreen::Update() {

	if ( player != 0 ) {

		int numDirsPressed = (keys[DOWN] ? 1 : 0) + (keys[UP] ? 1 : 0) + (keys[LEFT] ? 1 : 0) + (keys[RIGHT] ? 1 : 0);

        if ( numDirsPressed == 1 && !(player->IsInMotion()) ) {


			int dx = 0;
			int dy = 0;
			if ( keys[DOWN] ) {
				dy = 1;
			} else if ( keys[UP] ) {
				dy = -1;
			} else if ( keys[RIGHT] ) {
				dx = 1;
			} else if ( keys[LEFT] ) {
				dx = -1;
			}

			int desDir = UTIL::DirFromDelta(dx, dy);
			if ( player->GetDir() != desDir ) {
				player->SetDir( desDir );
			} else {
                int curx = player->GetClosestTileX();
                int cury = player->GetClosestTileY();

				// check if target is free
                if ( curChamber->CanTileBeEntered( curx + dx, cury + dy ) ) {
                    //curChamber->AddTileEntityToTile( player, curx + dx, cury + dy );
                    player->MoveDir( desDir, Chamber::GetTileNumFromPos( curx + dx, cury + dy ), 24 );
                    switch ( desDir ) {
                    case ( UTIL::DIR_NORTH ): player->PlayAnimation( "walkNorth" ); break;
                    case ( UTIL::DIR_EAST ):  player->PlayAnimation( "walkEast" );  break;
                    case ( UTIL::DIR_SOUTH ): player->PlayAnimation( "walkSouth" ); break;
                    case ( UTIL::DIR_WEST ):  player->PlayAnimation( "walkWest" );  break;
                    }
                }
				/*
                Tile * targetTile = curChamber->GetTile( tx + dx, ty + dy );
				if ( !(targetTile->IsOccupied()) ) { // if free
					targetTile->tileEntity = player;  // add to next
					player->Move( desDir, curChamber->GetTile( tx, ty ) );
				} 
                */
                /*else if ( targetTile->tileEntity != 0 && targetTile->tileEntity->type == Entity::TYPE_BLOCK ) {
					// we are pushing a block
					Tile * farTargetTile = curChamber->GetTile( tx + 2*dx, ty + 2*dy );
					TileEntity * block = targetTile->tileEntity;
					if ( !farTargetTile->IsOccupied() ) { // if free
						targetTile->tileEntity = player;  // add to next
						player->PushMove( desDir, curChamber->GetTile( tx, ty ) );
						farTargetTile->tileEntity = block; // move it
						block->Move( desDir, 0 );
					}

				}*/
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