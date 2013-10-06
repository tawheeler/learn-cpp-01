/*
========================================================================

	A single square in the grid of a chamber

	Tied to a static floor image
	Can contain TileEntities

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include <deque>
#include "jsoncons/json.hpp"

namespace MysticDave {
    class TileEntity;

    class Tile {

    public:
											    Tile();
											    Tile( int imageAddr );
                                                Tile( jsoncons::json jobj );
											    ~Tile();

        bool                                    BlocksOccupation();
        void                                    SetBlocksOccupation( bool b );
        int                                     GetImageAddr();
        void                                    SetImageAddr( int i );
	    bool									IsOccupied(); // whether this tile can be moved in to or not

        jsoncons::json                          GetJSON();

    private:
        bool									blocksOccupation;  // whether this tile can contain TileEntities that move around (walls do not, floors do, for instance)
	    int										imageAddr;         // determines which image in the sprite sheet to use								

        std::deque < TileEntity * >             tileEntityList; // the tile entities within this spot, if there are any

    };
}