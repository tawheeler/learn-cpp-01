/*
========================================================================

	Handles all loaded game resources, including images, sounds etc.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "allegro5/allegro.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "TextureSheet.h"
#include "jsoncons/json.hpp"
#include <string>
#include <deque>
#include <map>

namespace MysticDave {
    class ResourceManager {
    public:
	
	    void												StartUp();
	    void												ShutDown();
	    static ResourceManager&								GetInstance();	

	    ALLEGRO_BITMAP *									GetBitmap( const char * name ); // loads it if it needs to, otherwise returns it
	    TextureSheet *										LoadTextureSheet ( const char * name, int texWidth, int texHeight ); // returns if it has already been loaded, otherwise creates it

        void	    										PlaySample( const std::string sampleName );
        void                                                PlaySample( const std::string sampleName, float gain, float pan, float speed );

        void                                                LoadSamples( jsoncons::json jobj ); // load samples given by the json file

    private:
														    ResourceManager() {};
														    ResourceManager( ResourceManager const& );  //do not implement
	    void operator = ( ResourceManager const& ); // don't implement

	    std::map < std::string, ALLEGRO_BITMAP * >			bitmapMap;
	    std::map < std::string, TextureSheet * >			texSheetMap;
        std::map < std::string, ALLEGRO_SAMPLE * >          audioMap;
	
    };
}