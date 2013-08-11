/*
========================================================================

	An entity controlled by the player
	Mystic Dave!

========================================================================
*/

#include "PlayerEntity.h"
#include "AnimationVisual.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "Utils.h"

PlayerEntity::PlayerEntity() : TileEntity( TYPE_PLAYER, 1 ) {
	// TODO: fix UID 1 by default
	animVis = new AnimationVisual( pos, (ResourceManager::GetInstance()).GetBitmap( "./res/Sprites/Dave2/Dave_S_L.png" ) );
	visual = animVis;
	motion = 0;
	sourceTile = 0;
	dir = UTIL::DIR_SOUTH;

	standingArr = new int[4];
	standingArr[UTIL::DIR_NORTH] = 3;
	standingArr[UTIL::DIR_EAST]  = 1;
	standingArr[UTIL::DIR_SOUTH] = 7;
	standingArr[UTIL::DIR_WEST]  = 29;

	// note: resource manager will delete this
	TextureSheet * tex = (ResourceManager::GetInstance()).LoadTextureSheet("./res/Sprites/DaveSpriteSheet.png", TILE_DIM, TILE_DIM);

	animNorth = new Animation( 2, tex );
	animNorth->frameDurations[0] = 12; animNorth->frameIDs[0] = 11;
	animNorth->frameDurations[1] = 12; animNorth->frameIDs[1] = 3;
	animNorth->Init();

	animEast = new Animation( 2, tex );
	animEast->frameDurations[0] = 12; animEast->frameIDs[0] = 8;
	animEast->frameDurations[1] = 12; animEast->frameIDs[1] = 1;
	animEast->Init();

	animSouth = new Animation( 2, tex );
	animSouth->frameDurations[0] = 12; animSouth->frameIDs[0] = 15;
	animSouth->frameDurations[1] = 12; animSouth->frameIDs[1] = 7;
	animSouth->Init();

	animWest = new Animation( 2, tex );
	animWest->frameDurations[0] = 12; animWest->frameIDs[0] = 22;
	animWest->frameDurations[1] = 12; animWest->frameIDs[1] = 29;
	animWest->Init();

	animPushNorth = new Animation( 2, tex );
	animPushNorth->frameDurations[0] = 24; animPushNorth->frameIDs[0] = 6;
	animPushNorth->frameDurations[1] = 24; animPushNorth->frameIDs[1] = 25;
	animPushNorth->Init();

	animPushEast = new Animation( 2, tex );
	animPushEast->frameDurations[0] = 24; animPushEast->frameIDs[0] = 5;
	animPushEast->frameDurations[1] = 24; animPushEast->frameIDs[1] = 12;
	animPushEast->Init();

	animPushSouth = new Animation( 2, tex );
	animPushSouth->frameDurations[0] = 24; animPushSouth->frameIDs[0] = 20;
	animPushSouth->frameDurations[1] = 24; animPushSouth->frameIDs[1] = 21;
	animPushSouth->Init();

	animPushWest = new Animation( 2, tex );
	animPushWest->frameDurations[0] = 24; animPushWest->frameIDs[0] = 28;
	animPushWest->frameDurations[1] = 24; animPushWest->frameIDs[1] = 14;
	animPushWest->Init();
}

PlayerEntity::~PlayerEntity() {
	animVis = 0;
	sourceTile = 0;
	if ( motion != 0 ) {
		delete motion;
	}
	delete animNorth;
	delete animWest;
	delete animSouth;
	delete animEast;
}

int PlayerEntity::GetDir() {
	return dir;
}

void PlayerEntity::SetDir( int dir ) {
	PlayerEntity::dir = dir;
	animVis->SetBitmap( (ResourceManager::GetInstance()).GetTextureSheet("./res/Sprites/DaveSpriteSheet.png")->GetTexture( standingArr[dir] ) );
	motion = new Motion( pos, pos->x, pos->y, 8 );  // adds a little delay after turning
}

void PlayerEntity::PlayAnimation( Animation * anim ) {
	animVis->PlayAnimation( anim );
}

void PlayerEntity::Move( int dir, Tile * curTile ) {
	
	switch ( dir ) {
		case UTIL::DIR_NORTH:
			animVis->PlayAnimation( animNorth );
			motion = new Motion( pos, pos->x, pos->y - TILE_DIM, animNorth->totalDuration ); 
			break;
		case UTIL::DIR_EAST:  
			animVis->PlayAnimation( animEast );
			motion = new Motion( pos, pos->x + TILE_DIM, pos->y, animEast->totalDuration ); 
			break;
		case UTIL::DIR_SOUTH: 
			animVis->PlayAnimation( animSouth );
			motion = new Motion( pos, pos->x, pos->y + TILE_DIM, animSouth->totalDuration ); 
			break;
		case UTIL::DIR_WEST:  
			animVis->PlayAnimation( animWest );
			motion = new Motion( pos, pos->x - TILE_DIM, pos->y, animWest->totalDuration ); 
			break;
	}

	sourceTile = curTile;
}

void PlayerEntity::PushMove( int dir, Tile * curTile ) {
	
	switch ( dir ) {
		case UTIL::DIR_NORTH:
			animVis->PlayAnimation( animPushNorth );
			motion = new Motion( pos, pos->x, pos->y - TILE_DIM, animPushNorth->totalDuration ); 
			break;
		case UTIL::DIR_EAST:  
			animVis->PlayAnimation( animPushEast );
			motion = new Motion( pos, pos->x + TILE_DIM, pos->y, animPushEast->totalDuration ); 
			break;
		case UTIL::DIR_SOUTH: 
			animVis->PlayAnimation( animPushSouth );
			motion = new Motion( pos, pos->x, pos->y + TILE_DIM, animPushSouth->totalDuration ); 
			break;
		case UTIL::DIR_WEST:  
			animVis->PlayAnimation( animPushWest );
			motion = new Motion( pos, pos->x - TILE_DIM, pos->y, animPushWest->totalDuration ); 
			break;
	}

	sourceTile = curTile;
}

bool PlayerEntity::IsPlayingAnimation() {
	return animVis->IsPlayingAnimation();
}