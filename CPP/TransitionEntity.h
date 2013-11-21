/*
========================================================================

	A tile entity that triggers on Dave entering and causes the chamber
    to transition, and then transition to a new chamber. There are 
    several types of transitions:

    TRANSITION_BLACKOUT  - black, change, re-light (param = targetTileLoc)
    TRANSITION_SCROLL    - scrolls the chamber over (param = direction to scroll)
    TRANSITION_SPIN_TILE - fade using a spinning animation sort of like Cave Story (param = targetTileLoc)

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "TileEntity.h"

namespace MysticDave {
    class TransitionEntity : public TileEntity {
    public:

        enum Transition { TRANSITION_BLACKOUT = 1, TRANSITION_SCROLL = 2, TRANSITION_SPIN_TILE = 3 };

                                    TransitionEntity( int transitionType, int targetChamberUID, int param );
                                    TransitionEntity( jsoncons::json jobj );
		virtual                     ~TransitionEntity();

        virtual void                OnEntered( TileEntity * actor );

    private:
        int                         transitionType;
        int                         targetChamberUID;
        int                         transitionDuration; // [ticks]
        int                         param;
        

        void                        InitTransitionEntity();
    };
}