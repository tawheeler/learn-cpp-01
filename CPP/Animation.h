/*
========================================================================

	A sequence of sprites to play through
	Each frame has a set duration

========================================================================
*/

#pragma once

#include "TextureSheet.h"
#include <string>

class Animation {
public:
	int					numFrames;

						Animation( int numFrames, TextureSheet * tex );
					    ~Animation();

	void				Init();

	char *				frameIDs;
	TextureSheet *		tex;
	int *				frameDurations;
	int					totalDuration;
};