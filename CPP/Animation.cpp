/*
========================================================================

	A sequence of sprites to play through
	Each frame has a set duration

========================================================================
*/

#include "Animation.h"

Animation::Animation( int numFrames, TextureSheet * tex ) {
	Animation::numFrames = numFrames;
	Animation::tex = tex;
	Animation::frameDurations = new int[numFrames];
	Animation::frameIDs = new char[numFrames];
}

Animation::~Animation() {
	delete[] frameDurations;
	delete[] frameIDs;
}

void Animation::Init() {
	totalDuration = 0;
	for ( int  i = 0;  i < numFrames; i ++ ) {
		totalDuration += frameDurations[i];
	}
}