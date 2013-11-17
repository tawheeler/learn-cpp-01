/*
========================================================================

	A tile entity representing a patch of ice on the floor.
    Things travelling on an ice patch slide.

    If melted becomes a water puddle.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "IcePatch.h"
#include "ResourceManager.h"
#include "TileBitmapVisual.h"
#include "Utils.h"

using jsoncons::json;
using namespace MysticDave;

IcePatch::IcePatch( std::string name, int uid ) : TileEntity( name, uid ) {
    InitIcePatch();
}

IcePatch::IcePatch( jsoncons::json jobj ) : TileEntity( jobj ) {
    InitIcePatch();
}

IcePatch::~IcePatch() {
    // do nothing
}

void IcePatch::InitIcePatch() {
    type = "IcePatch";

    renderZ = 0;
    blocksOccupation = false;
    flammable = false;

    visual = new TileBitmapVisual( pos, (ResourceManager::GetInstance()).LoadTextureSheet( "./res/BackgroundTiles.gif", TILE_DIM, TILE_DIM )->GetTexture(115) );

}

