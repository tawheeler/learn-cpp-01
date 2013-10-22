/*
========================================================================

	A transition screen which causes the map to scroll laterally over
    to the next chamber. Dave is moved to the corresponding edge-tile
    of the next chamber depending on direction

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include <allegro5/allegro5.h>
#include "BaseScreen.h"
#include "TileEntity.h"
#include "Chamber.h"
#include "PlayerEntity.h"

namespace MysticDave {
    class TransitionScrollScreen : public BaseScreen {
    public:

                                                TransitionScrollScreen( int targetChamberUID, int transitionDuration, int direction );

	    virtual void	       					Init();
	    virtual void							Cleanup();
	    virtual void							Update();
	    virtual void							Render() const;

    private:
        int transitionDuration;
        int transitionCounter; // 0 means it is over
        int direction;
        int targetTile;

        // chamber position change
        int dx;
        int dy;

        // player position change
        int dx_player;
        int dy_player;

        Chamber * sourceChamber;
        Chamber * destChamber;
        PlayerEntity * player;
    };
}