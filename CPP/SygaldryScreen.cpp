/*
========================================================================

	A BaseScreen for adding sygaldry to an object

    Player can add any of the binding runes and set their color net

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "SygaldryScreen.h"
#include "ScreenManager.h"
#include "ResourceManager.h"
#include "ChamberManager.h"
#include "Globals.h"
#include "InputManager.h"
#include "SygaldryVisualOverlay.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace MysticDave;

SygaldryScreen::SygaldryScreen( TileEntity * te ) {
    sygaldryEntity = te;
}

void SygaldryScreen::Init() {
    
    keysPressed = (InputManager::GetInstance()).GetKeysPressed();
    keysToggled = (InputManager::GetInstance()).GetKeysToggled();

    this->SetBlockUpdate( true );
    this->SetBlockRender( false );

    panelPos = new Pos2D( 0, 0 );
    panelPos->SetPixPos( 256, 256 );
    sygaldryPanel = new BitmapVisual( panelPos, (ResourceManager::GetInstance()).GetBitmap("./res/SygaldryPanel.png") );

    runeSetTextureSheet = (ResourceManager::GetInstance()).LoadTextureSheet( "./res/RuneSet.png", TILE_DIM, TILE_DIM );

    colorMap = new int[6*3];
    colorMap[ 0] =   0; colorMap[ 1] = 162; colorMap[ 2] = 232; //blue
    colorMap[ 3] =   0; colorMap[ 4] = 255; colorMap[ 5] =  64; //green
    colorMap[ 6] = 255; colorMap[ 7] =   0; colorMap[ 8] =   0; //red
    colorMap[ 9] = 128; colorMap[10] =   0; colorMap[11] = 128; //violet
    colorMap[12] = 255; colorMap[13] = 255; colorMap[14] =   0; //yellow
    colorMap[15] = 248; colorMap[16] = 133; colorMap[17] =  29; //orange

    rune = sygaldryEntity->Lookup("Sygaldry")->GetInt();

    inputDelayCounter = 0;
}

void SygaldryScreen::Cleanup() {
	delete panelPos;
}

void SygaldryScreen::Update() {

    if ( keysToggled[ENTER] && keysPressed[ENTER] ) {

        sygaldryEntity->Lookup("Sygaldry")->Set( rune );

        int runeIndex = (rune & 0x00FF);
        char runeColor = (rune >> 8 ) & 0x00FF;
        float cx = colorMap[3*runeColor] / 256.0f;
        float cy = colorMap[3*runeColor+1] / 256.0f;
        float cz = colorMap[3*runeColor+2] / 256.0f;

        SygaldryVisualOverlay * vis = static_cast<SygaldryVisualOverlay *>(sygaldryEntity->GetVisual());
        vis->SetSygaldry( runeIndex, cx, cy, cz );

        (ChamberManager::GetInstance()).GetCurrentChamber()->CalcForceNets();

        this->SetDead();

    } else if ( inputDelayCounter <= 0 ){

        char runeSymbol = rune & 0x00FF;
        char runeColor  = (rune >> 8) & 0x00FF;

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

        rune = (runeColor << 8 ) + runeSymbol;

    } else {
        inputDelayCounter--;
        if ( inputDelayCounter < 0 ) {
            inputDelayCounter = 0;
        }
    }

}

void SygaldryScreen::Render() const {
    sygaldryPanel->Render( 0, 0 );

    int runeIndex = (rune & 0x00FF);
    char runeColor = (rune >> 8 ) & 0x00FF;
    float cx = colorMap[3*runeColor] / 256.0f;
    float cy = colorMap[3*runeColor+1] / 256.0f;
    float cz = colorMap[3*runeColor+2] / 256.0f;

    al_draw_tinted_bitmap( runeSetTextureSheet->GetTexture( runeIndex ), al_map_rgba_f(cx, cy, cz, 1), panelPos->GetPixX() - 32, panelPos->GetPixY() - 32, 0);
}