/*
========================================================================

	A tile entity representing a water puddle on the floor.

    If melted evaporates.
    If chilled becomes an ice patch.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "TileEntity.h"

namespace MysticDave {
    class WaterPatch : public TileEntity {
    public:

                                    WaterPatch( std::string name, int uid );
                                    WaterPatch( jsoncons::json jobj );
		virtual                     ~WaterPatch();

        void                        InitWaterPatch();

        virtual void                OnInput( const std::string I );
    };
}