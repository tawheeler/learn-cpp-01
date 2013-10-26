/*
========================================================================

	A translational action something undertakes

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "Motion.h"
#include "Utils.h"

using namespace MysticDave;

Motion::Motion( Pos2D * pos, int dX, int dY, int totalMotionTime )
    : startX( pos->GetPixDX() ),
      startY( pos->GetPixDY() ),
      destX( pos->GetPixDX() + dX ),
      destY( pos->GetPixDY() + dY ),
      totalMotionTime( totalMotionTime ),
      motionTick( totalMotionTime )
{ 
    Motion::pos = pos;
}

Motion::~Motion() {
	// do nothing
}

void Motion::Update() {
	//move countdown
    if ( motionTick > 0 ) {
        motionTick--;
        pos->SetPixDX( GetPixelX() );
		pos->SetPixDY( GetPixelY() );
    }
}

bool Motion::IsDone() const {
	return motionTick <= 0;
}

int Motion::GetPixelX() {
	float u = ((float)(totalMotionTime - motionTick)) / totalMotionTime;
    int retval = (int) UTIL::Lerp( u, (float)startX, (float)destX );
    return retval;
}

int Motion::GetPixelY() {
	float u = ((float)(totalMotionTime - motionTick)) / totalMotionTime;
    int retval = (int) UTIL::Lerp( u, (float)startY, (float)destY );
    return retval;
}