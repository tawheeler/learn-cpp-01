/*
========================================================================

	An entity controlled by the player
	Mystic Dave!

========================================================================
*/

#pragma once

#include "TileEntity.h"
#include "AnimationVisual.h"
#include "Animation.h"
#include "Motion.h"
#include "Tile.h"

class PlayerEntity : public TileEntity {

public:

						PlayerEntity();
						~PlayerEntity();

	int					GetDir();
	void				SetDir( int dir );

	void				PlayAnimation( Animation * anim );
	virtual void		Move( int dir, Tile * curTile ); // sets the player to move one tile in the specified direction
	void				PushMove( int dir, Tile * curTile );
	bool				IsPlayingAnimation();

private:

	AnimationVisual *	animVis;
	
	int					dir;         // the direction faced
	int *				standingArr; // images for the various directions

	Animation *			animNorth;
	Animation *			animEast;
	Animation *			animSouth;
	Animation *			animWest;

	Animation *			animPushNorth;
	Animation *			animPushEast;
	Animation *			animPushSouth;
	Animation *			animPushWest;

};