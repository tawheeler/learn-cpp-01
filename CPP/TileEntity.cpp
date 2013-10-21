/*
========================================================================

	An entity which has a tile as its location

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "TileEntity.h"
#include "Utils.h"
#include "ChamberManager.h"

using jsoncons::json;
using namespace MysticDave;

TileEntity::TileEntity( std::string name, int uid ) : Entity( name, uid ) {
    Init();
    
    pos = new Vec2i();
	
}

TileEntity::TileEntity( jsoncons::json jobj ) : Entity ( jobj ) {

    Init();

    //renderZ = jobj["renderZ"].as_int();
    //blocksOccupation = jobj["blocksOccupation"].as_bool();
    //flammable = jobj["flammable"].as_bool();
    
    int x = jobj["x"].as_int();
    int y = jobj["y"].as_int();
    pos->Set( x, y );
}

TileEntity::~TileEntity() {
    // do nothing
}

void TileEntity::Init() {
    type = "TileEntity";

    renderZ = 1;
    blocksOccupation = false;
    flammable = false;

    sourceTileLoc = -1;

    visual = 0;
    pos = new Vec2i();
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

int TileEntity::GetClosestTileX() {
    return UTIL::PixToGrid( pos->x );
}

int TileEntity::GetClosestTileY() {
    return UTIL::PixToGrid( pos->y );
}

int TileEntity::GetClosestTileLoc() {
    return Chamber::GetTileNumFromPos( GetClosestTileX(), GetClosestTileY() );
}

void TileEntity::SetPosTile( int tileLoc ) {
    int x = Chamber::GetTileXFromNum( tileLoc );
    int y = Chamber::GetTileYFromNum( tileLoc );
    SetPosTile( x, y );
}

void TileEntity::SetPosTile( int tileX, int tileY ) {
    pos->Set( UTIL::GridToPix( tileX ), UTIL::GridToPix( tileY ) );
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
	
    // update the motion, if we have one
    if ( !motionQueue.empty() ) {

        Motion * curMotion = motionQueue.front();

        curMotion->Update();

        if ( curMotion->IsDone() ) {
            motionQueue.pop_front();
            delete curMotion;
            if ( sourceTileLoc != -1 ) {
                // grab current chamber and remove from location
                Chamber * curChamber = (ChamberManager::GetInstance()).GetCurrentChamber();
                curChamber->UnregisterTileEntityInTile( this, sourceTileLoc );
                
                // Call onExtited tile on all tile entities in previous tile
                curChamber->OnEntityExitedTile( this, sourceTileLoc );
                
                // Call onEntered tile on all tile entities except for this one in current tile
                curChamber->OnEntityEnteredTile( this, Chamber::GetTileNumFromPos( GetClosestTileX(), GetClosestTileY() ) );

                // forget where it came from
                sourceTileLoc = -1;
            }
        }

    }
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

void TileEntity::MoveDir( int dir, int sourceTileLoc, int ticksInMove ) {
	
	switch ( dir ) {
		case UTIL::DIR_NORTH:
            motionQueue.push_back( new Motion( pos, pos->x, pos->y - TILE_DIM, ticksInMove ) ); 
			break;
		case UTIL::DIR_EAST:  
			motionQueue.push_back( new Motion( pos, pos->x + TILE_DIM, pos->y, ticksInMove ) ); 
			break;
		case UTIL::DIR_SOUTH: 
			motionQueue.push_back( new Motion( pos, pos->x, pos->y + TILE_DIM, ticksInMove ) ); 
			break;
		case UTIL::DIR_WEST:  
			motionQueue.push_back( new Motion( pos, pos->x - TILE_DIM, pos->y, ticksInMove ) ); 
			break;
	}

	TileEntity::sourceTileLoc = sourceTileLoc;
}
	
bool TileEntity::IsInMotion() {
	return !motionQueue.empty();
}

void TileEntity::OnInput( const std::string I ) {

    if ( I.compare( "EnableCollision" ) == 0 ) {
        // Sets the blocksOccupation to true
        blocksOccupation = true;
    } else if ( I.compare( "DisableCollision" ) == 0 ) {
        // Sets the blocksOccupation to false
        blocksOccupation = false;
    } else if ( I.compare( "Kill" ) == 0 ) {
        // trigger base response
        Entity::OnInput( "Kill" );
        // also remove self from chamber
        Chamber * C = (ChamberManager::GetInstance()).GetCurrentChamber();
        C->UnregisterTileEntityInTile( this, GetClosestTileX(), GetClosestTileY() );
        if ( sourceTileLoc != -1 ) {
            C->UnregisterTileEntityInTile( this, sourceTileLoc );
        }
    } else {
        Entity::OnInput( I );
    }
}

jsoncons::json TileEntity::GetJSON() {

    json jobj = Entity::GetJSON();

    jobj["sourceTileLoc"] = sourceTileLoc;
    jobj["x"] = pos->x;
    jobj["y"] = pos->y;

    return jobj;
}