/*
========================================================================

	A tile entity that can be pushed around and etched on (has 2 spots)
    Standard movement of the block is 1 tile

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "Block.h"
#include "ResourceManager.h"
#include "SygaldryVisualOverlay.h"
#include "Utils.h"
#include "Globals.h"
#include "ChamberManager.h"
#include "ForceNet.h"
#include "IcePatch.h"
#include "ChamberManager.h"

using jsoncons::json;
using namespace MysticDave;

Block::Block( std::string name, int uid, int blocktype ) : TileEntity( name, uid ),
    blockType( blockType )
{
    InitBlock();
}

Block::Block( jsoncons::json jobj ) : TileEntity( jobj ) {
    
    json jPropertiesArr = jobj["properties"];
    std::string blockTypeStr = jPropertiesArr["BlockType"].as_string();
    
    if ( blockTypeStr.compare("STONE") == 0 ) {
        blockType = BLOCK_TYPE::STONE;
    } else if ( blockTypeStr.compare("ICE") == 0 ) {
        blockType = BLOCK_TYPE::ICE;
    } else if ( blockTypeStr.compare("WOOD") == 0 ) {
        blockType = BLOCK_TYPE::WOOD;
    } else if ( blockTypeStr.compare("METAL") == 0 ) {
        blockType = BLOCK_TYPE::METAL;
    }
    
    InitBlock();

    sygaldry = jPropertiesArr["Sygaldry"].as_int();
}

Block::~Block() {
    // do nothing
}

void Block::InitBlock() {

    type = "Block";
    sygaldry = 0;
    renderZ = 1;
    blocksOccupation = true;

    int imageIndex = 0;

    switch( blockType ) {
    case ( BLOCK_TYPE::WOOD ):
        moveType = 1;
        flammable = true;
        imageIndex = 15;
        hardness = 0;
        break;
    case ( BLOCK_TYPE::STONE ):
        moveType = 1;
        flammable = false;
        imageIndex = 7;
        hardness = 1;
        break;
    case ( BLOCK_TYPE::ICE ):
        moveType = 2;
        flammable = false;
        imageIndex = 11;
        hardness = 0;
        break;
    case ( BLOCK_TYPE::METAL ):
        moveType = 1;
        flammable = false;
        imageIndex = 3;
        hardness = 2;
        break;
    }

    Register( "BlockType", &blockType, true );
    Register( "Sygaldry", &sygaldry, true );

    Register( "MoveType", &moveType, false );
    Register( "Hardness", &hardness, false );
    
    SygaldryVisualOverlay * vis = new SygaldryVisualOverlay( pos, (ResourceManager::GetInstance()).LoadTextureSheet("./res/Blocks.png", TILE_DIM, TILE_DIM )->GetTexture(imageIndex) );
    vis->SetSygaldry( sygaldry, 0.0f, 1.0f, 0.0f );
    visual = vis;
}

void Block::OnInput( const std::string I ) {

    if ( I.compare( "OnHeated" ) == 0 && blockType == BLOCK_TYPE::ICE ) {

        // turn it into an ice patch!
        OnInput( "Kill" );
        IcePatch * icePatch = new IcePatch( "icepatch", Entity::GetNextUID() );
        icePatch->GetPos()->SetPosFromTile( pos->GetTileNum() ); // set it to the same location

        Chamber * curChamber = (ChamberManager::GetInstance()).GetCurrentChamber();
        curChamber->RegisterTileEntityInTile( icePatch, icePatch->GetPos()->GetTileX(), icePatch->GetPos()->GetTileY() );
        curChamber->AddTileEntity( icePatch );

    } else {
        TileEntity::OnInput( I );
    }
}

void Block::Update() {
    TileEntity::Update();

    if ( blockType == BLOCK_TYPE::WOOD ) {
        // if the block is on fire for too long
        if ( fireDurationCounter > 300 ) {
            OnInput( "Kill" );
        }
    }
    
}

//void Block::OnMoveCompleted( Motion * completedMotion ) {
//
//    Chamber * curChamber = (ChamberManager::GetInstance()).GetCurrentChamber();
//    bool stopping = true;
//    ForceNet * fnet = curChamber->GetForceNetContaining( this->uid );
//
//    // check whether the force net containing can still move
//    if ( fnet != 0 ) {
//        int fnetMoveType = fnet->CalcMoveType();
//        if ( fnetMoveType == 2 ) { // will slide if possible
//
//            int dir = completedMotion->GetDir();
//            if ( fnet->CanMove( dir, curChamber ) ) {
//
//                int tx = pos->GetTileX() + UTIL::DirToXAdjustment( dir );
//                int ty = pos->GetTileY() + UTIL::DirToYAdjustment( dir );
//
//                curChamber->RegisterTileEntityInTile( this, tx, ty );
//                MoveDir( dir, completedMotion->GetTotalMotionTime() );
//
//                stopping = false;
//            }
//        }
//    } 
//    else if ( moveType == 2 ) { // move type 2 keeps on sliding
//        Chamber * curChamber = (ChamberManager::GetInstance()).GetCurrentChamber();
//
//        int cx = pos->GetTileX();
//        int cy = pos->GetTileY();
//        int dx = cx - Chamber::GetTileXFromNum( sourceTileLoc );
//        int dy = cy - Chamber::GetTileYFromNum( sourceTileLoc );
//        int tx = cx + dx;
//        int ty = cy + dy;
//        int desDir = UTIL::DirFromDelta( dx, dy );
//
//        if ( curChamber->CanTileBeEntered( tx, ty ) ) { //if it can slide through into the next space
//            curChamber->RegisterTileEntityInTile( this, tx, ty );
//            MoveDir( desDir, 36 );
//            stopping = false;
//        } 
//    }
//
//    if ( stopping ) {
//        // forget previous location
//        sourceTileLoc = -1;
//    }
//
//}