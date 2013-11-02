/*
========================================================================

	An inventory item manifest as a tile entity. One can pick it up by 
    walking over it. Sort of floats over the floor in an up & down 
    motion. Casting it into the fire will destroy it.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "ItemEntity.h"
#include "ResourceManager.h"
#include "TileBitmapVisual.h"
#include "PlayerEntity.h"
#include "Utils.h"
#include <math.h>

using jsoncons::json;
using namespace MysticDave;

ItemEntity::ItemEntity( std::string name, int uid ) : TileEntity( name, uid ) {
    InitItemEntity();

    visual = new BitmapVisual( pos, (ResourceManager::GetInstance()).LoadTextureSheet( "./res/items-6.png", TILE_DIM, TILE_DIM )->GetTexture(itemID));
}

ItemEntity::ItemEntity( jsoncons::json jobj ) : TileEntity( jobj ) {
    InitItemEntity();

    json jPropertiesArr = jobj["properties"];
    itemID = jPropertiesArr["ItemID"].as_int();

    visual = new TileBitmapVisual( pos, (ResourceManager::GetInstance()).LoadTextureSheet( "./res/items-6.png", TILE_DIM, TILE_DIM )->GetTexture(itemID));
}

ItemEntity::~ItemEntity() {
    // do nothing
}

void ItemEntity::InitItemEntity() {
    type = "ItemEntity";

    moveType = 0;
    itemID = 0;

    Register( "MoveType", &moveType, false );
    Register( "ItemID", &itemID, true );

    renderZ = 3;
    blocksOccupation = false;
    flammable = false;

    counter = 0;
    amplitude = 6;
    period = 140;
}

void ItemEntity::Update() {

    counter ++;
    if ( counter >= period ) {
        counter = 0;
    }
    
    int newDY = (int)(amplitude * sin( 2.0f*3.14159265f*counter / period)*sin( 2.0f*3.14159265f*counter / period) - amplitude - 4);
    pos->SetPixDY( newDY );

}

void ItemEntity::OnEntered( TileEntity * actor ) {
    // activate item pickup
    if ( actor->GetType().compare( "PlayerEntity" ) == 0 ) {
        // upcast to player entity
        PlayerEntity *player = dynamic_cast<PlayerEntity *>(actor);
        // add item to player inventory
        player->AddInventoryItem( itemID );

        // kill item entity
        ItemEntity::OnInput( "Kill" );
    }
}