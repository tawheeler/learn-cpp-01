/*
========================================================================

	A translational action something undertakes

========================================================================
*/

#include "Motion.h"
#include "Utils.h"

Motion::Motion( Vec2i * vec, int destX, int destY, int totalMotionTime ) {
	Motion::vec             = vec;
	Motion::startX          = vec->x;
	Motion::startY          = vec->y;
	Motion::destX           = destX;
	Motion::destY           = destY;
	Motion::totalMotionTime = totalMotionTime;
	Motion::motionTick      = totalMotionTime;
}

Motion::~Motion() {
	// do nothing
}

void Motion::Update() {
	//move countdown
    if ( motionTick > 0 ) {
        motionTick--;
		vec->x = GetPixelX();
		vec->y = GetPixelY();
    }
}

bool Motion::IsDone() {
	return motionTick <= 0;
}

int Motion::GetPixelX() {
	float u = ((float)totalMotionTime - (float) motionTick) / totalMotionTime;
    int retval = (int) UTIL::Lerp( u, startX, destX );
    return retval;
}

int Motion::GetPixelY() {
	float u = ((float)totalMotionTime - (float) motionTick) / totalMotionTime;
    int retval = (int) UTIL::Lerp( u, startY, destY );
    return retval;
}