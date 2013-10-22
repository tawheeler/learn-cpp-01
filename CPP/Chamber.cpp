/*
========================================================================

	A room in the world
	Composed of a grid of tiles (13 x 11)

========================================================================
*/

#include "Chamber.h"
#include "Globals.h"
#include "ForceNet.h"
#include "Utils.h"
#include "TileEntity.h"
#include "CampFire.h"
#include "StoneBlock.h"
#include "Trigger.h"
#include "TransitionEntity.h"
#include "LogManager.h"
#include <assert.h>

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
    tileEntityTileListArr = new std::list < TileEntity * >[numTiles];

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
			if ( x == 0 || x == 12 || y == 0 || y == 10 ) {
				tilePassableArr[ind] = false;
			} else {
                tilePassableArr[ind] = true;
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

    tileWidth  = jobj["tileWidth"].as_int();
	tileHeight = jobj["tileHeight"].as_int();
	numTiles   = tileWidth * tileHeight;

    //tileArr = new Tile[numTiles];
    tileImageAddrArr = new int[numTiles];
    tilePassableArr = new bool[numTiles];
    tileEntityTileListArr = new std::list < TileEntity * >[numTiles];

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
        ++i;
    }

    // extract plain entities
    json jEntities = jobj["entities"];
    for ( auto it = jEntities.begin_elements(); it != jEntities.end_elements(); ++it ) {
        entityList.push_back( new Entity(*it) );
    }

    // extract tile entities
    json jTileEntities = jobj["tileEntities"];
    for ( auto it = jTileEntities.begin_elements(); it != jTileEntities.end_elements(); ++it ) {

        TileEntity * te = 0;
        if ( (*it)["type"].as_string().compare( "TileEntity" ) == 0 ) {
            te = new TileEntity( *it );
        } else if ( (*it)["type"].as_string().compare( "CampFire" ) == 0 ) {
            te = new CampFire( *it );
        } else if ( (*it)["type"].as_string().compare( "StoneBlock" ) == 0 ) {
            te = new StoneBlock( *it );
        } else if ( (*it)["type"].as_string().compare( "Trigger" ) == 0 ) {
            te = new Trigger( *it );
        } else if ( (*it)["type"].as_string().compare( "TransitionEntity" ) == 0 ) {
            te = new TransitionEntity( *it );
        }

        if ( te != 0 ) {
            RegisterTileEntityInTile( te, te->GetClosestTileX(), te->GetClosestTileY() );
            AddTileEntity( te );
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

    std::list < TileEntity * >::iterator iter;
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ) {
		(*iter)->Cleanup();
		delete (*iter);
		iter = tileEntityList.erase(iter);
	}

    std::list < Entity * >::iterator iter2;
	for ( iter2 = entityList.begin(); iter2 != entityList.end(); ) {
		(*iter2)->Cleanup();
		delete (*iter2);
		iter2 = entityList.erase(iter2);
	}

    std::list < ForceNet * >::iterator iterFNet;
	for ( iterFNet = forceNetList.begin(); iterFNet != forceNetList.end(); ) {
		delete (*iterFNet);
		iterFNet = forceNetList.erase(iterFNet);
	}
}

void Chamber::Cleanup() {
    // TODO: this
}
	
void Chamber::Update() {
    std::list < TileEntity * >::iterator iter;
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ) {
        if ( (*iter)->ShouldBeRemoved() ) {
            (*iter)->Cleanup();
            delete  (*iter);
            iter = tileEntityList.erase(iter);
        } else {
		    (*iter)->Update();
            ++iter;
        }
	}

    std::list < Entity * >::iterator iter2;
    for ( iter2 = entityList.begin(); iter2 != entityList.end(); ++iter2 ) {
        if ( (*iter2)->ShouldBeRemoved() ) {
            (*iter2)->Cleanup();
            delete  (*iter2);
            iter2 = entityList.erase(iter2);
        } else {
		    (*iter2)->Update();
            ++iter2;
        }
    }
}

void Chamber::Render( int x, int y ) {
	al_draw_bitmap( GetFloorImage(), -x, -y, 0 );

    std::list < TileEntity * >::iterator iter;
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ++iter ) {
		if ( (*iter)->GetVisual() != 0 ) {
			(*iter)->GetVisual()->Render( x, y );
		}
	}
}

void Chamber::AddEntity( Entity * e) {
    entityList.push_back( e );
    entityUIDMap[ e->GetUID() ] = e;
}

void Chamber::AddTileEntity( TileEntity * te ) {
    tileEntityList.push_back( te );
    entityUIDMap[ te->GetUID() ] = te;
}

void Chamber::RegisterTileEntityInTile( TileEntity * te, int tileX, int tileY ) {
    // TODO: insert in list in order of zbuffer
    tileEntityTileListArr[GetTileNumFromPos(tileX, tileY)].push_back( te );
}

void Chamber::RegisterTileEntityInTile( TileEntity * te, int tileNum ) {
    // TODO: insert in list in order of zbuffer
    tileEntityTileListArr[tileNum].push_back( te );
}

void Chamber::RemoveEntity( Entity * e ) {
    entityList.remove( e );
}

void Chamber::RemoveTileEntity( TileEntity * te ) {
    tileEntityList.remove( te );
}

void Chamber::UnregisterTileEntityInTile( TileEntity * te, int tileX, int tileY ) {
    tileEntityTileListArr[GetTileNumFromPos(tileX, tileY)].remove( te );
}

void Chamber::UnregisterTileEntityInTile( TileEntity * te, int tileNum ) {
    tileEntityTileListArr[tileNum].remove( te );
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

bool Chamber::IsInChamber_Tile( int tileNum ) {
	return IsInChamber_Tile( Chamber::GetTileXFromNum(tileNum), Chamber::GetTileYFromNum(tileNum) );
}

bool Chamber::IsInChamber_Tile( int x, int y ) {
	return ( x >= 0 && x < tileWidth && y >= 0 && y < tileHeight );
}

bool Chamber::IsInChamber_Pixel( float x, float y ) {
	return ( x >= 0 && x < tileWidth*TILE_DIM && y >= 0 && y < tileHeight*TILE_DIM );
}

bool Chamber::CanTileBeEntered( int x, int y ) {
    bool retval = false;
    if ( IsInChamber_Tile( x, y ) && tilePassableArr[GetTileNumFromPos(x,y)] ) {
        retval = true;

        //check associated list of tile entities for blocking
        std::list < TileEntity * > list = tileEntityTileListArr[GetTileNumFromPos(x,y)];
        std::list < TileEntity * >::iterator iter;
	    for ( iter = list.begin(); iter != list.end(); ++iter ) {
            if ( (*iter)->BlocksOccupation() ) {
                retval = false;
                break;
            }
        }
    }
    return retval;
}

Entity * Chamber::GetEntity( int uid ) {
    std::map< int, Entity *>::iterator pos = entityUIDMap.find(uid);
    //assert(pos != entityUIDMap.end());
    if ( pos == entityUIDMap.end() ) {
        return 0;
    }
    return pos->second;
}

TileEntity * Chamber::GetEntityWithPropertyInTile( std::string propertyName, int tileNum ) {
    TileEntity * retval = 0;

    if ( IsInChamber_Tile( tileNum ) ) {
        std::list < TileEntity * > list = tileEntityTileListArr[tileNum];
        std::list < TileEntity * >::iterator iter;
	    for ( iter = list.begin(); iter != list.end(); ++iter ) {
            if ( (*iter)->HasProperty(propertyName) ) {
                retval = (*iter);
                break;
            }
        }
    }

    return retval;
}

void Chamber::CalcForceNets() {

    // delete the current force nets
    std::list < ForceNet * >::iterator iterFNet;
	for ( iterFNet = forceNetList.begin(); iterFNet != forceNetList.end(); ) {
		delete (*iterFNet);
		iterFNet = forceNetList.erase(iterFNet);
	}

    // run through tile entities and add them to the force nets as appropriate
    ForceNet * farr[6] = { new ForceNet(), new ForceNet(), new ForceNet(), new ForceNet(), new ForceNet(), new ForceNet() };
    std::list < TileEntity * >::iterator iter;
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ++iter ) {
        if ( (*iter)->HasProperty("SygaldryA") ) {
            int sygA = (*iter)->Lookup( "SygaldryA" )->GetInt();
            char runeIndex = (sygA & 0x00FF);
            char runeColor = (sygA >> 8 ) & 0x00FF;
            if ( runeIndex == 1 ) { // if a force rune
                farr[runeColor]->AddTileEntity( *iter ); // add this tile entity to the given force net
            }
        }
    }

    // save the force nets that contain entities
    for ( int i = 0; i < 6; i ++ ) {
        if ( farr[i]->GetSize() > 0 ) {
            forceNetList.push_back( farr[i] );
        }
    }
}

ForceNet * Chamber::GetForceNetContaining( int uid ) {

    ForceNet * retval = 0;

    std::list < ForceNet * >::iterator iter;
	for ( iter = forceNetList.begin(); iter != forceNetList.end(); ++iter) {
		if ( (*iter)->Contains( uid ) ) {
            retval = (*iter);
            break;
        }
	}

    return retval;
}

void Chamber::OnEntityExitedTile( TileEntity * actor, int tileLoc ) {
    std::list< TileEntity * >::iterator iter;
    for ( iter = tileEntityTileListArr[tileLoc].begin(); iter != tileEntityTileListArr[tileLoc].end(); ++iter ) {
        (*iter)->OnExited( actor );
    }
}

void Chamber::OnEntityEnteredTile( TileEntity * actor, int tileLoc ) {
    std::list< TileEntity * >::iterator iter;
    for ( iter = tileEntityTileListArr[tileLoc].begin(); iter != tileEntityTileListArr[tileLoc].end(); ++iter ) {
        (*iter)->OnEntered( actor );
    }
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
    std::list < Entity * >::iterator iterA;
    for ( iterA = entityList.begin(); iterA != entityList.end(); ++iterA ) {
        entitiesJSON.add( (*iterA)->GetJSON() );
    }
    obj["entities"] = entitiesJSON;

    // Add list of tile entities
    json tileEntitiesJSON( json::an_array );
    std::list < TileEntity * >::iterator iterB;
    for ( iterB = tileEntityList.begin(); iterB != tileEntityList.end(); ++iterB ) {
        tileEntitiesJSON.add( (*iterB)->GetJSON() );
    }
    obj["tileEntities"] = tileEntitiesJSON;

    return obj;
    
}