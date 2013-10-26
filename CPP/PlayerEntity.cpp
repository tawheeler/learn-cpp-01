/*
========================================================================

	A tile entity controlled by the player
	Mystic Dave!

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "PlayerEntity.h"
#include "AnimationVisual.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "Utils.h"
#include <string>
#include <map>
#include "Property.h"

using namespace MysticDave;

PlayerEntity::PlayerEntity() : TileEntity( "MysticDave", 1 ) {

	// TODO: fix UID 1 by default
    Init();

}

PlayerEntity::PlayerEntity( jsoncons::json jobj ) : TileEntity( jobj ) {
    Init();
}

PlayerEntity::~PlayerEntity() {
    // do nothing
}

void PlayerEntity::Init() {

    type = "PlayerEntity";

    renderZ = 1;
    blocksOccupation = true;
    flammable = true;

    animVis = new AnimationVisual( pos, (ResourceManager::GetInstance()).GetBitmap( "./res/Sprites/Dave2/Dave_S_L.png" ) );
	visual = animVis;

    sourceTileLoc = -1;
	dir = UTIL::DIR_SOUTH;
    Register( "dir", &dir );

	standingArr = new int[4];
	standingArr[UTIL::DIR_NORTH] = 3;
	standingArr[UTIL::DIR_EAST]  = 1;
	standingArr[UTIL::DIR_SOUTH] = 7;
	standingArr[UTIL::DIR_WEST]  = 29;

	TextureSheet * tex = (ResourceManager::GetInstance()).LoadTextureSheet("./res/Sprites/DaveSpriteSheet.png", TILE_DIM, TILE_DIM);

	Animation * animNorth = new Animation( 2, tex );
	animNorth->frameDurations[0] = 12; animNorth->frameIDs[0] = 11;
	animNorth->frameDurations[1] = 12; animNorth->frameIDs[1] = 3;
	animNorth->Init();
    animationMap["walkNorth"] = animNorth;

	Animation * animEast = new Animation( 2, tex );
	animEast->frameDurations[0] = 12; animEast->frameIDs[0] = 8;
	animEast->frameDurations[1] = 12; animEast->frameIDs[1] = 1;
	animEast->Init();
    animationMap["walkEast"] = animEast;

	Animation * animSouth = new Animation( 2, tex );
	animSouth->frameDurations[0] = 12; animSouth->frameIDs[0] = 15;
	animSouth->frameDurations[1] = 12; animSouth->frameIDs[1] = 7;
	animSouth->Init();
    animationMap["walkSouth"] = animSouth;

	Animation * animWest = new Animation( 2, tex );
	animWest->frameDurations[0] = 12; animWest->frameIDs[0] = 22;
	animWest->frameDurations[1] = 12; animWest->frameIDs[1] = 29;
	animWest->Init();
    animationMap["walkWest"] = animWest;

	Animation * animPushNorth = new Animation( 2, tex );
	animPushNorth->frameDurations[0] = 18; animPushNorth->frameIDs[0] = 6;
	animPushNorth->frameDurations[1] = 18; animPushNorth->frameIDs[1] = 25;
	animPushNorth->Init();
    animationMap["pushNorth"] = animPushNorth;

	Animation * animPushEast = new Animation( 2, tex );
	animPushEast->frameDurations[0] = 18; animPushEast->frameIDs[0] = 5;
	animPushEast->frameDurations[1] = 18; animPushEast->frameIDs[1] = 12;
	animPushEast->Init();
    animationMap["pushEast"] = animPushEast;

	Animation * animPushSouth = new Animation( 2, tex );
	animPushSouth->frameDurations[0] = 18; animPushSouth->frameIDs[0] = 20;
	animPushSouth->frameDurations[1] = 18; animPushSouth->frameIDs[1] = 21;
	animPushSouth->Init();
    animationMap["pushSouth"] = animPushSouth;

	Animation * animPushWest = new Animation( 2, tex );
	animPushWest->frameDurations[0] = 18; animPushWest->frameIDs[0] = 28;
	animPushWest->frameDurations[1] = 18; animPushWest->frameIDs[1] = 14;
	animPushWest->Init();
    animationMap["pushWest"] = animPushWest;

    Animation * animTryPushNorth = new Animation( 1, tex );
    animTryPushNorth->frameDurations[0] = 5; animTryPushNorth->frameIDs[0] = 6;
    animTryPushNorth->Init();
    animationMap["tryPushNorth"] = animTryPushNorth;

    Animation * animTryPushEast = new Animation( 1, tex );
    animTryPushEast->frameDurations[0] = 5; animTryPushEast->frameIDs[0] = 5;
    animTryPushEast->Init();
    animationMap["tryPushEast"] = animTryPushEast;

    Animation * animTryPushSouth = new Animation( 1, tex );
    animTryPushSouth->frameDurations[0] = 5; animTryPushSouth->frameIDs[0] = 20;
    animTryPushSouth->Init();
    animationMap["tryPushSouth"] = animTryPushSouth;

    Animation * animTryPushWest = new Animation( 1, tex );
    animTryPushWest->frameDurations[0] = 5; animTryPushWest->frameIDs[0] = 28;
    animTryPushWest->Init();
    animationMap["tryPushWest"] = animTryPushWest;
}

void PlayerEntity::Cleanup() {
	animVis = 0;

    std::map< std::string, Animation * >::iterator iter ;
    for ( iter = animationMap.begin(); iter != animationMap.end(); ) {
        delete iter->second;
        iter = animationMap.erase(iter);
    }

    TileEntity::Cleanup();
}

int PlayerEntity::GetDir() {
	return dir;
}

void PlayerEntity::SetDir( int dir ) {
	PlayerEntity::dir = dir;
	animVis->SetBitmap( (ResourceManager::GetInstance()).GetTextureSheet("./res/Sprites/DaveSpriteSheet.png")->GetTexture( standingArr[dir] ) );
    AddMotion( new Motion( pos, 0, 0, 8 ) ); // adds a little delay after turning
}

void PlayerEntity::PlayAnimation( std::string animName ) {
	animVis->PlayAnimation( animationMap[animName] );
}

bool PlayerEntity::IsPlayingAnimation() {
	return animVis->IsPlayingAnimation();
}

jsoncons::json PlayerEntity::GetJSON() {
    return TileEntity::GetJSON();
}