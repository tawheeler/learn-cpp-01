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


bool ForceNet::CanMove( int dir, Chamber * C ) {
    int dx = UTIL::DirToXAdjustment( dir );
    int dy = UTIL::DirToYAdjustment( dir );
	int x, y;

	bool retval =  true;
	std::deque < TileEntity * >::iterator iter = tileEntityList.begin();
	while ( retval && iter != tileEntityList.end() ) {
        x = (*iter)->GetPos()->GetTileX();
        y = (*iter)->GetPos()->GetTileY();
        retval = C->CanTileBeEntered( x + dx, y + dy );
		++iter;
	}
	return retval;
}

void ForceNet::Move( int dir, Chamber * C ) {
	int dx = UTIL::DirToXAdjustment( dir );
    int dy = UTIL::DirToYAdjustment( dir );
	int x, y;

    // TODO: check to see whether the target tile is an entity within this fnet

	std::deque < TileEntity * >::iterator iter;
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ++iter ) {
		x = (*iter)->GetPos()->GetTileX();
        y = (*iter)->GetPos()->GetTileY();

		C->RegisterTileEntityInTile( (*iter), x + dx, y + dy );
        (*iter)->MoveDir( dir, Chamber::GetTileNumFromPos( x, y ), 36 );
	}
	
}

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