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

Motion::Motion( Pos2D * pos, int dir, int totalMotionTime )
    : startX( pos->GetPixDX() ),
      startY( pos->GetPixDY() ),
      destX( 0 ),
      destY( 0 ),
      totalMotionTime( totalMotionTime ),
      motionTick( totalMotionTime ),
      dir( dir )
{ 
    int dX = 0;
    int dY = 0;

    switch ( dir ) {
    case UTIL::DIR_NONE:
        break;
	case UTIL::DIR_NORTH:
        dX = 0;
        dY = -TILE_DIM;
		break;
	case UTIL::DIR_EAST:  
        dX = TILE_DIM;
        dY = 0;
		break;
	case UTIL::DIR_SOUTH: 
        dX = 0;
        dY = TILE_DIM;
		break;
	case UTIL::DIR_WEST:  
        dX = -TILE_DIM;
        dY = 0;
		break;
	}

    destX = startX + dX;
    destY = startY + dY;

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