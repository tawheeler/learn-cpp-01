/*
========================================================================

	A single square in the grid of a chamber

	Tied to a static floor image
	Can contain TileEntities

========================================================================
*/

#include "Tile.h"

#include "TileEntity.h"

Tile::Tile() {
	Tile::imageAddr  = 0;
	blocksOccupation = false;
	tileEntity = 0;
}

Tile::Tile( char imageAddr ) {
	Tile::imageAddr  = imageAddr;
	blocksOccupation = false;
}

Tile::~Tile() {
	// do nothing (tile entity will be destroyed by someone else)
}

bool Tile::IsOccupied() {


	bool retval = blocksOccupation || tileEntity != 0;

	//TODO: make it so that not all tileEntities automatically block occupation

	return retval;

}