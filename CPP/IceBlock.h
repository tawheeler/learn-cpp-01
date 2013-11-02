/*
========================================================================

	A tile entity that can be pushed around and etched on
    Standard movement of the block is for it to slide until it hits
    something

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "TileEntity.h"

namespace MysticDave {
    class IceBlock : public TileEntity {
    public:

                                    IceBlock( std::string name, int uid );
                                    IceBlock( jsoncons::json jobj );
		virtual                     ~IceBlock();

        void                        InitIceBlock();

    private:
        int                         sygaldry;
        int                         moveType;
    };
}