/*
========================================================================

	A component of a larger block

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "Block.h"

namespace MysticDave {
    class CompoundBlock : public Block {
    public:

        enum TILE_TYPE{ NORTH_EDGE, NORTHEAST_CORNER, EAST_EDGE, SOUTHEAST_CORNER, SOUTH_EDGE, SOUTHWEST_CORNER, WEST_EDGE, NORTHWEST_CORNER, CENTER,
            NORTH_TERMINAL, EAST_TERMINAL, SOUTH_TERMINAL, WEST_TERMINAL, VERTICAL, HORIZONTAL };

                                    CompoundBlock( int blockType, int tileType );
                                    CompoundBlock( jsoncons::json jobj );
		virtual                     ~CompoundBlock();

        void                        InitCompoundBlock();

    private:
        int                         tileType;
        int                         inherentSygaldry; // force binding joining this with the other compound blocks
        
    };
}