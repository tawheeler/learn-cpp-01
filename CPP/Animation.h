/*
========================================================================

	A sequence of sprites to play through
	Each frame has a set duration

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "TextureSheet.h"
#include <string>

namespace MysticDave {
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
}