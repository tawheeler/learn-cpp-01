/*
========================================================================

	A BaseScreen which runs the standard game mode

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "BaseScreen.h"
#include "ChamberManager.h"

namespace MysticDave {
    class MainScreen : public BaseScreen {

    public:

	    virtual void						    Init();
	    virtual void							Cleanup();
	    virtual void							Update();
	    virtual void							Render() const;

    private:

        bool * keysPressed;
        bool * keysToggled;

	    enum KEYS{ UP        = ALLEGRO_KEY_UP, 
                   DOWN      = ALLEGRO_KEY_DOWN, 
                   LEFT      = ALLEGRO_KEY_LEFT,
                   RIGHT     = ALLEGRO_KEY_RIGHT,
                   INTERACT  = ALLEGRO_KEY_E,
                   INVENTORY = ALLEGRO_KEY_I,
                   SPACE     = ALLEGRO_KEY_SPACE };

        ChamberManager * CM; // pointer to out chamber manager

    };
}