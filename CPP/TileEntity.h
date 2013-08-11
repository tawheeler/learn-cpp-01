/*
========================================================================

	An entity which has a tile as its location

========================================================================
*/

#pragma once

#include "Entity.h"
#include "Vec2i.h"
#include "Visual.h"
//#include "RuneSpace.h"
#include "Motion.h"
#include "Tile.h"

class TileEntity : public Entity {
public:

	bool				blocksOccupation;

						TileEntity( int type );
						TileEntity( int type, int uid );
						~TileEntity();

	Vec2i *				pos; // position in pixel space

	int					tileX;  // position in tile space
	int					tileY;

	void				SetTilePosToMatchPixPos(); // matches tile position from pixel position
	void				SetPixPosToMatchTilePos();

	Visual*				visual;
	//RuneSpace*			runeSpace;

	virtual void		Update();
	virtual void		Cleanup();

	void				AddMotion( Motion * motion );
	virtual void 		Move( int dir, Tile * curTile ); // sets the player to move one tile in the specified direction

	bool				IsInMotion();

protected:
	
	Motion *			motion;
	Tile *				sourceTile;
	
};