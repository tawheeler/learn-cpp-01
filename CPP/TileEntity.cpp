/*
========================================================================

	An entity which has a tile as its location

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "TileEntity.h"
#include "Utils.h"
#include "ForceNet.h"
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

    // remove self from chamber
    Chamber * C = (ChamberManager::GetInstance()).GetCurrentChamber();
    C->UnregisterTileEntityInTile( this, pos->GetTileX(), pos->GetTileY() );
    if ( sourceTileLoc != -1 ) {
        C->UnregisterTileEntityInTile( this, sourceTileLoc );
    }

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
            
            if ( sourceTileLoc != -1 ) {
                // grab current chamber and remove from location
                Chamber * curChamber = (ChamberManager::GetInstance()).GetCurrentChamber();
                curChamber->UnregisterTileEntityInTile( this, sourceTileLoc );
                
                // Call onExtited tile on all tile entities in previous tile
                curChamber->OnEntityExitedTile( this, sourceTileLoc );
                
                // Call onEntered tile on all tile entities except for this one in current tile
                curChamber->OnEntityEnteredTile( this, Chamber::GetTileNumFromPos( pos->GetTileX(), pos->GetTileY() ) );

                // Call onMoveCompleted on self
                OnMoveCompleted( curMotion );
            }

            delete curMotion;
        }

    }
}

void TileEntity::Render( int x, int y ) {
    if ( visual != 0 ) {
        visual->Render( x, y );
    }
}

void TileEntity::MoveDir( int dir, int ticksInMove ) {
    motionQueue.push_back( new Motion( pos, dir, ticksInMove ) ); 
	TileEntity::sourceTileLoc = Chamber::GetTileNumFromPos( pos->GetTileX(), pos->GetTileY() );
}
	
bool TileEntity::IsInMotion() const {
	return !motionQueue.empty();
}

bool TileEntity::CanMove( int dir, Chamber * C ) {
    int dx = UTIL::DirToXAdjustment( dir );
    int dy = UTIL::DirToYAdjustment( dir );
    int x = pos->GetTileX();
    int y = pos->GetTileY();
    return HasProperty("MoveType") && (Lookup( "MoveType" )->GetInt() != 0) && C->CanTileBeEntered( x + dx, y + dy );
}

void TileEntity::AddMotion( Motion * motion ) {
    motionQueue.push_back( motion );
}

void TileEntity::OnMoveCompleted( Motion * completedMotion ) {

    Chamber * curChamber = (ChamberManager::GetInstance()).GetCurrentChamber();
    bool stopping = true;
    ForceNet * fnet = curChamber->GetForceNetContaining( this->uid );

    // check whether the force net containing can still move
    if ( fnet != 0 ) {
        int moveType = fnet->CalcMoveType();
        if ( moveType == 2 ) { // will slide if possible

            int dir = completedMotion->GetDir();
            if ( fnet->CanMove( dir, curChamber ) ) {

                int tx = pos->GetTileX() + UTIL::DirToXAdjustment( dir );
                int ty = pos->GetTileY() + UTIL::DirToYAdjustment( dir );

                curChamber->RegisterTileEntityInTile( this, tx, ty );
                MoveDir( dir, completedMotion->GetTotalMotionTile() );

                stopping = false;
            }
        }
    } 

    if ( stopping ) {
        // forget previous location
        sourceTileLoc = -1;
    }
}

void TileEntity::OnInput( const std::string I ) {

    if ( I.compare( "EnableCollision" ) == 0 ) {
        // Sets the blocksOccupation to true
        blocksOccupation = true;
    } else if ( I.compare( "DisableCollision" ) == 0 ) {
        // Sets the blocksOccupation to false
        blocksOccupation = false;
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