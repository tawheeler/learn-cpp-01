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
}

TileEntity::TileEntity( jsoncons::json jobj ) : Entity ( jobj ) {

    Init();

    //renderZ = jobj["renderZ"].as_int();
    //blocksOccupation = jobj["blocksOccupation"].as_bool();
    //flammable = jobj["flammable"].as_bool();
    
    int x = jobj["x"].as_int();
    int y = jobj["y"].as_int();
    pos->SetPosFromTile( x, y );
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
    pos = new Pos2D();
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

void TileEntity::SetVisual( Visual * visual ) {
    if ( visual != 0 ) {
        visual->Cleanup();
        delete visual;
    }
    TileEntity::visual = visual;
}

void TileEntity::Update() {
	Entity::Update();
	
    // update the motion, if we have one
    if ( !motionQueue.empty() ) {

        Motion * curMotion = motionQueue.front();

        curMotion->Update();

        if ( curMotion->IsDone() ) {
            motionQueue.pop_front();
            pos->SetToClosestTile();

            delete curMotion;
            if ( sourceTileLoc != -1 ) {
                // grab current chamber and remove from location
                Chamber * curChamber = (ChamberManager::GetInstance()).GetCurrentChamber();
                curChamber->UnregisterTileEntityInTile( this, sourceTileLoc );
                
                // Call onExtited tile on all tile entities in previous tile
                curChamber->OnEntityExitedTile( this, sourceTileLoc );
                
                // Call onEntered tile on all tile entities except for this one in current tile
                curChamber->OnEntityEnteredTile( this, Chamber::GetTileNumFromPos( pos->GetTileX(), pos->GetTileY() ) );

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

void TileEntity::HaltAllMotion( Motion * motion ) {
    //TODO: this
    // first blip Dave over to a tile
}

void TileEntity::MoveDir( int dir, int sourceTileLoc, int ticksInMove ) {
	
	switch ( dir ) {
		case UTIL::DIR_NORTH:
            motionQueue.push_back( new Motion( pos, 0, -TILE_DIM, ticksInMove ) ); 
			break;
		case UTIL::DIR_EAST:  
			motionQueue.push_back( new Motion( pos, TILE_DIM, 0, ticksInMove ) ); 
			break;
		case UTIL::DIR_SOUTH: 
			motionQueue.push_back( new Motion( pos, 0, TILE_DIM, ticksInMove ) ); 
			break;
		case UTIL::DIR_WEST:  
			motionQueue.push_back( new Motion( pos, -TILE_DIM, 0, ticksInMove ) ); 
			break;
	}

	TileEntity::sourceTileLoc = sourceTileLoc;
}
	
bool TileEntity::IsInMotion() const {
	return !motionQueue.empty();
}

void TileEntity::AddMotion( Motion * motion ) {
    motionQueue.push_back( motion );
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
        C->UnregisterTileEntityInTile( this, pos->GetTileX(), pos->GetTileY() );
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
    jobj["x"] = pos->GetTileX();
    jobj["y"] = pos->GetTileY();

    return jobj;
}