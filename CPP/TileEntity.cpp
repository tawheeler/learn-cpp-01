/*
========================================================================

	An entity which has a tile as its location

========================================================================
*/

#include "TileEntity.h"
#include "Utils.h"

TileEntity::TileEntity( int type ) : Entity( type ) {
	pos = new Vec2i();
	blocksOccupation = false;
	tileX = tileY = 0;

	motion = 0;
	sourceTile = 0;
}

TileEntity::TileEntity( int type, int uid ) : Entity( type, uid ) {
	pos = new Vec2i();
	blocksOccupation = false;
}

TileEntity::~TileEntity() {
	// do nothing
}

void TileEntity::SetTilePosToMatchPixPos() {
	tileX = UTIL::PixToGrid( pos->x );
	tileY = UTIL::PixToGrid( pos->y );
}

void TileEntity::SetPixPosToMatchTilePos() {
	pos->x = UTIL::GridToPix( tileX );
	pos->y = UTIL::GridToPix( tileY );
}

void TileEntity::Update() {
	Entity::Update();
	if ( motion != 0 ) {
		motion->Update();

		if ( motion->IsDone() ){
			delete motion;
			motion = 0;
			if ( sourceTile != 0 ) {
				sourceTile->tileEntity = 0;  // free it
				sourceTile = 0;
			}
			SetTilePosToMatchPixPos();  //update position
		}
	}
}

void TileEntity::Cleanup() {
	Entity::Cleanup();
	delete pos;
	if ( visual != 0 ) {
		visual->Cleanup();
		delete visual;
	}
	sourceTile = 0;
	if ( motion != 0 ) {
		delete motion;
	}
}

void TileEntity::AddMotion( Motion * motion ) {
	if ( TileEntity::motion != 0 ) {
		//abort it
		delete TileEntity::motion;
	}
	TileEntity::motion = motion;
}

void TileEntity::Move( int dir, Tile * curTile ) {
	
	switch ( dir ) {
		case UTIL::DIR_NORTH:
			motion = new Motion( pos, pos->x, pos->y - TILE_DIM, 48 ); 
			break;
		case UTIL::DIR_EAST:  
			motion = new Motion( pos, pos->x + TILE_DIM, pos->y, 48 ); 
			break;
		case UTIL::DIR_SOUTH: 
			motion = new Motion( pos, pos->x, pos->y + TILE_DIM, 48 ); 
			break;
		case UTIL::DIR_WEST:  
			motion = new Motion( pos, pos->x - TILE_DIM, pos->y, 48 ); 
			break;
	}

	sourceTile = curTile;
}
	
bool TileEntity::IsInMotion() {
	return (motion != 0);
}