/*
========================================================================

	A state machine for handling the screens
	Holds a stack of BaseScreen objects and controls their updating
	and rendering

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include <allegro5/allegro5.h>
#include <deque>
#include "BaseScreen.h"

namespace MysticDave {

    class BaseScreen;

    class ScreenManager {
    public:
										    ScreenManager();
										    ~ScreenManager();
	    void								StartUp();
	    void								ShutDown();
	    static ScreenManager&				GetInstance();

	    void								HandleEvent( ALLEGRO_EVENT evt );
	    void								Update();
	    void								Render();

	    void								PushGameScreen( BaseScreen * gs );

    private:
	    std::deque < BaseScreen * > states;
	    std::deque < BaseScreen * > statesToAdd;
	    std::deque < BaseScreen * >::iterator iter;
    };
}