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

namespace MysticDave {
    class TileEntity;

    class Tile {

    public:

	    bool									blocksOccupation;  // whether this tile can contain TileEntities that move around (walls do not, floors do, for instance)
	    int										imageAddr;         // determines which image in the sprite sheet to use								

											    Tile();
											    Tile( char imageAddr );
											    ~Tile();

	    bool									IsOccupied(); // whether this tile can be moved in to or not

        std::deque < TileEntity * >             tileEntityList; // the tile within this spot, if there is one

    };
}