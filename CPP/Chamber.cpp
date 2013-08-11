/*
========================================================================

	A room in the world
	Composed of a grid of tiles (12 x 11)

========================================================================
*/

#include "Chamber.h"
#include "Globals.h"
#include "Utils.h"
#include "TileEntity.h"

int Chamber::CHAMBER_TILE_WIDTH = 12;
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

Chamber::~Chamber() {
	delete[] tileArr;
	
	if ( floorImage != 0 ) {
		al_destroy_bitmap( floorImage );
	}
	
	delete texSheet;

	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ) {
		(*iter)->Cleanup();
		delete (*iter);
		iter = tileEntityList.erase(iter);
	}
}
	
void Chamber::Update() {
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ++iter ) {
		(*iter)->Update();
	}
}

void Chamber::Render() {
	al_draw_bitmap( GetFloorImage(), 0, 0, 0 );
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ++iter ) {
		if ( (*iter)->visual != 0 ) {
			(*iter)->visual->Render();
		}
	}
}

void Chamber::AddTileEntity( TileEntity * te ) {
	int tileX = UTIL::PixToGrid( te->pos->x );
	int tileY = UTIL::PixToGrid( te->pos->y );
	tileArr[tileX + tileY*tileWidth].tileEntity = te;
	
	tileEntityList.push_back( te );
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

bool Chamber::IsInChamber( int x, int y ) {
	return ( x >= 0 && x < tileWidth && y >= 0 && y < tileHeight );
}