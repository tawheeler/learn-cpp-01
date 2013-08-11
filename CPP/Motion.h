/*
========================================================================

	A translational action something undertakes

========================================================================
*/
#pragma once

#include "Vec2i.h"

class Motion {
public:

				Motion( Vec2i * vec, int destX, int destY, int totalMotionTime );
				~Motion();

	void		Update();
	bool		IsDone();
	

private:
	
	int			GetPixelX();
	int			GetPixelY();

	int			totalMotionTime;  // number of ticks the overall motion takes
	int			motionTick;       // the tick the motion is currently in
	
	int			startX; // [pix]
	int			startY; // [pix]
	int			destX;  // [pix]
	int			destY;  // [pix]

	Vec2i *		vec;    // the vector tied to the motion

};