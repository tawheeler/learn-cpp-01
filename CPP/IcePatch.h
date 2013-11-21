/*
========================================================================

	A tile entity representing a patch of ice on the floor.
    Things travelling on an ice patch slide.

    If melted becomes a water puddle.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "TileEntity.h"

namespace MysticDave {
    class IcePatch : public TileEntity {
    public:

                                    IcePatch();
                                    IcePatch( jsoncons::json jobj );
		virtual                     ~IcePatch();

        void                        InitIcePatch();

        virtual void                OnInput( const std::string I );
    };
}