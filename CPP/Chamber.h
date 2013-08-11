/*
========================================================================

	A room in the world
	Composed of a grid of tiles (12 x 11)

========================================================================
*/

#pragma once

#include "Tile.h"
#include "TextureSheet.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <deque>

class Chamber {

public:

	static int								CHAMBER_TILE_WIDTH;  // how many tiles wide the chamber is (12)
	static int								CHAMBER_TILE_HEIGHT; // how many tiles tall the chamber is (11)

	int										chamberID; // a unique chamber identifier

											Chamber( int chamberID );
											~Chamber();

	void									Update();
	void									Render();

	void									AddTileEntity( TileEntity * te );
	
	Tile *									GetTile( int x, int y );
	int										GetTileWidth() const;
	int										GetTileHeight() const;
	ALLEGRO_BITMAP *						GetFloorImage() const;

	void									GenerateFloorImage();

	bool									IsInChamber( int x, int y ); // whether point (in tilespace) is in chamber

private:

	Tile *									tileArr;     // array of tiles
	int										numTiles;    // how many tiles we have
	int										tileWidth;   // how many tiles wide the chamber is
	int										tileHeight;  // how many tiles high the chamber is

	ALLEGRO_BITMAP *						floorImage;  // image created by tile base images
	TextureSheet *							texSheet;    // texture sheet for the tiles

	std::deque < TileEntity * >				tileEntityList;
	std::deque < TileEntity * >::iterator	iter;
};