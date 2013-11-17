/*
========================================================================

	A tile entity that is by default on fire. One can interact with it to
    put an inventory item in the flames. It can only be added to a net
    by putting an inventory item with sygaldry into the camp fire.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "TileEntity.h"

namespace MysticDave {
    class CampFire : public TileEntity {
    public:

                                    CampFire( std::string name, int uid );
                                    CampFire( jsoncons::json jobj );
		virtual                     ~CampFire();

        void                        InitCampFire();

    };
}