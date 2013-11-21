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
#include "WaterPatch.h"
#include "ResourceManager.h"
#include "ChamberManager.h"
#include "TileBitmapVisual.h"
#include "Utils.h"

using jsoncons::json;
using namespace MysticDave;

IcePatch::IcePatch() : TileEntity() {
    InitIcePatch();
    name = type;
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

void IcePatch::OnInput( const std::string I ) {

    if ( I.compare( "OnHeated" ) == 0 ) {
        // it melts
        OnInput( "Kill" );

        // create a water patch

        Chamber * curChamber = (ChamberManager::GetInstance()).GetCurrentChamber();
        WaterPatch * waterPatch = new WaterPatch();
        waterPatch->GetPos()->SetPosFromTile( pos->GetTileNum() ); // set it to the same location

        curChamber->AddTileEntity( waterPatch );
        curChamber->RegisterTileEntityInTile( waterPatch, waterPatch->GetPos()->GetTileX(), waterPatch->GetPos()->GetTileY() );

    } else {
        TileEntity::OnInput( I );
    }
}

