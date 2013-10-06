/*
========================================================================

	A single square in the grid of a chamber

	Tied to a static floor image
	Can contain TileEntities

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "Tile.h"
#include "TileEntity.h"

using namespace MysticDave;
using jsoncons::json;

Tile::Tile() {
	Tile::imageAddr  = 0;
	blocksOccupation = false;
}

Tile::Tile( int imageAddr ) {
	Tile::imageAddr  = imageAddr;
	blocksOccupation = false;
}

Tile::Tile( jsoncons::json jobj ) {
    Tile::imageAddr = jobj["imageAddr"].as_int();
    Tile::blocksOccupation = jobj["blocksOccupation"].as_bool();

    /* json jtileArr = jobj["tileArr"];
    int i = 0;
    for (auto it = jtileArr.begin_elements(); it != jtileArr.end_elements(); ++it)
    {
        tileArr[i] = Tile( *it ); // TODO: make sure this doesn't cause a memory leak
        ++i;
    } */

    // Extract list of tile entities
    /* json jtileEntitiesArr = jobj["tileEntities"];
    for ( auto it = jtileEntitiesArr.begin_elements(); it != jtileEntitiesArr.end_elements(); ++it ) {
        tileEntityList.push_back( new );
    } */
}

Tile::~Tile() {
	// do nothing (tile entities will be destroyed by someone else)
}

bool Tile::BlocksOccupation() {
    return blocksOccupation;
}

void Tile::SetBlocksOccupation( bool b ) {
    Tile::blocksOccupation = b;
}

int Tile::GetImageAddr() {
    return imageAddr;
}

void Tile::SetImageAddr( int i ) {
    Tile::imageAddr = i;
}

bool Tile::IsOccupied() {

	bool retval = blocksOccupation;

    // TODO: check list of tile entities

	return retval;
}

jsoncons::json Tile::GetJSON() {
    json obj( json::an_object );

    obj["imageAddr"]  = imageAddr;
    obj["blocksOccupation"] = blocksOccupation;

    // Add list of tile entities
    json tileEntitiesJSON( json::an_array );
    std::deque < TileEntity * >::iterator iter;
    for ( iter = tileEntityList.begin(); iter != tileEntityList.end(); ++iter ) {
        tileEntitiesJSON.add( (*iter)->GetJSON() );
    }
    obj["tileEntities"] = tileEntitiesJSON;

    return obj;
}