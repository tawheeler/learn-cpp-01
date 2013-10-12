/*
========================================================================

	A tile entity that can be pushed around and etched on (has 2 spots)
    Standard movement of the block is 1 tile

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "StoneBlock.h"
#include "ResourceManager.h"
#include "AnimationVisual.h"
#include "Utils.h"

using jsoncons::json;
using namespace MysticDave;

StoneBlock::StoneBlock( std::string name, int uid ) : TileEntity( name, uid ) {
    InitStoneBlock();
}

StoneBlock::StoneBlock( jsoncons::json jobj ) : TileEntity( jobj ) {
    InitStoneBlock();

    json jPropertiesArr = jobj["properties"];
    moveType  = jPropertiesArr["MoveType"].as_int();
    sygaldryA = jPropertiesArr["SygaldryA"].as_int();
    sygaldryB = jPropertiesArr["SygaldryB"].as_int();
}

StoneBlock::~StoneBlock() {
    // do nothing
}

void StoneBlock::InitStoneBlock() {
    type = "StoneBlock";

    moveType = 1;
    sygaldryA = -1;
    sygaldryB = -1;

    Register( "MoveType", &moveType );
    Register( "SygaldryA", &sygaldryA );
    Register( "SygaldryB", &sygaldryB );

    renderZ = 1;
    blocksOccupation = true;
    flammable = false;
    
    visual = new AnimationVisual( pos, (ResourceManager::GetInstance()).GetBitmap( "./res/Pot.png" ) );
}