/*
========================================================================

	A visual the size of a tile, so is rendered in tilespace

========================================================================
*/

#include "TileBitmapVisual.h"
#include "Globals.h"

TileBitmapVisual::TileBitmapVisual( Vec2i * pos, ALLEGRO_BITMAP * bitmap ) : BitmapVisual( pos, bitmap ) {
	// do nothing
}

TileBitmapVisual::~TileBitmapVisual() {
	BitmapVisual::~BitmapVisual();
}

void TileBitmapVisual::Render() {
	al_draw_bitmap( bitmap, pos->x, pos->y, 0 );
}