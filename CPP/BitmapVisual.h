/*
========================================================================

	A visual which always shows a static bitmap image

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "Visual.h"
#include "Vec2i.h"
#include "TextureSheet.h"

namespace MysticDave {
    class BitmapVisual : public Visual {

    public:

									    BitmapVisual( Vec2i * pos, ALLEGRO_BITMAP * bitmap );
									    ~BitmapVisual();

	    virtual void				    Cleanup();
	    virtual void					Render( int x, int y );

    protected:

	    Vec2i *							pos;
	    ALLEGRO_BITMAP *				bitmap;
	    int								halfWidth;  // bitmap width
	    int								halfHeight;  // bitmap height

    };
}