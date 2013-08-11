/*
========================================================================

	A visual which always shows a static bitmap image

========================================================================
*/

#pragma once

#include "Visual.h"
#include "Vec2i.h"
#include "TextureSheet.h"

class BitmapVisual : public Visual {

public:

									BitmapVisual( Vec2i * pos, ALLEGRO_BITMAP * bitmap );
									~BitmapVisual();

	void							Cleanup();
	void							Render();

protected:

	Vec2i *							pos;
	ALLEGRO_BITMAP *				bitmap;
	int								halfWidth;  // bitmap width
	int								halfHeight;  // bitmap height

};