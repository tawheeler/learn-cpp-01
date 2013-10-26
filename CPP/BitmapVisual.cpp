/*
========================================================================

	A visual which always shows a static bitmap image

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "BitmapVisual.h"

using namespace MysticDave;

BitmapVisual::BitmapVisual( Pos2D * pos, ALLEGRO_BITMAP * bitmap ) {
	BitmapVisual::pos = pos;
	BitmapVisual::bitmap = bitmap;
	BitmapVisual::halfWidth = al_get_bitmap_width( BitmapVisual::bitmap ) / 2;
	BitmapVisual::halfHeight = al_get_bitmap_height( BitmapVisual::bitmap ) / 2;
}

BitmapVisual::~BitmapVisual() {
	// do nothing
}

void BitmapVisual::Cleanup() {
	bitmap = 0; // someone else will delete the bitmap
	pos = 0;    // someone else will delete pos
}

void BitmapVisual::Render( int x, int y ) {
	al_draw_bitmap( bitmap, pos->GetPixX() - halfWidth - x, pos->GetPixY() - halfHeight - y, 0 );
}

void BitmapVisual::Render( int x, int y, float cx, float cy, float cz ) {
	al_draw_tinted_bitmap( bitmap, al_map_rgba_f(cx, cy, cz, 1), pos->GetPixX() - halfWidth - x, pos->GetPixY() - halfHeight - y, 0 );
}

void BitmapVisual::SetBitmap( ALLEGRO_BITMAP * bitmap ) {
	BitmapVisual::bitmap = bitmap;
	BitmapVisual::halfWidth = al_get_bitmap_width( BitmapVisual::bitmap ) / 2;
	BitmapVisual::halfHeight = al_get_bitmap_height( BitmapVisual::bitmap ) / 2;
}