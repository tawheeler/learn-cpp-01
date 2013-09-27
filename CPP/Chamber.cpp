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

using namespace MysticDave;
using jsoncons::json;

int Chamber::CHAMBER_TILE_WIDTH = 13;
int Chamber::CHAMBER_TILE_HEIGHT = 11;

Chamber::Chamber( int chamberID ) {
	Chamber::chamberID = chamberID;
	
	tileWidth  = CHAMBER_TILE_WIDTH;
	tileHeight = CHAMBER_TILE_HEIGHT;
	numTiles   = tileWidth * tileHeight;

	tileArr = new Tile[numTiles];

	floorImage = 0;

	// TODO: make this not-hardcoded
	texSheet = new TextureSheet( "./res/BackgroundTiles.gif", 64, 64 );
}

Chamber::Chamber( jsoncons::json jobj ) {

    Chamber::chamberID = jobj["uid"].as_int();

    tileWidth  = Chamber::chamberID = jobj["tileWidth"].as_int();
	tileHeight = Chamber::chamberID = jobj["tileHeight"].as_int();
	numTiles   = tileWidth * tileHeight;

    tileArr = new Tile[numTiles];
    floorImage = 0;

    json jtileArr = jobj["tileArr"];
    int i = 0;
    for (auto it = jtileArr.begin_elements(); it != jtileArr.end_elements(); ++it)
    {
        tileArr[i] = it->as_int();
        ++i;
    }

    // TODO: make this not-hardcoded
	texSheet = new TextureSheet( "./res/BackgroundTiles.gif", 64, 64 );
}

Chamber::~Chamber() {
	delete[] tileArr;
	
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
	
void Chamber::Update() {
    std::deque < TileEntity * >::iterator iter;
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ++iter ) {
		(*iter)->Update();
	}
}

void Chamber::Render() {
	al_draw_bitmap( GetFloorImage(), 0, 0, 0 );

    std::deque < TileEntity * >::iterator iter;
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ++iter ) {
		if ( (*iter)->GetVisual() != 0 ) {
			(*iter)->GetVisual()->Render();
		}
	}
}

void Chamber::AddTileEntity( TileEntity * te ) {
	/* TODO: this
    int tileX = UTIL::PixToGrid( te->GetPos()->x );
	int tileY = UTIL::PixToGrid( te->GetPos()->y );
	tileArr[tileX + tileY*tileWidth].tileEntity = te;
	
	tileEntityList.push_back( te );
    */
}

Tile * Chamber::GetTile( int x, int y ) {
	return &(tileArr[x + y*tileWidth]);
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
			texSheet->RenderTexture( (&(tileArr[ind]))->imageAddr, x*TILE_DIM, y*TILE_DIM );
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

jsoncons::json Chamber::GetJSON() {

    json obj( json::an_object );

    obj["uid"]  = chamberID;
    obj["tileWidth"] = tileWidth;
    obj["tileHeight"] = tileHeight;

    json jtileArr( json::an_array );
    for ( int i = 0; i < numTiles; ++i ) {
        jtileArr.add( tileArr[i].imageAddr );
    }

    obj["tileArr"] = jtileArr;

    return obj;
    
}