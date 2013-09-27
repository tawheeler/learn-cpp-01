/*
========================================================================

	A single square in the grid of a chamber

	Tied to a static floor image
	Can contain TileEntities

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "Tile.h"
#include "TileEntity.h"

using namespace MysticDave;

Tile::Tile() {
	Tile::imageAddr  = 0;
	blocksOccupation = false;
}

Tile::Tile( char imageAddr ) {
	Tile::imageAddr  = imageAddr;
	blocksOccupation = false;
}

Tile::~Tile() {
	// do nothing (tile entity will be destroyed by someone else)
}

bool Tile::IsOccupied() {


	bool retval = blocksOccupation;

    // TODO: check list of tile entities

	return retval;

}