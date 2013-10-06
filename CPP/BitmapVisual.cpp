/*
========================================================================

	A visual which always shows a static bitmap image

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "BitmapVisual.h"

using namespace MysticDave;

BitmapVisual::BitmapVisual( Vec2i * pos, ALLEGRO_BITMAP * bitmap ) {
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
	al_draw_bitmap( bitmap, pos->x - halfWidth - x, pos->y - halfHeight - y, 0 );
}