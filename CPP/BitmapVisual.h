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
#include "Pos2D.h"

namespace MysticDave {
    class BitmapVisual : public Visual {

    public:

									    BitmapVisual( Pos2D * pos, ALLEGRO_BITMAP * bitmap );
									    ~BitmapVisual();

	    virtual void				    Cleanup();
	    virtual void					Render( int x, int y );
        virtual void                    Render( int x, int y, float cx, float cy, float cz );

        void                            SetBitmap( ALLEGRO_BITMAP * bitmap );

    protected:

	    Pos2D *							pos;
	    ALLEGRO_BITMAP *				bitmap;
	    int								halfWidth;  // bitmap width
	    int								halfHeight;  // bitmap height

    };
}