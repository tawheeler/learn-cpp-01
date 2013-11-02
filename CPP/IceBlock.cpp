/*
========================================================================

	A tile entity that can be pushed around and etched on
    Standard movement of the block is for it to slide until it hits
    something

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "IceBlock.h"
#include "ResourceManager.h"
#include "SygaldryVisualOverlay.h"
#include "Utils.h"

using jsoncons::json;
using namespace MysticDave;

IceBlock::IceBlock( std::string name, int uid ) : TileEntity( name, uid ) {
    InitIceBlock();
}

IceBlock::IceBlock( jsoncons::json jobj ) : TileEntity( jobj ) {
    InitIceBlock();

    json jPropertiesArr = jobj["properties"];
    sygaldry = jPropertiesArr["Sygaldry"].as_int();
}

IceBlock::~IceBlock() {
    // do nothing
}

void IceBlock::InitIceBlock() {
    type = "IceBlock";

    moveType = 1;
    sygaldry = 0;

    Register( "MoveType", &moveType, false );
    Register( "Sygaldry", &sygaldry, true );

    renderZ = 1;
    blocksOccupation = true;
    flammable = false;
    
    
    SygaldryVisualOverlay * vis = new SygaldryVisualOverlay( pos, (ResourceManager::GetInstance()).GetBitmap( "./res/IceBlock.png" ) );
    vis->SetSygaldry( sygaldry, 0.0f, 1.0f, 0.0f );
    visual = vis;
}