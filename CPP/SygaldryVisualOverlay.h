/*
========================================================================

	A visual containing a "standard" visual and a bitmap visual for 
    sygaldry display

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "TileBitmapVisual.h"
#include "Vec2i.h"
#include "TextureSheet.h"

namespace MysticDave {
    class SygaldryVisualOverlay : public Visual {

    public:

									    SygaldryVisualOverlay( Vec2i * pos, ALLEGRO_BITMAP * bitmap );
									    ~SygaldryVisualOverlay();
        virtual void                    Cleanup();

	    virtual void					Render( int x, int y );
        virtual void		            Render( int x, int y, float cx, float cy, float cz );

        void                            SetSygaldry( int runeSpriteNum, float colorX, float colorY, float colorZ );

    private:
        TileBitmapVisual *              primaryVisual;
        TileBitmapVisual *              sygaldryVisual;

        float colorX;
        float colorY;
        float colorZ;
    };
}