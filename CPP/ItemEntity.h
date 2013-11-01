/*
========================================================================

	An inventory item manifest as a tile entity. One can pick it up by 
    walking over it. Sort of floats over the floor in an up & down 
    motion. Casting it into the fire will destroy it.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "TileEntity.h"

namespace MysticDave {
    class ItemEntity : public TileEntity {
    public:

                                    ItemEntity( std::string name, int uid );
                                    ItemEntity( jsoncons::json jobj );
		virtual                     ~ItemEntity();

        virtual void                Update();

        virtual void                OnEntered( TileEntity * actor );

        void                        InitItemEntity();

    private:
        int itemID;
        int moveType;
        
        int period; // how long it takes (in ticks) to undergo one oscillation
        int amplitude; // oscillation amplitude
        int counter; // counter for oscillation
    };
}