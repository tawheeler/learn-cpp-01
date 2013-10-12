/*
========================================================================

	A BaseScreen which runs the standard game mode

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include <allegro5/allegro5.h>
#include "BaseScreen.h"
#include "Chamber.h"
#include "PlayerEntity.h"
#include "ForceNet.h"

namespace MysticDave {
    class MainScreen : public BaseScreen {
    public:

        bool * keysPressed;
        bool * keysToggled;

	    enum KEYS{ UP       = ALLEGRO_KEY_UP, 
                   DOWN     = ALLEGRO_KEY_DOWN, 
                   LEFT     = ALLEGRO_KEY_LEFT,
                   RIGHT    = ALLEGRO_KEY_RIGHT,
                   INTERACT = ALLEGRO_KEY_E,
                   SPACE    = ALLEGRO_KEY_SPACE };

	    virtual void						    Init();
	    virtual void							Cleanup();
	    virtual void							Update();
	    virtual void							Render() const;

	    Chamber *								curChamber;
	    PlayerEntity *							player;

	    ForceNet *								fnet;
    };
}