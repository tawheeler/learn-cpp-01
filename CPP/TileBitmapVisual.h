/*
========================================================================

	A visual the size of a bitmap, so is rendered in tilespace

========================================================================
*/

#pragma once

#include "BitmapVisual.h"
#include "Vec2i.h"
#include "TextureSheet.h"

class TileBitmapVisual : public BitmapVisual {

public:

									TileBitmapVisual( Vec2i * pos, ALLEGRO_BITMAP * bitmap );
									~TileBitmapVisual();

	void							Render();

};