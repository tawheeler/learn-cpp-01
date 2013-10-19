/*
========================================================================

	A BaseScreen for adding sygaldry to an object

    Player can add any of the binding runes and set their color net

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include <allegro5/allegro5.h>
#include "BaseScreen.h"
#include "TileEntity.h"
#include "BitmapVisual.h"
#include "TextureSheet.h"
#include "Vec2i.h"

namespace MysticDave {
    class SygaldryScreen : public BaseScreen {
    public:

	    bool * keysPressed;
        bool * keysToggled;

	    enum KEYS{ UP       = ALLEGRO_KEY_UP, 
                   DOWN     = ALLEGRO_KEY_DOWN, 
                   LEFT     = ALLEGRO_KEY_LEFT,
                   RIGHT    = ALLEGRO_KEY_RIGHT,
                   ENTER    = ALLEGRO_KEY_ENTER, };

                                                SygaldryScreen( TileEntity * te );

	    virtual void							Init();
	    virtual void							Cleanup();
	    virtual void							Update();
	    virtual void							Render() const;

    private:
        TileEntity *                            sygaldryEntity;

        TextureSheet *                          runeSetTextureSheet;

        BitmapVisual *                          sygaldryPanel;
        Vec2i *                                 panelPos;

        int                                     rune; // lsb is rune char (0x01 = force, 0x02 = conduction), msb is color (0x01 = k, 0x02 = b, etc.)
        int *                                   colorMap;
        int                                     inputDelayCounter;
    };
}