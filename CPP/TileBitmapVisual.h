/*
========================================================================

	A visual the size of a bitmap, so is rendered in tilespace

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "BitmapVisual.h"
#include "Vec2i.h"
#include "TextureSheet.h"

namespace MysticDave {
    class TileBitmapVisual : public BitmapVisual {

    public:

									    TileBitmapVisual( Vec2i * pos, ALLEGRO_BITMAP * bitmap );
									    ~TileBitmapVisual();

	    virtual void					Render( int x, int y );
        virtual void                    Render( int x, int y, float cx, float cy, float cz );

    };
}