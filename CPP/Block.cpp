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
        imageIndex = 3;
        hardness = 0;
        break;
    case ( BLOCK_TYPE::STONE ):
        moveType = 1;
        flammable = false;
        imageIndex = 1;
        hardness = 1;
        break;
    case ( BLOCK_TYPE::ICE ):
        moveType = 2;
        flammable = false;
        imageIndex = 2;
        hardness = 0;
        break;
    case ( BLOCK_TYPE::METAL ):
        moveType = 1;
        flammable = false;
        imageIndex = 0;
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

void Block::OnMoveCompleted() {

    if ( moveType == 2 ) { // move type 2 keeps on sliding
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
            MoveDir( desDir, 36 );
        } else {
            sourceTileLoc = -1;
        }
    } else {
        sourceTileLoc = -1; // just forget where we came from
    }

}