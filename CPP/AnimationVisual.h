/*
========================================================================

	A visual which shows animations

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "Visual.h"
#include "Animation.h"
#include "Vec2i.h"

namespace MysticDave {
    class AnimationVisual : public Visual {
    public:

						    AnimationVisual( Vec2i * pos, ALLEGRO_BITMAP * bitmap );
						    ~AnimationVisual();

	    virtual void		Cleanup();
	    virtual void		Render( int x, int y );
        virtual void		Render( int x, int y, float cx, float cy, float cz );

	    void				PlayAnimation( Animation * anim );
	    void				SetBitmap( ALLEGRO_BITMAP * bitmap );
	    bool				IsPlayingAnimation();

    private:

	    Vec2i *				pos;
	    ALLEGRO_BITMAP *	bitmap; // default bitmap to play
	    int					halfWidth;  // bitmap width
	    int					halfHeight;  // bitmap height

	    Animation *			animation;  // the animation to play
	    int					frameTick;  // the tick counter for the frame shifting
	    int					frameIndex; // the current frame index

    };
}