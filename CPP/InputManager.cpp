/*
========================================================================

	Handles all player input

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "InputManager.h"
#include "LogManager.h"
#include <assert.h>

using namespace MysticDave;

void InputManager::StartUp() {
	ZeroKeys();
}

void InputManager::ShutDown() {
	// nothing to free
}

InputManager& InputManager::GetInstance() {
	static InputManager* lmSingleton = NULL;
	if ( lmSingleton == NULL ) {
		lmSingleton = new InputManager();
	}
	assert( lmSingleton );
	return *lmSingleton;
}

void InputManager::ZeroKeys() {
    for ( int i = 0; i < ALLEGRO_KEY_MAX; i ++ ) {
        keys_pressed[i] = false;
        keys_toggled[i] = false;
    }
}

void InputManager::ZeroToggled() {
    for ( int i = 0; i < ALLEGRO_KEY_MAX; i ++ ) {
        keys_toggled[i] = false;
    }
}

void InputManager::HandleEvent( ALLEGRO_EVENT evt ) {
	if( evt.type == ALLEGRO_EVENT_KEY_DOWN ){
        keys_pressed[evt.keyboard.keycode] = true;
        keys_toggled[evt.keyboard.keycode] = true;
	} else if( evt.type == ALLEGRO_EVENT_KEY_UP ){
		keys_pressed[evt.keyboard.keycode] = false;
        keys_toggled[evt.keyboard.keycode] = true;
	}
}