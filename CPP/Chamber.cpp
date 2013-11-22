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
#include "Block.h"
#include "CompoundBlock.h"
#include "IcePatch.h"
#include "Trigger.h"
#include "TransitionEntity.h"
#include "ItemEntity.h"
#include "LogManager.h"
#include "MessageStruct.h"
#include "EntityEventManager.h"
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
        } else if ( (*it)["type"].as_string().compare( "Block" ) == 0 ) {
            te = new Block( *it );
        } else if ( (*it)["type"].as_string().compare( "CompoundBlock" ) == 0 ) {
            te = new CompoundBlock( *it );
        } else if ( (*it)["type"].as_string().compare( "Trigger" ) == 0 ) {
            te = new Trigger( *it );
        } else if ( (*it)["type"].as_string().compare( "TransitionEntity" ) == 0 ) {
            te = new TransitionEntity( *it );
        } else if ( (*it)["type"].as_string().compare( "ItemEntity" ) == 0 ) {
            te = new ItemEntity( *it );
        } else if ( (*it)["type"].as_string().compare( "IcePatch" ) == 0 ) {
            te = new IcePatch( *it );
        }

        if ( te != 0 ) {
            RegisterTileEntityInTile( te, te->GetPos()->GetTileX(), te->GetPos()->GetTileY() );
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
}

void Chamber::Cleanup() {
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
			(*iter)->Render( x, y );
	}
}

void Chamber::AddEntity( Entity * e) {
    e->SetUID( GetNextUID() ); // generate a UID for the entity
    entityList.push_back( e );
    entityUIDMap[ e->GetUID() ] = e;
}

void Chamber::AddTileEntity( TileEntity * te ) {

    // generate a UID for the entity
    te->SetUID( GetNextUID() );

    // insert in order by renderZ
    int index = 0;
    bool inserted = false;
    for ( auto iter = tileEntityList.begin(); iter != tileEntityList.end(); ++iter ) {
        if ( (*iter)->GetRenderZ() > te->GetRenderZ() ) {
            tileEntityList.insert( iter, te );
            inserted = true;
            break;
        }
        index ++;
    }

    if ( !inserted ) {
        tileEntityList.push_front( te );
    }

    // place in map
    entityUIDMap[ te->GetUID() ] = te;
}

void Chamber::RegisterTileEntityInTile( TileEntity * te, int tileX, int tileY ) {
    RegisterTileEntityInTile( te, GetTileNumFromPos(tileX, tileY) );
}

void Chamber::RegisterTileEntityInTile( TileEntity * te, int tileNum ) {

    // insert in order
    /*int index = 0;
    bool inserted = false;
    for ( auto iter = tileEntityTileListArr[tileNum].begin(); iter != tileEntityTileListArr[tileNum].end(); ++iter ) {
        if ( (*iter)->GetRenderZ() > te->GetRenderZ() ) {
            tileEntityTileListArr[tileNum].insert( iter, te );
            inserted = true;
            break;
        }
        index ++;
    }*/

    //if ( !inserted ) {
        tileEntityTileListArr[tileNum].push_front( te );
    //}
    
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

bool Chamber::HasEntityInMotion() {
    for ( auto it = tileEntityList.begin(); it != tileEntityList.end(); ++it ) {
        if ( (*it)->IsInMotion() ) {
            return true;
        }
    }
    return false;
}

Entity * Chamber::GetEntity( int uid ) {
    std::map< int, Entity *>::iterator pos = entityUIDMap.find(uid);
    //assert(pos != entityUIDMap.end());
    if ( pos == entityUIDMap.end() ) {
        return 0;
    }
    return pos->second;
}

Entity * Chamber::GetEntity( std::string name ) {
    Entity * retval = 0;

    std::map< int, Entity *>::iterator iter;
    for( iter = entityUIDMap.begin(); iter != entityUIDMap.end(); ++iter) {
        //std::string name = (iter->second)->GetName();
        if ( (iter->second)->GetName().compare( name ) == 0 ) {
            retval = iter->second;
            break;
        }
    }

    return retval;
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

TileEntity * Chamber::GetEntityOfTypeInTile( std::string type, int tileNum ) {
    TileEntity * retval = 0;

    if ( IsInChamber_Tile( tileNum ) ) {
        std::list < TileEntity * > list = tileEntityTileListArr[tileNum];
        std::list < TileEntity * >::iterator iter;
	    for ( iter = list.begin(); iter != list.end(); ++iter ) {
            if ( (*iter)->GetType().compare(type) == 0 ) {
                retval = (*iter);
                break;
            }
        }
    }

    return retval;
}

std::list < TileEntity * > * Chamber::GetEntitiesInTile( int tileNum ) {
    std::list < TileEntity * > * retval;

    if ( IsInChamber_Tile( tileNum ) ) {
        retval = &(tileEntityTileListArr[tileNum]);
    }

    return retval;
}

std::list < int > Chamber::GetTilesContainingTileEntity( int tileEntityID ) {
    
    std::list < int > retval;
    
    for ( int a = 0; a < numTiles; a ++ ) {
        for ( auto it = tileEntityTileListArr[a].begin(); it != tileEntityTileListArr[a].end(); ++it ) {
            if ( (*it)->GetUID() == tileEntityID ) {
                retval.push_back( a );
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
    ForceNet * farr[12] = { new ForceNet(), new ForceNet(), new ForceNet(), new ForceNet(), new ForceNet(), new ForceNet(),
                            new ForceNet(), new ForceNet(), new ForceNet(), new ForceNet(), new ForceNet(), new ForceNet()};
    std::list < TileEntity * >::iterator iter;
	for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ++iter ) {
        if ( (*iter)->HasProperty("Sygaldry") ) {
            int sygA = (*iter)->Lookup( "Sygaldry" )->GetInt();
            char runeIndex = (sygA & 0x00FF);
            char runeColor = (sygA >> 8 ) & 0x00FF;
            if ( runeIndex == 1 ) { // if a force rune
                farr[runeColor]->AddTileEntity( *iter ); // add this tile entity to the given force net
            }
        }
        if ( (*iter)->HasProperty("InherentSygaldry") ) {
            int sygA = (*iter)->Lookup( "InherentSygaldry" )->GetInt();
            char runeIndex = (sygA & 0x00FF);
            char runeColor = (sygA >> 8 ) & 0x00FF;
            if ( runeIndex == 1 ) { // if a force rune
                farr[runeColor]->AddTileEntity( *iter ); // add this tile entity to the given force net
            }
        }
    }

    // check whether any force nets intersect
    // if they do, move all entities from the second into the first
    for ( int i = 0; i < 12; i ++ ) {
        for ( int j = i + 1; j < 12; j ++ ) {

            bool intersects = false;
            for ( int k = 0; k < farr[j]->GetSize(); k ++ ) {
                if ( farr[i]->Contains( farr[j]->GetTileEntityAtIndex(k)->GetUID() ) ) {
                    intersects = true;
                    break;
                }
            }

            if ( intersects ) {
                // move all entities from the second into the first
                for ( int k = 0; k < farr[j]->GetSize(); k ++ ) {
                    farr[i]->AddTileEntity( farr[j]->GetTileEntityAtIndex( k ) );
                }

                // clear out the force net
                delete farr[j];
                farr[j] = new ForceNet();
            }
        }
    }

    // save the force nets that contain entities
    for ( int i = 0; i < 12; i ++ ) {
        if ( farr[i]->GetSize() > 0 ) {
            forceNetList.push_back( farr[i] );
        }
    }
}

void Chamber::CalcConductionNets( TileEntity * te ) {

    // this function calculates the conduction net corresponding to a specific tile entity
    // 1 - add the TE to the conduction net
    // while ( we have new things we just added )
    //    2 - For every new TE, find which tile(s) it is in and add all other TEs into the conduction net
    //    3 - For nevey new TE, add any TEs which share conduction sygaldry with it
    

    std::list < TileEntity * > condNet;
    std::set  < int > condSet; // keyed by uid
    std::list < TileEntity * > newAdditions;
    std::list < TileEntity * > additions;

    // (1) add the given TE
    condNet.push_back( te );
    condSet.insert( te->GetUID() );
    newAdditions.push_back( te );

    while ( !(newAdditions.empty()) ) {
        
        additions.clear(); // empty it out
        additions.insert( additions.begin(), newAdditions.begin(), newAdditions.end() ); // copy the new additions
        newAdditions.clear(); // empty it out

        for ( auto it = additions.begin(); it != additions.end(); ++it ) {

            std::string name = (*it)->GetName();

            // (2) add tile entities that were in the same tile
            std::list < int > tileIDs = GetTilesContainingTileEntity( (*it)->GetUID() ); // list of tile ids that this TE is in
            for ( auto it2 = tileIDs.begin(); it2 != tileIDs.end(); ++it2 ) {
                std::list < TileEntity * > * entitiesInTile = GetEntitiesInTile( *it2 );
                for ( auto it3 = entitiesInTile->begin(); it3 != entitiesInTile->end(); ++it3 ) {
                    if ( condSet.find( (*it3)->GetUID() ) == condSet.end() ) { // not yet in set
                        // insert!
                        condNet.push_back( *it3 );
                        condSet.insert( (*it3)->GetUID() );
                        newAdditions.push_back( *it3 );
                    }
                }
            }

            // (3) add all TEs that share sygaldry with it
            if ( (*it)->HasProperty("Sygaldry") ) {
                int sygA = (*it)->Lookup( "Sygaldry" )->GetInt();
                char runeIndex = (sygA & 0x00FF);
                char runeColor = (sygA >> 8 ) & 0x00FF;
                if ( runeIndex == 2 ) { // if a conduction rune
                    // go through all entities and find those which also have this rune

                    for ( auto it2 = tileEntityList.begin(); it2 != tileEntityList.end(); ++it2 ) {
                        if ( (*it2)->HasProperty( "Sygaldry" ) && ((*it2)->Lookup("Sygaldry")->GetInt() == sygA)
                            && condSet.find( (*it2)->GetUID() ) == condSet.end() ) {
                            // insert!
                            condNet.push_back( *it2 );
                            condSet.insert( (*it2)->GetUID() );
                            newAdditions.push_back( *it2 );
                        }
                        if ( (*it2)->HasProperty( "InherentSygaldry" ) && ((*it2)->Lookup("InherentSygaldry")->GetInt() == sygA)
                            && condSet.find( (*it2)->GetUID() ) == condSet.end() ) {
                            // insert!
                            condNet.push_back( *it2 );
                            condSet.insert( (*it2)->GetUID() );
                            newAdditions.push_back( *it2 );
                        }
                    }

                }
            }
            if ( (*it)->HasProperty("InherentSygaldry") ) {
                int sygA = (*it)->Lookup( "InherentSygaldry" )->GetInt();
                char runeIndex = (sygA & 0x00FF);
                char runeColor = (sygA >> 8 ) & 0x00FF;
                if ( runeIndex == 2 ) { // if a conduction rune
                    // go through all entities and find those which also have this rune

                    for ( auto it2 = tileEntityList.begin(); it2 != tileEntityList.end(); ++it2 ) {
                        if ( (*it2)->HasProperty( "Sygaldry" ) && ((*it2)->Lookup("Sygaldry")->GetInt() == sygA)
                            && condSet.find( (*it2)->GetUID() ) == condSet.end() ) {
                            // insert!
                            condNet.push_back( *it2 );
                            condSet.insert( (*it2)->GetUID() );
                            newAdditions.push_back( *it2 );
                        }
                        if ( (*it2)->HasProperty( "InherentSygaldry" ) && ((*it2)->Lookup("InherentSygaldry")->GetInt() == sygA)
                            && condSet.find( (*it2)->GetUID() ) == condSet.end() ) {
                            // insert!
                            condNet.push_back( *it2 );
                            condSet.insert( (*it2)->GetUID() );
                            newAdditions.push_back( *it2 );
                        }
                    }

                }
            }
        }
    }

    // now compute the action to take
    // 1 - sort entities into "hot", "cold", and "neutral"
    // 2 - if there are more hot than cold, apply "OnHeated" to cold and neutral
    // 3 - if there are more cold than hold, apply "OnChilled" to hot and neutral
    // 4 - if there is an equal amount, apply "OnHeated" to hot, "OnChilled" to cold, and nothing to neutral

    // (1) count cold and hot
    int numHot = 0;
    int numCold = 0;
    for ( auto it = condNet.begin(); it != condNet.end(); ++it ) {
        switch( (*it)->GetTemperature() ) {
            case ( TileEntity::TEMPERATURE::HOT ): numHot++; break;
            case ( TileEntity::TEMPERATURE::COLD ): numCold++; break;
        }
    }

    (LogManager::GetInstance()).Write( LogManager::LOG_APP, "Conduction Net: %d, %d\n", numHot, numCold );
    for ( auto it = condNet.begin(); it != condNet.end(); ++it ) {
        (LogManager::GetInstance()).Write( LogManager::LOG_APP, "\t%s\n", (*it)->GetType().c_str() );
    }

    for ( auto it = condNet.begin(); it != condNet.end(); ++it ) {
        if ( numHot > numCold ) {
            if ( (*it)->GetTemperature() != TileEntity::TEMPERATURE::HOT ) {

                MessageStruct * ms = new MessageStruct();
                ms->inputName = "OnHeated";
                ms->targetEntityID = (*it)->GetUID();
                ms->timeDelay = 0;

                (EntityEventManager::GetInstance()).AddEvent( ms );
            }

        } else if ( numCold > numHot ) {
            if ( (*it)->GetTemperature() != TileEntity::TEMPERATURE::COLD ) {

                MessageStruct * ms = new MessageStruct();
                ms->inputName = "OnChilled";
                ms->targetEntityID = (*it)->GetUID();
                ms->timeDelay = 0;

                (EntityEventManager::GetInstance()).AddEvent( ms );
            }

        } else {

            if ( (*it)->GetTemperature() == TileEntity::TEMPERATURE::HOT ) {

                MessageStruct * ms = new MessageStruct();
                ms->inputName = "OnChilled";
                ms->targetEntityID = (*it)->GetUID();
                ms->timeDelay = 0;

                (EntityEventManager::GetInstance()).AddEvent( ms );
            }

            if ( (*it)->GetTemperature() == TileEntity::TEMPERATURE::COLD ) {

                MessageStruct * ms = new MessageStruct();
                ms->inputName = "OnHeated";
                ms->targetEntityID = (*it)->GetUID();
                ms->timeDelay = 0;

                (EntityEventManager::GetInstance()).AddEvent( ms );
            }

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
    int i = tileEntityTileListArr[tileLoc].size();
    for ( iter = tileEntityTileListArr[tileLoc].begin(); iter != tileEntityTileListArr[tileLoc].end(); ++iter ) {
        if ( (*iter) != actor ) {
            (*iter)->OnEntered( actor );
        }
    }
}

int Chamber::GetNextUID() {
    // run through all of the entities and return the first UID not yet used
    int retval = 1;
    bool done = false;
    while ( !done ) {
        retval++;
        done = (entityUIDMap.find(retval) == entityUIDMap.end());
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