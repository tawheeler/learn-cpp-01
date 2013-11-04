/*
========================================================================

	A translational action something undertakes

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/
#pragma once

#include "Pos2D.h"

namespace MysticDave {
    class Motion {
    public:

				    Motion( Pos2D * pos, int dir, int totalMotionTime );
				    ~Motion();

	    void		Update();
	    bool		IsDone() const;

        int         GetDir() { return dir; }
        int         GetTotalMotionTile() { return totalMotionTime; }

    private:
	
	    int			GetPixelX();
	    int			GetPixelY();

	    int			totalMotionTime;  // number of ticks the overall motion takes
	    int			motionTick;       // the tick the motion is currently in
	
	    int			startX; // [pix]
	    int			startY; // [pix]
	    int			destX;  // [pix]
	    int			destY;  // [pix]

        int         dir;

	    Pos2D *		pos;    // the vector tied to the motion

    };
}