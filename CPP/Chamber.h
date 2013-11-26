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
#include "TextureSheet.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <list>
#include <map>
#include <string>
#include "jsoncons/json.hpp"

namespace MysticDave {

    class ForceNet;

    class Chamber {

    public:

	    static int								CHAMBER_TILE_WIDTH;  // how many tiles wide the chamber is (13)
	    static int								CHAMBER_TILE_HEIGHT; // how many tiles tall the chamber is (11)

											    Chamber( int chamberID );
                                                Chamber( jsoncons::json jobj );
											    ~Chamber();

        int                                     GetUID() { return chamberID; }

        void                                    Cleanup();
	    void									Update();
	    void									Render( int x, int y );

        void									GenerateFloorImage();

        bool									IsInChamber_Tile( int x, int y ); // whether the given tile point is in the chamber
        bool									IsInChamber_Tile( int tileNum ); // whether the given tile point is in the chamber
        bool                                    IsInChamber_Pixel( float x, float y ); // whether the given pixel point is in the chamber

        bool                                    CanTileBeEntered( int x, int y );
        bool                                    HasEntityInMotion();

        void                                    AddEntity( Entity * e );
	    void									AddTileEntity( TileEntity * te );
        void									RegisterTileEntityInTile( TileEntity * te, int tileX, int tileY ); //place it at the given tile loc
        void									RegisterTileEntityInTile( TileEntity * te, int tileNum );
        
        void                                    RemoveEntity( Entity * e );
        void                                    RemoveTileEntity( TileEntity * te );
        void                                    UnregisterTileEntityInTile( TileEntity * te, int tileX, int tileY );
        void                                    UnregisterTileEntityInTile( TileEntity * te, int tileNum );
	
	    int										GetTileWidth() const;
	    int										GetTileHeight() const;
	    ALLEGRO_BITMAP *						GetFloorImage() const;

        Entity *                                GetEntity( int uid );
        Entity *                                GetEntity( std::string name );
        TileEntity *                            GetEntityOfTypeInTile( std::string type, int tileNum );
        TileEntity *                            GetEntityWithPropertyInTile( std::string propertyName, int tileNum );
        std::list < TileEntity * > *            GetEntitiesInTile( int tileNum );
        std::list < int >                       GetTilesContainingTileEntity( int tileEntityID );

        void                                    CalcForceNets();
        void                                    CalcConductionNets( TileEntity * te );
        ForceNet *                              GetForceNetContaining( int uid );

        void                                    OnEntityExitedTile( TileEntity * actor, int tileLoc ); // Call onExtited tile on all tile entities in given tile
        void                                    OnEntityEnteredTile( TileEntity * actor, int tileLoc ); // Call onEntered tile on all tile entities in given tile

        int                                     GetNextUID();

        jsoncons::json                          GetJSON();

        static int GetTileNumFromPos( int x, int y ) { return x + y * CHAMBER_TILE_WIDTH; }
        static int GetTileXFromNum( int n ) { return n % CHAMBER_TILE_WIDTH; }
        static int GetTileYFromNum( int n ) { return n / CHAMBER_TILE_WIDTH; }

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

	    std::list < TileEntity * >				tileEntityList; // list of all tile entities in the chamber
        
        std::list < TileEntity * > *            tileEntityTileListArr; // array of tile entity lists for the tiles
        
        std::map< int, Entity * >               entityUIDMap;     // maps UIDs to any entity in chamber (including Tile Entities)
        std::list< Entity * >                   entityList;       // list of all plain entities (ie, does not include Tile Entities)

        std::list< ForceNet * >                 forceNetList;     // list of force nets

        bool                                    EntityPassesSpawnCondition( jsoncons::json * entityJSON );

    };
}