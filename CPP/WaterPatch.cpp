/*
========================================================================

	A tile entity representing a water puddle on the floor.

    If melted evaporates.
    If chilled becomes an ice patch.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "WaterPatch.h"
#include "IcePatch.h"
#include "ResourceManager.h"
#include "ChamberManager.h"
#include "TileBitmapVisual.h"
#include "Utils.h"

using jsoncons::json;
using namespace MysticDave;

WaterPatch::WaterPatch( std::string name, int uid ) : TileEntity( name, uid ) {
    InitWaterPatch();
}

WaterPatch::WaterPatch( jsoncons::json jobj ) : TileEntity( jobj ) {
    InitWaterPatch();
}

WaterPatch::~WaterPatch() {
    // do nothing
}

void WaterPatch::InitWaterPatch() {
    type = "WaterPatch";

    renderZ = 0;
    blocksOccupation = false;
    flammable = false;

    visual = new TileBitmapVisual( pos, (ResourceManager::GetInstance()).GetBitmap( "./res/WaterPatch.png" ) );

}

void WaterPatch::OnInput( const std::string I ) {

    if ( I.compare( "OnHeated" ) == 0 ) {
        // it evaporates
        OnInput( "Kill" );
    
    } else if ( I.compare( "OnChilled" ) == 0 ) {

        // it freezes into an ice patch
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

