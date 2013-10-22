/*
========================================================================

	A visual containing a "standard" visual and a bitmap visual for 
    sygaldry display

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "SygaldryVisualOverlay.h"
#include "ResourceManager.h"
#include "Globals.h"
#include <math.h>

using namespace MysticDave;

SygaldryVisualOverlay::SygaldryVisualOverlay( Vec2i * pos, ALLEGRO_BITMAP * bitmap ) {
	primaryVisual = new TileBitmapVisual( pos, bitmap );
    sygaldryVisual = new TileBitmapVisual( pos, bitmap );
    SetSygaldry( 0, 1, 1, 1 );
}

SygaldryVisualOverlay::~SygaldryVisualOverlay() {
	//do nothing
}

void SygaldryVisualOverlay::Cleanup() {
    primaryVisual->Cleanup();
    delete primaryVisual;
    sygaldryVisual->Cleanup();
    delete sygaldryVisual;
}

void SygaldryVisualOverlay::Render( int x, int y ) {
	primaryVisual->Render( x, y );
    sygaldryVisual->Render( x, y, colorX, colorY, colorZ );
}

void SygaldryVisualOverlay::Render( int x, int y, float cx, float cy, float cz ) {
	primaryVisual->Render( x, y, cx, cy, cz );
    sygaldryVisual->Render( x, y, colorX*cx, colorY*cy, colorZ*cz );
}

void SygaldryVisualOverlay::SetSygaldry( int runeSpriteNum, float colorX, float colorY, float colorZ ) {
    sygaldryVisual->SetBitmap( (ResourceManager::GetInstance()).LoadTextureSheet( "./res/RuneSet.png", TILE_DIM, TILE_DIM )->GetTexture( runeSpriteNum ) );
    SygaldryVisualOverlay::colorX = colorX;
    SygaldryVisualOverlay::colorY = colorY;
    SygaldryVisualOverlay::colorZ = colorZ;
}