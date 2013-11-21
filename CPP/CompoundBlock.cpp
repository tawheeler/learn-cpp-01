/*
========================================================================

	A component of a larger block

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "CompoundBlock.h"
#include "ResourceManager.h"
#include "SygaldryVisualOverlay.h"
#include "Utils.h"
#include "Globals.h"
#include "ChamberManager.h"
#include "ForceNet.h"

using jsoncons::json;
using namespace MysticDave;

CompoundBlock::CompoundBlock( int blocktype, int tileType ) : Block( blocktype ),
    tileType( tileType )
{
    InitCompoundBlock();
    name = type;
}

CompoundBlock::CompoundBlock( jsoncons::json jobj ) : Block( jobj ) {
    
    json jPropertiesArr = jobj["properties"];
    std::string tileTypeStr = jPropertiesArr["TileType"].as_string();
    
    if ( tileTypeStr.compare("NORTH_EDGE") == 0 ) {
        tileType = TILE_TYPE::NORTH_EDGE;
    } else if ( tileTypeStr.compare("NORTHEAST_CORNER") == 0 ) {
        tileType = TILE_TYPE::NORTHEAST_CORNER;
    } else if ( tileTypeStr.compare("EAST_EDGE") == 0 ) {
        tileType = TILE_TYPE::EAST_EDGE;
    } else if ( tileTypeStr.compare("SOUTHEAST_CORNER") == 0 ) {
        tileType = TILE_TYPE::SOUTHEAST_CORNER;
    } else if ( tileTypeStr.compare("SOUTH_EDGE") == 0 ) {
        tileType = TILE_TYPE::SOUTH_EDGE;
    } else if ( tileTypeStr.compare("SOUTHWEST_CORNER") == 0 ) {
        tileType = TILE_TYPE::SOUTHWEST_CORNER;
    } else if ( tileTypeStr.compare("WEST_EDGE") == 0 ) {
        tileType = TILE_TYPE::WEST_EDGE;
    } else if ( tileTypeStr.compare("NORTHWEST_CORNER") == 0 ) {
        tileType = TILE_TYPE::NORTHWEST_CORNER;
    } else if ( tileTypeStr.compare("CENTER") == 0 ) {
        tileType = TILE_TYPE::CENTER;
    } else if ( tileTypeStr.compare("NORTH_TERMINAL") == 0 ) {
        tileType = TILE_TYPE::NORTH_TERMINAL;
    } else if ( tileTypeStr.compare("EAST_TERMINAL") == 0 ) {
        tileType = TILE_TYPE::EAST_TERMINAL;
    } else if ( tileTypeStr.compare("SOUTH_TERMINAL") == 0 ) {
        tileType = TILE_TYPE::SOUTH_TERMINAL;
    } else if ( tileTypeStr.compare("WEST_TERMINAL") == 0 ) {
        tileType = TILE_TYPE::WEST_TERMINAL;
    } else if ( tileTypeStr.compare("VERTICAL") == 0 ) {
        tileType = TILE_TYPE::VERTICAL;
    } else if ( tileTypeStr.compare("HORIZONTAL") == 0 ) {
        tileType = TILE_TYPE::HORIZONTAL;
    }

    InitCompoundBlock();

    inherentSygaldry = jPropertiesArr["InherentSygaldry"].as_int();

}

CompoundBlock::~CompoundBlock() {
    // do nothing
}

void CompoundBlock::InitCompoundBlock() {

    type = "CompoundBlock";

    int imageIndexX = 0;
    int imageIndexY = 0;

    switch( tileType ) {
    case ( TILE_TYPE::NORTH_EDGE ):
        imageIndexX = 2;
        imageIndexY = 1;
        break;
    case ( TILE_TYPE::NORTHEAST_CORNER ):
        imageIndexX = 3;
        imageIndexY = 1;
        break;
    case ( TILE_TYPE::EAST_EDGE ):
        imageIndexX = 3;
        imageIndexY = 2;
        break;
    case ( TILE_TYPE::SOUTHEAST_CORNER ):
        imageIndexX = 3;
        imageIndexY = 3;
        break;
    case ( TILE_TYPE::SOUTH_EDGE ):
        imageIndexX = 2;
        imageIndexY = 3;
        break;
    case ( TILE_TYPE::SOUTHWEST_CORNER ):
        imageIndexX = 1;
        imageIndexY = 3;
        break;
    case ( TILE_TYPE::WEST_EDGE ):
        imageIndexX = 1;
        imageIndexY = 2;
        break;
    case ( TILE_TYPE::NORTHWEST_CORNER ):
        imageIndexX = 1;
        imageIndexY = 1;
        break;
    case ( TILE_TYPE::CENTER ):
        imageIndexX = 2;
        imageIndexY = 2;
        break;
    case ( TILE_TYPE::NORTH_TERMINAL ):
        imageIndexX = 0;
        imageIndexY = 1;
        break;
    case ( TILE_TYPE::EAST_TERMINAL ):
        imageIndexX = 2;
        imageIndexY = 0;
        break;
    case ( TILE_TYPE::SOUTH_TERMINAL ):
        imageIndexX = 0;
        imageIndexY = 3;
        break;
    case ( TILE_TYPE::WEST_TERMINAL ):
        imageIndexX = 0;
        imageIndexY = 0;
        break;
    case ( TILE_TYPE::VERTICAL ):
        imageIndexX = 0;
        imageIndexY = 2;
        break;
    case ( TILE_TYPE::HORIZONTAL ):
        imageIndexX = 1;
        imageIndexY = 0;
        break;
    }

    int multiplier = 0;
    switch( blockType ) {
    case ( BLOCK_TYPE::WOOD ):
        multiplier = 3;
        break;
    case ( BLOCK_TYPE::STONE ):
        multiplier = 1;
        break;
    case ( BLOCK_TYPE::ICE ):
        multiplier = 2;
        break;
    case ( BLOCK_TYPE::METAL ):
        multiplier = 0;
        break;
    }

    int imageIndex = imageIndexX + 4*multiplier + 16*imageIndexY;

    Register( "InherentSygaldry", &inherentSygaldry, true );
    Register( "TileType", &tileType, true );
   
    // get rid of Block visual
    visual->Cleanup();
    delete visual;

    // replace with a new one
    SygaldryVisualOverlay * vis = new SygaldryVisualOverlay( pos, (ResourceManager::GetInstance()).LoadTextureSheet("./res/Blocks.png", TILE_DIM, TILE_DIM )->GetTexture(imageIndex) );
    vis->SetSygaldry( sygaldry, 0.0f, 1.0f, 0.0f );
    visual = vis;
}