/*
========================================================================

	A tile entity that can be pushed around and etched on (has 2 spots)
    Standard movement of the block is 1 tile

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "TileEntity.h"
#include "Animation.h"

namespace MysticDave {
    class StoneBlock : public TileEntity {
    public:

                                    StoneBlock( std::string name, int uid );
                                    StoneBlock( jsoncons::json jobj );
		                            ~StoneBlock();

        void                        InitStoneBlock();

    private:
        int                         sygaldryA;
        int                         sygaldryB;
        int                         moveType;
    };
}