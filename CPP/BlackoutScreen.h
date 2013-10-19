/*
========================================================================

	A transition screen which pushes everything to black and swaps the
    underlying chambers

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include <allegro5/allegro5.h>
#include "BaseScreen.h"
#include "TileEntity.h"
#include "Chamber.h"

namespace MysticDave {
    class BlackoutScreen : public BaseScreen {
    public:

                                                BlackoutScreen( int targetChamberUID, int blackoutDuration, int targetTile );

	    virtual void	       					Init();
	    virtual void							Cleanup();
	    virtual void							Update();
	    virtual void							Render() const;

    private:
        int blackoutCounter;
        int targetChamberUID;
        int targetTile;
    };
}