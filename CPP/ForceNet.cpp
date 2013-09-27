/*
========================================================================

	The collection of objects bound in a force net
	Pushing one pushes all of them

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "ForceNet.h"
#include "Utils.h"

using namespace MysticDave;

ForceNet::ForceNet() {
	// do nothing
}

ForceNet::~ForceNet() {
	// do nothing, someone else will delete the tile entities
}

/*
bool ForceNet::CanAct( int dir, Chamber * C ) {
	int dx = 0, dy = 0;
	switch ( dir ) {
		case( UTIL::DIR_NORTH ): dy = -1; break;
		case( UTIL::DIR_EAST ):  dx =  1; break;
		case( UTIL::DIR_SOUTH ): dy =  1; break;
		case( UTIL::DIR_WEST ):  dx = -1; break;
	}

	int x, y;

	bool retval =  true;
	std::deque < TileEntity * >::iterator iter = tileEntityList.begin();
	while ( retval && iter != tileEntityList.end() ) {
		x = (*iter)->tileX + dx;
		y = (*iter)->tileY + dy;
		retval = (C->IsInChamber( x, y )) && !(C->GetTile( x, y )->IsOccupied());
		++iter;
	}
	return retval;
} */

/*
void ForceNet::Act( int dir, Chamber * C ) {
	int dx = 0, dy = 0;
	switch ( dir ) {
		case( UTIL::DIR_NORTH ): dy = -1; break;
		case( UTIL::DIR_EAST ):  dx =  1; break;
		case( UTIL::DIR_SOUTH ): dy =  1; break;
		case( UTIL::DIR_WEST ):  dx = -1; break;
	}

	int x, y;

	// TODO: ensure we aren't clearing areas being moved into

	std::deque < TileEntity * >::iterator iter;
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ++iter ) {
		x = (*iter)->tileX + dx;
		y = (*iter)->tileY + dy;
		Tile * targetTile = C->GetTile( x, y );
		targetTile->tileEntity = (*iter);
		(*iter)->Move( dir, C->GetTile( (*iter)->tileX, (*iter)->tileY ) );
	}
	
}*/

void ForceNet::AddTileEntity( TileEntity * toAdd ) {
	tileEntityList.push_back( toAdd );
}

bool ForceNet::Contains( int uid ) {
	bool retval = false;
	std::deque < TileEntity * >::iterator iter = tileEntityList.begin();
	while ( !retval && iter != tileEntityList.end() ) {		
		retval = ((*iter)->GetUID() == uid);
		++iter;
	}
	return retval;
}