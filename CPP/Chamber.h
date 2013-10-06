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

        void                                    Cleanup();
	    void									Update();
	    void									Render( int x, int y );

        void									GenerateFloorImage();

        bool									IsInChamber_Tile( int x, int y ); // whether the given tile point is in the chamber
        bool                                    IsInChamber_Pixel( float x, float y ); // whether the given pixel point is in the chamber

        bool                                    CanTileBeEntered( int x, int y );

	    void									AddTileEntity( TileEntity * te );
        void                                    AddEntity( Entity * e );
	
	    int										GetTileWidth() const;
	    int										GetTileHeight() const;
	    ALLEGRO_BITMAP *						GetFloorImage() const;

        jsoncons::json                          GetJSON();

        static int GetTileNumFromPos( int x, int y ) { return x + y * CHAMBER_TILE_WIDTH; };

    private:

        int	      								chamberID; // a unique chamber identifier

	    //Tile *									tileArr;     // array of tiles
	    int										numTiles;    // how many tiles we have
	    int										tileWidth;   // how many tiles wide the chamber is
	    int										tileHeight;  // how many tiles high the chamber is

        int *                                   tileImageAddrArr;  // array of image addresses for the chamber
        bool *                                  tilePassableArr; // array of tile impassability (if true, tile is fundamentally passable)

	    ALLEGRO_BITMAP *						floorImage;  // image created by tile base images
	    TextureSheet *							texSheet;    // texture sheet for the tiles

	    std::deque < TileEntity * >				tileEntityList; // list of all tile entities in the chamber
        
        std::deque < TileEntity * > *           tileEntityTileListArr; // array of tile entity lists for the tiles
        
        std::map< long,        Entity * >       entityUIDMap;     // maps UIDs to any entity in chamber (including Tile Entities)
        std::deque< Entity * >                  entityList;       // list of all plain entities (ie, does not include Tile Entities)

    };
}