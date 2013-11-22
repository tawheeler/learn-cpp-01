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
#include "ResourceManager.h"

using jsoncons::json;
using namespace MysticDave;

TileEntity::TileEntity() : Entity() {
    Init();
    name = type;
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

    fireDurationCounter = -1;
    visual = 0;
    pos = new Pos2D();

    fireFlickerVisual = new AnimationVisual( pos, (ResourceManager::GetInstance()).LoadTextureSheet( "./res/FireSprite.png", TILE_DIM, TILE_DIM )->GetTexture(1) );

    fireFlickerAnim = new Animation( 2, (ResourceManager::GetInstance()).LoadTextureSheet("./res/FireSprite.png", TILE_DIM, TILE_DIM) );
	fireFlickerAnim->frameDurations[0] = 10; fireFlickerAnim->frameIDs[0] = 0;
	fireFlickerAnim->frameDurations[1] = 10; fireFlickerAnim->frameIDs[1] = 1;
	fireFlickerAnim->Init();
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

    // fire flicker
    fireFlickerVisual->Cleanup();
    delete fireFlickerVisual;
    delete fireFlickerAnim;

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
	
    // update the fire flicker
    if ( IsOnFire() ) {
        fireDurationCounter++;
        if ( !(fireFlickerVisual->IsPlayingAnimation()) ) {
            fireFlickerVisual->PlayAnimation( fireFlickerAnim );
        }
    }

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
    if ( IsOnFire() ) {
        fireFlickerVisual->Render( x, y );
    }
}

void TileEntity::MoveDir( int dir, int ticksInMove ) {
    motionQueue.push_back( new Motion( pos, dir, ticksInMove ) ); 
	TileEntity::sourceTileLoc = Chamber::GetTileNumFromPos( pos->GetTileX(), pos->GetTileY() );
}
	
Motion * TileEntity::GetCurrentMotion() {
    if ( !(motionQueue.empty()) ) {
        return motionQueue.front();
    }
    return 0;
}

int TileEntity::GetTemperature() {
    if ( IsOnFire() ) {
        return TEMPERATURE::HOT;
    } else {
        return TEMPERATURE::NEUTRAL;
    }
}

bool TileEntity::IsInMotion() const {
	return !motionQueue.empty();
}

bool TileEntity::CanMove( int dir, Chamber * C ) {
    int dx = UTIL::DirToXAdjustment( dir );
    int dy = UTIL::DirToYAdjustment( dir );
    int x = pos->GetTileX();
    int y = pos->GetTileY();

    if ( HasProperty("MoveType") && (Lookup( "MoveType" )->GetInt() != 0) ) {
        if ( C->CanTileBeEntered( x + dx, y + dy ) ) { // space is open
            return true;
        } else { // space is not open
            // check if what is blocking us is part of the same fnet
            Chamber * curChamber = (ChamberManager::GetInstance()).GetCurrentChamber();
            ForceNet * fnet = curChamber->GetForceNetContaining( this->uid );
            TileEntity * pushable = curChamber->GetEntityWithPropertyInTile( "MoveType", Chamber::GetTileNumFromPos( x + dx, y + dy) );
            if ( pushable != 0 && fnet != 0 && fnet->Contains( pushable->GetUID() ) ) {
                return true;
            }
        }
    }

    return false;
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
                MoveDir( dir, completedMotion->GetTotalMotionTime() );

                stopping = false;
            }
        }
    } else if ( (HasProperty("MoveType") && Lookup("MoveType")->GetInt() == 2) // can move do to having move type 2
                || (curChamber->GetEntityOfTypeInTile( "IcePatch", Chamber::GetTileNumFromPos(pos->GetTileX(), pos->GetTileY()) ) != 0) ) {  // can move due to being on ice patch
        
        Chamber * curChamber = (ChamberManager::GetInstance()).GetCurrentChamber();

        int cx = pos->GetTileX();
        int cy = pos->GetTileY();
        int dx = cx - Chamber::GetTileXFromNum( sourceTileLoc );
        int dy = cy - Chamber::GetTileYFromNum( sourceTileLoc );
        int tx = cx + dx;
        int ty = cy + dy;
        int desDir = UTIL::DirFromDelta( dx, dy );

        if ( curChamber->CanTileBeEntered( tx, ty ) ) { //if it can slide through into the next space
            curChamber->RegisterTileEntityInTile( this, tx, ty );
            MoveDir( desDir, completedMotion->GetTotalMotionTime() );
            stopping = false;
        } 
    }

    if ( stopping ) {
        // forget previous location
        sourceTileLoc = -1;
    }

    // don't forget to calculate conduction nets
    curChamber->CalcConductionNets( this );
}

void TileEntity::OnInput( const std::string I ) {

    if ( I.compare( "EnableCollision" ) == 0 ) {
        // Sets the blocksOccupation to true
        blocksOccupation = true;
    } else if ( I.compare( "DisableCollision" ) == 0 ) {
        // Sets the blocksOccupation to false
        blocksOccupation = false;
    } else if ( I.compare( "OnHeated" ) == 0 ) {
        // set it on fire if it is flammable
        if( flammable ) {
            fireDurationCounter = 0; // set on fire!
        }
    } else if ( I.compare( "OnChilled" ) == 0 ) {
        fireDurationCounter = -1; // extinguish fire
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