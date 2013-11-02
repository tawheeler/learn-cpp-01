/*
========================================================================

	A tile entity that can be pushed around and etched on
    Standard movement of the block is 1 tile

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "TileEntity.h"

namespace MysticDave {
    class StoneBlock : public TileEntity {
    public:

                                    StoneBlock( std::string name, int uid );
                                    StoneBlock( jsoncons::json jobj );
		virtual                     ~StoneBlock();

        void                        InitStoneBlock();

    private:
        int                         sygaldry;
        int                         moveType;
    };
}