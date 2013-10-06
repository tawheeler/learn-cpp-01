/*
========================================================================

	An entity which has a tile as its location

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "TileEntity.h"
#include "Utils.h"

using jsoncons::json;
using namespace MysticDave;

TileEntity::TileEntity( std::string name, int uid ) : Entity( name, uid ) {
    renderZ = 1;
    sourceTileLoc = -1;

    blocksOccupation = false;
    flammable = false;

    pos = new Vec2i();
	visual = 0;
}

TileEntity::TileEntity( jsoncons::json jobj ) : Entity ( jobj ) {
    renderZ = jobj["renderZ"].as_int();
    sourceTileLoc = jobj["sourceTileLoc"].as_int();
    blocksOccupation = jobj["blocksOccupation"].as_bool();
    flammable = jobj["flammable"].as_bool();
    int x = jobj["x"].as_int();
    int y = jobj["y"].as_int();

    pos = new Vec2i( x, y );
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
    if ( visual != 0 ) {
        visual->Render( x, y );
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

    json jobj = Entity::GetJSON();

    jobj["renderZ"] = renderZ;
    jobj["sourceTileLoc"] = sourceTileLoc;
    jobj["blocksOccupation"] = blocksOccupation;
    jobj["flammable"] = flammable;
    jobj["x"] = pos->x;
    jobj["y"] = pos->y;
    jobj["type"] = "TileEntitiy";

    return jobj;
}