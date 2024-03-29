/*
========================================================================

	A visual the size of a tile, so is rendered in tilespace

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "TileBitmapVisual.h"

using namespace MysticDave;

TileBitmapVisual::TileBitmapVisual( Pos2D * pos, ALLEGRO_BITMAP * bitmap ) : BitmapVisual( pos, bitmap ) {
	// do nothing
}

TileBitmapVisual::~TileBitmapVisual() {
	BitmapVisual::~BitmapVisual();
}

void TileBitmapVisual::Render( int x, int y ) {
	al_draw_bitmap( bitmap, pos->GetPixX() - x, pos->GetPixY() - y, 0 );
}

void TileBitmapVisual::Render( int x, int y, float cx, float cy, float cz ) {
	al_draw_tinted_bitmap( bitmap, al_map_rgba_f(cx, cy, cz, 1), pos->GetPixX() - x, pos->GetPixY() - y, 0 );
}