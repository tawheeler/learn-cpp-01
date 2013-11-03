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
    class Block : public TileEntity {
    public:

        enum BLOCK_TYPE{ STONE, ICE, WOOD, METAL };

                                    Block( std::string name, int uid, int blockType );
                                    Block( jsoncons::json jobj );
		virtual                     ~Block();

        void                        InitBlock();

        virtual void                OnMoveCompleted();

    private:
        
        int                         blockType; // type of block
        int                         sygaldry;  // the rune enscribed on it

        int                         moveType;  // 0 - stationary, 1 - moves 1 spot, 2 - slides until it hits
        int                         hardness;  // the higher the number, the greater the "strength" needed to chisel it
        
    };
}