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
#include "SygaldryVisualOverlay.h"
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
    sygaldryA = 0;
    sygaldryB = 0;

    Register( "MoveType", &moveType );
    Register( "SygaldryA", &sygaldryA );
    Register( "SygaldryB", &sygaldryB );

    renderZ = 1;
    blocksOccupation = true;
    flammable = false;
    
    
    SygaldryVisualOverlay * vis = new SygaldryVisualOverlay( pos, (ResourceManager::GetInstance()).GetBitmap( "./res/Pot.png" ) );
    vis->SetSygaldry( sygaldryA, 0.0f, 1.0f, 0.0f );
    visual = vis;
}