/*
========================================================================

	A tile entity that is always on fire. One can interact with it to
    put an inventory item in the flames. It can only be added to a net
    by putting an inventory item with sygaldry into the camp fire.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "CampFire.h"
#include "ResourceManager.h"
#include "TileBitmapVisual.h"
#include "Utils.h"

using jsoncons::json;
using namespace MysticDave;

CampFire::CampFire() : TileEntity() {
    InitCampFire();
    name = type;
}

CampFire::CampFire( jsoncons::json jobj ) : TileEntity( jobj ) {
    InitCampFire();
}

CampFire::~CampFire() {
    // do nothing
}

void CampFire::InitCampFire() {
    type = "CampFire";

    renderZ = 1;
    blocksOccupation = true;
    flammable = true;
    fireDurationCounter = 0;
    
    visual = new TileBitmapVisual( pos, (ResourceManager::GetInstance()).GetBitmap( "./res/Woodpile.png" ));

}

