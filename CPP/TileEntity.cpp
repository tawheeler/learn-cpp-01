/*
========================================================================

	An entity which has a tile as its location

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "TileEntity.h"
#include "Utils.h"

using namespace MysticDave;

TileEntity::TileEntity( std::string name, long uid ) : Entity( name, uid ) {
    renderZ = 1;
    sourceTileLoc = -1;

    blocksOccupation = false;
    flammable = false;

    pos = new Vec2i();
	visual = 0;
}

TileEntity::~TileEntity() {
	// do nothing
}

void TileEntity::Cleanup() {
	Entity::Cleanup();

	// position
    delete pos;

    // visual
	if ( visual != 0 ) {
		visual->Cleanup();
		delete visual;
	}

    // motions
    std::deque< Motion * >::iterator iter;
    for ( iter = motionQueue.begin(); iter != motionQueue.end(); ) {
        delete (*iter);
        iter = motionQueue.erase(iter);
    }
}

bool TileEntity::BlocksOccupation() {
    return blocksOccupation;
}

void TileEntity::SetBlocksOccupation( bool blocks ) {
    blocksOccupation = blocks;
}

Vec2i * TileEntity::GetPos() {
    return pos;
}

Visual * TileEntity::GetVisual() {
    return visual;
}

void TileEntity::SetVisual( Visual * visual ) {
    TileEntity::visual = visual;
}

int TileEntity::GetRenderZ() {
    return renderZ;
}

void TileEntity::SetRenderZ( int z ) {
    TileEntity::renderZ = z;
}

bool TileEntity::IsFlammable() {
    return flammable;
}

void TileEntity::SetFlammable( bool b ) {
    TileEntity::flammable = b;
}

void TileEntity::Update() {
	Entity::Update();
	
    // TODO: this
    /*
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
    */
}

void TileEntity::Render( int x, int y ) {
    //TODO: change visual render to Render(x,y)
    if ( visual != 0 ) {
        visual->Render();
    }
}

void TileEntity::AddMotion( Motion * motion ) {
    motionQueue.push_back( motion );
}

void TileEntity::HaltAllMotion( Motion * motion ) {
    //TODO: this
    // first blip Dave over to a tile
}

void TileEntity::MoveDir( int dir, int sourceTileLoc ) {
	
	switch ( dir ) {
		case UTIL::DIR_NORTH:
            motionQueue.push_back( new Motion( pos, pos->x, pos->y - TILE_DIM, 48 ) ); 
			break;
		case UTIL::DIR_EAST:  
			motionQueue.push_back( new Motion( pos, pos->x + TILE_DIM, pos->y, 48 ) ); 
			break;
		case UTIL::DIR_SOUTH: 
			motionQueue.push_back( new Motion( pos, pos->x, pos->y + TILE_DIM, 48 ) ); 
			break;
		case UTIL::DIR_WEST:  
			motionQueue.push_back( new Motion( pos, pos->x - TILE_DIM, pos->y, 48 ) ); 
			break;
	}

	TileEntity::sourceTileLoc = sourceTileLoc;
}
	
bool TileEntity::IsInMotion() {
	return !motionQueue.empty();
}

jsoncons::json TileEntity::GetJSON() {
    return Entity::GetJSON();
}