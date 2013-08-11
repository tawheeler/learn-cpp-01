/*
========================================================================

	The main function, which initializes Allegro and runs the game loop

========================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "Globals.h"
#include "LogManager.h"
#include "ScreenManager.h" 
#include "ResourceManager.h"
//#include "GameObjectManager.h"


#include "BaseScreen.h"
#include "MainScreen.h"


LogManager *				myLogManager;
ScreenManager *				myScreenManager;
//GameObjectManager *		myGameObjectManager;
ResourceManager *			myResourceManager;

bool						done;
ALLEGRO_EVENT_QUEUE *		event_queue;
ALLEGRO_TIMER *				timer;
ALLEGRO_DISPLAY *			display;

void AbortGame( const char* message ) {
	if ( myLogManager ) {
		myLogManager->Write( LogManager::LOG_APP, "%s\n", message );
	} else {
		printf( "%s \n", message );
	}
    exit( 1 );
}

void Init( void ) {

	myLogManager = &(LogManager::GetInstance());
	myLogManager->StartUp();

	// Allegro Init Functions
    if ( !al_init() ) {
		AbortGame( "Failed to initialize allegro" );
	}
	if( !al_init_primitives_addon() ) {
		AbortGame( "Failed to install primitives addon" );
	}
	if( !al_install_mouse() ) {
		AbortGame( "Failed to install mouse" );
	}
    if ( !al_install_keyboard() ) {
		AbortGame( "Failed to install keyboard" );
	}

	al_init_image_addon();  // image addon
	al_init_font_addon();   // font addon
	al_init_ttf_addon();    // true type font addon
	al_install_audio();     // audio addon
	al_init_acodec_addon(); // audio codec addon

	al_reserve_samples( 15 );

	myScreenManager = &(ScreenManager::GetInstance());
	myScreenManager->StartUp();
	myResourceManager = &(ResourceManager::GetInstance());
	myResourceManager->StartUp();
	/*myGameObjectManager = &(GameObjectManager::GetInstance());
	myGameObjectManager->StartUp();*/
	
    timer = al_create_timer( 1.0 / FPS ); //set fps
    if ( !timer ) {
        AbortGame( "Failed to create timer" );
	}
 
    al_set_new_display_flags( ALLEGRO_WINDOWED );

	// enable antialiasing
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

	// create the display
	display = al_create_display( SCREEN_WIDTH, SCREEN_HEIGHT );
    if ( !display ) {
        AbortGame( "Failed to create display" );
	}
 
    event_queue = al_create_event_queue();
    if ( !event_queue ) {
        AbortGame( "Failed to create event queue" );
	}

    al_register_event_source( event_queue, al_get_keyboard_event_source() );
    al_register_event_source( event_queue, al_get_timer_event_source( timer ));
    al_register_event_source( event_queue, al_get_display_event_source( display ));
    al_register_event_source( event_queue, al_get_mouse_event_source() );

	al_set_window_title( display, "Mystic Dave" );

	BaseScreen * screen = new MainScreen();
	screen->Init();
	myScreenManager->PushGameScreen( screen );

	// init random number generator
	srand( time(NULL) );

	myLogManager->Write( LogManager::LOG_APP, "Finished Main Initialization\n" );
    done = false;
}

void Shutdown(void) {

	// destroy shell objects
    if ( timer ) {
       al_destroy_timer( timer );
	}
    if ( display ) {
        al_destroy_display( display );
	}
    if ( event_queue ) {
        al_destroy_event_queue( event_queue );
	}

	//free all user-defined objects
	//myGameObjectManager->ShutDown();
	//delete myGameObjectManager;
	myResourceManager->ShutDown();
	delete myResourceManager;
	myScreenManager->ShutDown();
	delete myScreenManager;
	myLogManager->ShutDown();
	delete myLogManager;
	
}

void Render( void ) {
	myScreenManager->Render();
}

/*
================================================
UpdateLogic

	Updates the game logic by one tick
================================================
 */
void UpdateLogic( void ) {
	myScreenManager->Update();
}

void GameLoop( void ) {
   bool redraw = true;
   al_start_timer( timer );
 
   while ( !done ) {
       ALLEGRO_EVENT evt;
       al_wait_for_event( event_queue, &evt );
 
       if ( evt.type == ALLEGRO_EVENT_TIMER ) {
           redraw = true;
           UpdateLogic();
       } else {
			if ( evt.type == ALLEGRO_EVENT_KEY_DOWN ) {
				if ( evt.keyboard.keycode == ALLEGRO_KEY_ESCAPE ) {
					myLogManager->Write( LogManager::LOG_APP, "Shutting down due to escape key press\n" );
					done = true;
				}
			} else if ( evt.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {  //close button pressed
				done = true;
			}
			myScreenManager->HandleEvent( evt ); //pass it on
        }
 
	    //render
        if ( redraw && al_is_event_queue_empty( event_queue )) {
            redraw = false;
            al_clear_to_color( al_map_rgb( 0, 0, 0 ));
			Render();
            al_flip_display();
        }
    }
}

int main() {

    Init();
    GameLoop();
    Shutdown();

	return 0;
} 