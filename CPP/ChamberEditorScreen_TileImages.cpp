/*
========================================================================

	A BaseScreen which allows the user to edit a given chamber
    
    Specifically edits the tile images in a given chamber

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "ChamberEditorScreen_TileImages.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Globals.h"
#include "jsoncons/json.hpp"
#include "InputManager.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

using jsoncons::json;
using namespace MysticDave;

void ChamberEditorScreen_TileImages::Init() {
    keysPressed = (InputManager::GetInstance()).GetKeysPressed();
    keysToggled = (InputManager::GetInstance()).GetKeysToggled();

    cursorX = 0;
    cursorY = 0;
    actionCooldown = 0;
    brushIndex = 0;

    myChamber = (ChamberManager::GetInstance()).GetChamber( 1 );
    (ChamberManager::GetInstance()).SetCurrentChamber( 1 );
    //myChamber = (ChamberManager::GetInstance()).GetCurrentChamber();
    // todo: support conditions

    texSheet = new TextureSheet( "./res/BackgroundTiles.gif", 64, 64 );
}

void ChamberEditorScreen_TileImages::Cleanup() {
	// do nothing
}

void ChamberEditorScreen_TileImages::Update() {

    if ( actionCooldown != 0 ) {
        actionCooldown --;
    } else {

        int numDirsPressed = (keysPressed[DOWN] ? 1 : 0) + (keysPressed[UP] ? 1 : 0) + (keysPressed[LEFT] ? 1 : 0) + (keysPressed[RIGHT] ? 1 : 0);
        int numDirsPressed2 = (keysPressed[KEY_S] ? 1 : 0) + (keysPressed[KEY_W] ? 1 : 0) + (keysPressed[KEY_A] ? 1 : 0) + (keysPressed[KEY_D] ? 1 : 0);

        if ( numDirsPressed == 1 ) {

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

                cursorX += dx;
                if ( cursorX >= Chamber::CHAMBER_TILE_WIDTH ) {
                    cursorX = Chamber::CHAMBER_TILE_WIDTH - 1;
                } else if ( cursorX < 0 ) {
                    cursorX = 0;
                }
                
                cursorY += dy;
                if ( cursorY >= Chamber::CHAMBER_TILE_HEIGHT ) {
                    cursorY = Chamber::CHAMBER_TILE_HEIGHT - 1;
                } else if ( cursorY < 0 ) {
                    cursorY = 0;
                }

                actionCooldown = 5;

        } else if ( numDirsPressed2 == 1 ) {

			    if ( keysPressed[KEY_A] ) {
				    brushIndex -= 1;
			    } else if ( keysPressed[KEY_S] ) {
				    brushIndex += 20;
			    } else if ( keysPressed[KEY_D] ) {
				    brushIndex += 1;
			    } else if ( keysPressed[KEY_W] ) {
				    brushIndex -= 20;
			    }

                if ( brushIndex < 0 ) {
                    brushIndex = 0;
                } else if ( brushIndex > 399 ) {
                    brushIndex = 399;
                }

                actionCooldown = 5;
                
        } else if ( keysToggled[ENTER] && keysPressed[ENTER] ) { // apply the texture

            myChamber->SetTileImageAddress( Chamber::GetTileNumFromPos( cursorX, cursorY ), brushIndex );
            myChamber->GenerateFloorImage();

            actionCooldown = 5;

        } else if ( keysToggled[COPY] && keysPressed[COPY] ) { // copy the texture

            brushIndex = myChamber->GetTileImageAddress( Chamber::GetTileNumFromPos( cursorX, cursorY ) );

        } else if ( keysToggled[SAVE] && keysPressed[SAVE] ) {

            // TODO: save the chamber

        }
    }

}

void ChamberEditorScreen_TileImages::Render() const {

    // draw just the chamber's background image
    al_draw_bitmap( myChamber->GetFloorImage(), 0, 0, 0 );

    // draw the brush with 50% opacity
    al_draw_tinted_bitmap( texSheet->GetTexture( brushIndex ), al_map_rgba_f(1, 1, 1, 0.5), TILE_DIM * cursorX, TILE_DIM * cursorY, 0);

    // draw the cursor position
    float thickness = 4;
    float x1 = TILE_DIM * cursorX - thickness / 2;
    float y1 = TILE_DIM * cursorY - thickness / 2;
    float x2 = x1 + TILE_DIM + thickness;
    float y2 = y1 + TILE_DIM + thickness;
    
    ALLEGRO_COLOR color = al_color_html( "#FFD700" );

    al_draw_rectangle( x1, y1, x2, y2, color, thickness );
	
}