/*
========================================================================

	A BaseScreen which runs the standard game mode

========================================================================
*/

#include "MainScreen.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "Globals.h"
#include "Tile.h"
#include "Motion.h"
#include "Utils.h"
#include "TileBitmapVisual.h"

#include <iostream>
#include <fstream>
#include "jsoncons/json.hpp"

using namespace MysticDave;

void MainScreen::Init() {
	keys[UP] = keys[DOWN] = keys[LEFT] = keys[RIGHT] = keys[SPACE] = false;
	
    using jsoncons::json;

    json jobj = json::parse_file("./saves/chamber.json");
    curChamber = new Chamber( jobj );

    // add a chamber mananger that can import / export chambers

    /*curChamber = new Chamber(1);

	int chamberTileInd[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21,  6, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 40, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 42 };

	int ind = 0;
	for ( int y = 0; y < 11; y ++ ) {
		for ( int x = 0; x < 13; x ++ ) {
			curChamber->GetTile( x, y )->imageAddr = chamberTileInd[ind];
			if ( x == 0 || x == 11 || y == 0 || y == 10 ) {
				curChamber->GetTile( x, y )->blocksOccupation = true;
			}
			ind++;
		}
	}*/

	curChamber->GenerateFloorImage();

    /*using namespace std;
    using jsoncons::json;
    using jsoncons::pretty_print;

    jsoncons::json jobj = curChamber->GetJSON();

    ofstream myfile;
    myfile.open ("./saves/chamber.json");
    myfile << pretty_print(jobj) << std::endl;
    myfile.close();*/

	/*player = new PlayerEntity();
	player->tileX = 5;
	player->tileY = 4;
	player->SetPixPosToMatchTilePos();

	TileEntity * block = new TileEntity( Entity::TYPE_BLOCK );
	block->visual = new TileBitmapVisual( block->pos, (ResourceManager::GetInstance()).GetBitmap("./res/Pot.png") );
	block->tileX = 6;
	block->tileY = 6;
	block->SetPixPosToMatchTilePos();
	curChamber->AddTileEntity( block );

	block = new TileEntity( Entity::TYPE_BLOCK );
	block->visual = new TileBitmapVisual( block->pos, (ResourceManager::GetInstance()).GetBitmap("./res/Pot.png") );
	block->tileX = 7;
	block->tileY = 6;
	block->SetPixPosToMatchTilePos();
	curChamber->AddTileEntity( block );*/

}

void MainScreen::Cleanup() {
	delete curChamber;
	//player->Cleanup();
	//delete player;
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

	/*if ( player != 0 ) {

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
				int tx = player->tileX;
				int ty = player->tileY;
				if ( curChamber->IsInChamber( tx + dx, ty + dy ) ) {
					// check if target is free
					Tile * targetTile = curChamber->GetTile( tx + dx, ty + dy );
					if ( !(targetTile->IsOccupied()) ) { // if free
						targetTile->tileEntity = player;  // add to next
						player->Move( desDir, curChamber->GetTile( tx, ty ) );
					} else if ( targetTile->tileEntity != 0 && targetTile->tileEntity->type == Entity::TYPE_BLOCK ) {
						// we are pushing a block
						Tile * farTargetTile = curChamber->GetTile( tx + 2*dx, ty + 2*dy );
						TileEntity * block = targetTile->tileEntity;
						if ( !farTargetTile->IsOccupied() ) { // if free
							targetTile->tileEntity = player;  // add to next
							player->PushMove( desDir, curChamber->GetTile( tx, ty ) );
							farTargetTile->tileEntity = block; // move it
							block->Move( desDir, 0 );
						}

					}
				}
			}

		}

		player->Update();
	}*/

	curChamber->Update();

}

void MainScreen::Render() const {
	curChamber->Render();
	//player->visual->Render();
}