/*
========================================================================

	A tile entity that solely exists for causing some sort of output 
    when something enters or exits.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "TileEntity.h"

namespace MysticDave {
    class Trigger : public TileEntity {
    public:

                                    Trigger( std::string name, int uid );
                                    Trigger( jsoncons::json jobj );
		virtual                     ~Trigger();

        virtual void                OnInput( const std::string I );
        virtual void                OnEntered( TileEntity * actor );

    private:
        void                        InitTrigger();
        void                        OnTrigger();

        bool                        isEnabled;
        bool                        startDisabled; // If true, stay dormant until activated with Enable input
    };
}