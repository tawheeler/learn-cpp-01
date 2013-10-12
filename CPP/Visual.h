/*
========================================================================

	An object which can be rendered on the screen

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

namespace MysticDave {
    class Visual {
    public:
						    Visual();
						    ~Visual();
	    virtual void		Cleanup() = 0;
	    virtual void		Render( int x, int y ) = 0;  // render, where (x,y) = (0,0) renders appropriates for the chamber being appropraitely placed on the screen
        virtual void        Render( int x, int y, float cx, float cy, float cz ) = 0; // render where cx,cy,cz are color filter multipliers
    };
}