/*
========================================================================

	A screen for displaying the player's inventory

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "InventoryScreen.h"
#include "ScreenManager.h"
#include "ResourceManager.h"
#include "ChamberManager.h"
#include "InputManager.h"
#include "Globals.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace MysticDave;

InventoryScreen::InventoryScreen() {
    // do nothing
}

void InventoryScreen::Init() {
    
    keysPressed = (InputManager::GetInstance()).GetKeysPressed();
    keysToggled = (InputManager::GetInstance()).GetKeysToggled();

    this->SetBlockUpdate( true );
    this->SetBlockRender( true );

    player = (ChamberManager::GetInstance()).GetPlayer();
    cursorPos = new Pos2D( 0, 0 );
    itemTexSheet = (ResourceManager::GetInstance()).LoadTextureSheet( "./res/items-6.png", TILE_DIM, TILE_DIM );

    inputDelayCounter = 0;
}

void InventoryScreen::Cleanup() {
	delete cursorPos;
}

void InventoryScreen::Update() {

    if ( keysToggled[INVENTORY] && keysPressed[INVENTORY] ) {
        this->SetDead();
    } else if ( inputDelayCounter <= 0 ){

        /*
        // wants to change up one rune
        if ( keysPressed[RIGHT] ) {
            runeSymbol++;
            if ( runeSymbol > 2 ) {
                runeSymbol = 2;
            }
            inputDelayCounter = 10;
        }
        else if ( keysPressed[LEFT] ) {
            runeSymbol--;
            if ( runeSymbol < 0 ) {
                runeSymbol = 0;
            }
            inputDelayCounter = 10;
        }
        else if ( keysPressed[UP] ) {
            runeColor ++;
            if ( runeColor > 5 ) {
                runeColor = 5;
            }
            inputDelayCounter = 10;
        }
        else if ( keysPressed[DOWN] ) {
            runeColor --;
            if ( runeColor < 0 ) {
                runeColor = 0;
            }
            inputDelayCounter = 10;
        }

        
        */

    } else {
        inputDelayCounter--;
        if ( inputDelayCounter < 0 ) {
            inputDelayCounter = 0;
        }
    }

}

void InventoryScreen::Render() const {

    // NOTE: this line is only okay since we are rendering over everything below
    al_clear_to_color( al_map_rgb( 50, 50, 100 ));

    int x = 0;
    int y = 0;
    int delta = (int)(TILE_DIM * 1.5f);
    int numPerRow = 4;

    for ( auto it = player->GetInventory()->begin(); it != player->GetInventory()->end(); ++it ) {

        int drawX = 32 + x*delta;
        int drawY = 32 + y*delta;

        al_draw_bitmap( itemTexSheet->GetTexture( (*it) ), drawX, drawY, 0 );

        x++;
        if ( x > numPerRow ) {
            x = 0;
            y ++;
        }
    }


    // TODO: render cursor position
}