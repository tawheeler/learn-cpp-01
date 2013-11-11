/*
========================================================================

	A screen for displaying the player's inventory

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include <allegro5/allegro5.h>
#include "BaseScreen.h"
#include "BitmapVisual.h"
#include "TextureSheet.h"
#include "Pos2D.h"
#include "PlayerEntity.h"

namespace MysticDave {
    class InventoryScreen : public BaseScreen {
    public:

        static const int INPUT_DELAY = 10;

	    bool * keysPressed;
        bool * keysToggled;

	    enum KEYS{ UP       = ALLEGRO_KEY_UP, 
                   DOWN     = ALLEGRO_KEY_DOWN, 
                   LEFT     = ALLEGRO_KEY_LEFT,
                   RIGHT    = ALLEGRO_KEY_RIGHT,
                   ENTER    = ALLEGRO_KEY_ENTER,
                   INVENTORY = ALLEGRO_KEY_I };

                                                InventoryScreen();

	    virtual void							Init();
	    virtual void							Cleanup();
	    virtual void							Update();
	    virtual void							Render() const;

    private:
        PlayerEntity *                          player;
        TextureSheet *                          itemTexSheet;
        Pos2D *                                 cursorPos;

        int inputDelayCounter;
    };
}