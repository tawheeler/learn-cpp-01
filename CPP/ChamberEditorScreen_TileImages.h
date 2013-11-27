/*
========================================================================

	A BaseScreen which allows the user to edit a given chamber
    
    Specifically edits the tile images in a given chamber

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/


#pragma once

#include "BaseScreen.h"
#include "ChamberManager.h"
#include "Chamber.h"

namespace MysticDave {
    class ChamberEditorScreen_TileImages : public BaseScreen {

    public:

	    virtual void						    Init();
	    virtual void							Cleanup();
	    virtual void							Update();
	    virtual void							Render() const;

    private:

        int cursorX;
        int cursorY;
        int actionCooldown;

        int brushIndex;

        Chamber *                               myChamber;
        TextureSheet *							texSheet;    // texture sheet for the tiles

        bool * keysPressed;
        bool * keysToggled;

	    enum KEYS{ UP        = ALLEGRO_KEY_UP, 
                   DOWN      = ALLEGRO_KEY_DOWN, 
                   LEFT      = ALLEGRO_KEY_LEFT,
                   RIGHT     = ALLEGRO_KEY_RIGHT,
                   KEY_W     = ALLEGRO_KEY_W, 
                   KEY_S     = ALLEGRO_KEY_S, 
                   KEY_A     = ALLEGRO_KEY_A,
                   KEY_D     = ALLEGRO_KEY_D,
                   SPACE     = ALLEGRO_KEY_SPACE,
                   ENTER     = ALLEGRO_KEY_ENTER,
                   SAVE      = ALLEGRO_KEY_F1,
                   COPY      = ALLEGRO_KEY_C};

    };
}