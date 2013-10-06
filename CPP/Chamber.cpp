/*
========================================================================

	A room in the world
	Composed of a grid of tiles (13 x 11)

========================================================================
*/

#include "Chamber.h"
#include "Globals.h"
#include "Utils.h"
#include "TileEntity.h"
#include "CampFire.h"

using jsoncons::json;
using namespace MysticDave;

int Chamber::CHAMBER_TILE_WIDTH = 13;
int Chamber::CHAMBER_TILE_HEIGHT = 11;

Chamber::Chamber( int chamberID ) {
	Chamber::chamberID = chamberID;
	
	tileWidth  = CHAMBER_TILE_WIDTH;
	tileHeight = CHAMBER_TILE_HEIGHT;
	numTiles   = tileWidth * tileHeight;

    tileImageAddrArr = new int[numTiles];
    tilePassableArr = new bool[numTiles];
    tileEntityTileListArr = new std::deque < TileEntity * >[numTiles];

    int chamberTileInd[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21,  6, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
					 40, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 42 };

	int ind = 0;
	for ( int y = 0; y < 11; y ++ ) {
		for ( int x = 0; x < 13; x ++ ) {
			tileImageAddrArr[ind] = chamberTileInd[ind];
			if ( x == 0 || x == 11 || y == 0 || y == 10 ) {
				tilePassableArr[ind] = false;
			}
			ind++;
		}
	}

	floorImage = 0;

	// TODO: make this not-hardcoded
	texSheet = new TextureSheet( "./res/BackgroundTiles.gif", 64, 64 );
    GenerateFloorImage();
}

Chamber::Chamber( jsoncons::json jobj ) {

    Chamber::chamberID = jobj["uid"].as_int();

    tileWidth  = Chamber::chamberID = jobj["tileWidth"].as_int();
	tileHeight = Chamber::chamberID = jobj["tileHeight"].as_int();
	numTiles   = tileWidth * tileHeight;

    //tileArr = new Tile[numTiles];
    tileImageAddrArr = new int[numTiles];
    tilePassableArr = new bool[numTiles];
    tileEntityTileListArr = new std::deque < TileEntity * >[numTiles];

    floorImage = 0;

    int i = 0;
    json tileImageAddrArrJSON = jobj["tileImageAddrArr"];
    for ( auto it = tileImageAddrArrJSON.begin_elements(); it != tileImageAddrArrJSON.end_elements(); ++it ) {
        tileImageAddrArr[i] = (*it).as_int();
        ++i;
    }

    i = 0;
    json tilePassableArrJSON = jobj["tilePassableArr"];
    for ( auto it = tilePassableArrJSON.begin_elements(); it != tilePassableArrJSON.end_elements(); ++it ) {
        tilePassableArr[i] = (*it).as_bool();
    }

    // extract plain entities
    json jEntities = jobj["entities"];
    for ( auto it = jEntities.begin_elements(); it != jEntities.end_elements(); ++it ) {
        entityList.push_back( new Entity(*it) );
    }

    // extract tile entities
    json jTileEntities = jobj["tileEntities"];
    for ( auto it = jTileEntities.begin_elements(); it != jTileEntities.end_elements(); ++it ) {

        if ( (*it)["type"].as_string().compare( "TileEntity" ) == 0 ) {
            AddTileEntity( new TileEntity( *it ) );
        } else if ( (*it)["type"].as_string().compare( "CampFire" ) == 0 ) {
            AddTileEntity( new CampFire( *it ) );
        }
        
    }

    // TODO: make this not-hardcoded
	texSheet = new TextureSheet( "./res/BackgroundTiles.gif", 64, 64 );
    GenerateFloorImage();
}

Chamber::~Chamber() {
    delete[] tileImageAddrArr;
    delete[] tilePassableArr;
    delete[] tileEntityTileListArr;  //okay to delete this; tile entities are appropriately deleted below
	
	if ( floorImage != 0 ) {
		al_destroy_bitmap( floorImage );
	}
	
	delete texSheet;

    std::deque < TileEntity * >::iterator iter;
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ) {
		(*iter)->Cleanup();
		delete (*iter);
		iter = tileEntityList.erase(iter);
	}
}

void Chamber::Cleanup() {
    // TODO: this
}
	
void Chamber::Update() {
    std::deque < TileEntity * >::iterator iter;
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ++iter ) {
		(*iter)->Update();
	}
}

void Chamber::Render( int x, int y ) {
	al_draw_bitmap( GetFloorImage(), 0, 0, 0 );

    std::deque < TileEntity * >::iterator iter;
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ++iter ) {
		if ( (*iter)->GetVisual() != 0 ) {
			(*iter)->GetVisual()->Render( x, y );
		}
	}
}

void Chamber::AddTileEntity( TileEntity * te ) {
    int tileX = UTIL::PixToGrid( te->GetPos()->x );
	int tileY = UTIL::PixToGrid( te->GetPos()->y );
    tileEntityTileListArr[GetTileNumFromPos(tileX, tileY)].push_back( te );
	tileEntityList.push_back( te );
}

void Chamber::AddTileEntity( TileEntity * te, int tileX, int tileY ) {
    int pixX = UTIL::GridToPix( tileX );
	int pixY = UTIL::GridToPix( tileY );
    te->GetPos()->Set( pixX, pixY );
    tileEntityTileListArr[GetTileNumFromPos(tileX, tileY)].push_back( te );
	tileEntityList.push_back( te );
}

int Chamber::GetTileWidth() const {
	return tileWidth;
}

int	Chamber::GetTileHeight() const {
	return tileHeight;
}

ALLEGRO_BITMAP * Chamber::GetFloorImage() const {
	return floorImage;
}

void Chamber::GenerateFloorImage() {
	
	// create an image if needed
	if ( floorImage == 0 ) {
		floorImage = al_create_bitmap( tileWidth*TILE_DIM, tileHeight*TILE_DIM );
	}

	// set the target to floorImage
	al_set_target_bitmap( floorImage );

	// render each Tile's image
	int ind = 0;
	for ( int y = 0; y < tileHeight; y ++ ) {
		for ( int x = 0; x < tileWidth; x ++ ) {
            texSheet->RenderTexture( tileImageAddrArr[ind], x*TILE_DIM, y*TILE_DIM );
			//texSheet->RenderTexture( (&(tileArr[ind]))->GetImageAddr(), x*TILE_DIM, y*TILE_DIM );
			ind ++;
		}
	}

	// return to drawing normally
	al_set_target_bitmap( al_get_backbuffer( al_get_current_display() ) );

}

bool Chamber::IsInChamber_Tile( int x, int y ) {
	return ( x >= 0 && x < tileWidth && y >= 0 && y < tileHeight );
}

bool Chamber::IsInChamber_Pixel( float x, float y ) {
	return ( x >= 0 && x < tileWidth*TILE_DIM && y >= 0 && y < tileHeight*TILE_DIM );
}

bool Chamber::CanTileBeEntered( int x, int y ) {
    bool retval = false;
    if ( !IsInChamber_Tile( x, y ) && tilePassableArr[GetTileNumFromPos(x,y)] ) {
        retval = true;

        //check associated list of tile entities for blocking
        retval = true;
        std::deque < TileEntity * > list = tileEntityTileListArr[GetTileNumFromPos(x,y)];
        std::deque < TileEntity * >::iterator iter;
	    for ( iter = list.begin(); iter != list.end(); ++iter ) {
            if ( (*iter)->BlocksOccupation() ) {
                retval = false;
                break;
            }
        }
    }
    return retval;
}

jsoncons::json Chamber::GetJSON() {

    json obj( json::an_object );

    obj["uid"]  = chamberID;
    obj["tileWidth"] = tileWidth;
    obj["tileHeight"] = tileHeight;

    json tileImageAddrArrJSON( json::an_array );
    json tilePassableArrJSON( json::an_array );
    for ( int i = 0; i < numTiles;  ++i ) {
        tileImageAddrArrJSON.add( tileImageAddrArr[i] );
        tilePassableArrJSON.add( tilePassableArr[i] );
    }
    obj["tileImageAddrArr"] = tileImageAddrArrJSON;
    obj["tilePassableArr"] = tilePassableArrJSON;

    // Add list of plain entities
    json entitiesJSON( json::an_array );
    std::deque < Entity * >::iterator iterA;
    for ( iterA = entityList.begin(); iterA != entityList.end(); ++iterA ) {
        entitiesJSON.add( (*iterA)->GetJSON() );
    }
    obj["entities"] = entitiesJSON;

    // Add list of tile entities
    json tileEntitiesJSON( json::an_array );
    std::deque < TileEntity * >::iterator iterB;
    for ( iterB = tileEntityList.begin(); iterB != tileEntityList.end(); ++iterB ) {
        tileEntitiesJSON.add( (*iterB)->GetJSON() );
    }
    obj["tileEntities"] = tileEntitiesJSON;

    return obj;
    
}