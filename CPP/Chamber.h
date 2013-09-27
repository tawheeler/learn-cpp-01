/*
========================================================================

	A room in the world
	Composed of a grid of tiles

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "Entity.h"
#include "TileEntity.h"
#include "Tile.h"
#include "TextureSheet.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <deque>
#include <map>
#include <string>
#include "jsoncons/json.hpp"

namespace MysticDave {
    class Chamber {

    public:

	    static int								CHAMBER_TILE_WIDTH;  // how many tiles wide the chamber is (13)
	    static int								CHAMBER_TILE_HEIGHT; // how many tiles tall the chamber is (11)

	    int                                     GetUID();

											    Chamber( int chamberID );
                                                Chamber( jsoncons::json jobj );
											    ~Chamber();

	    void									Update();
	    void									Render();

        void									GenerateFloorImage();

        bool									IsInChamber_Tile( int x, int y ); // whether the given tile point is in the chamber
        bool                                    IsInChamber_Pixel( float x, float y ); // whether the given pixel point is in the chamber

        bool                                    CanTileBeEntered( int x, int y );

	    void									AddTileEntity( TileEntity * te );
        void                                    AddEntity( Entity * e );
	
	    Tile *									GetTile( int x, int y );
	    int										GetTileWidth() const;
	    int										GetTileHeight() const;
	    ALLEGRO_BITMAP *						GetFloorImage() const;

        jsoncons::json                          GetJSON();

    private:

        int	      								chamberID; // a unique chamber identifier

	    Tile *									tileArr;     // array of tiles
	    int										numTiles;    // how many tiles we have
	    int										tileWidth;   // how many tiles wide the chamber is
	    int										tileHeight;  // how many tiles high the chamber is

	    ALLEGRO_BITMAP *						floorImage;  // image created by tile base images
	    TextureSheet *							texSheet;    // texture sheet for the tiles

	    std::deque < TileEntity * >				tileEntityList;
        
        std::map< std::string, Entity * >       entityStringMap;
        std::map< long,        Entity * >       entityUIDMap;
        std::deque< Entity * >                  entityList;

    };
}