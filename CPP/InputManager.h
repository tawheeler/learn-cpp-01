/*
========================================================================

	Handles all player input

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "allegro5/allegro.h"

namespace MysticDave {
    class InputManager {
    public:

	    void												StartUp();
	    void												ShutDown();
	    static InputManager&								GetInstance();	

	    void                                                ZeroKeys();
        void                                                ZeroToggled();
        void							                    HandleEvent( ALLEGRO_EVENT evt );

        bool *                                              GetKeysPressed() { return keys_pressed; }
        bool *                                              GetKeysToggled() { return keys_toggled; }

    private:
														    InputManager() {};
														    InputManager( InputManager const& );  //do not implement
	    void operator = ( InputManager const& ); // don't implement

        bool keys_pressed[ALLEGRO_KEY_MAX];
        bool keys_toggled[ALLEGRO_KEY_MAX];
	
    };
}