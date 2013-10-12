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
#include "Utils.h"

using jsoncons::json;
using namespace MysticDave;

CampFire::CampFire( std::string name, int uid ) : TileEntity( name, uid ) {
    InitCampFire();
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
    flammable = false;
    
    animVis = new AnimationVisual( pos, (ResourceManager::GetInstance()).GetBitmap( "./res/CampfireSprite.png" ) );
	visual = animVis;

    fireFlickerAnim = new Animation( 2, (ResourceManager::GetInstance()).LoadTextureSheet("./res/CampfireSpriteSheet.gif", TILE_DIM, TILE_DIM) );
	fireFlickerAnim->frameDurations[0] = 10; fireFlickerAnim->frameIDs[0] = 0;
	fireFlickerAnim->frameDurations[1] = 10; fireFlickerAnim->frameIDs[1] = 1;
	fireFlickerAnim->Init();
}

void CampFire::Update() {

    // repeat the animation if it is not playing
    if ( !(animVis->IsPlayingAnimation()) ) {
        animVis->PlayAnimation( fireFlickerAnim );
    }
}

