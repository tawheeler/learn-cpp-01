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
#include "TextureSheet.h"
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

    private:
														    ResourceManager() {};
														    ResourceManager( ResourceManager const& );  //do not implement
	    void operator = ( ResourceManager const& ); // don't implement

	    std::deque < ALLEGRO_BITMAP * >						bitmapList;
	    std::deque < TextureSheet * >						texSheetList;

	    std::map < std::string, ALLEGRO_BITMAP * >			bitmapMap;
	    std::map < std::string, TextureSheet * >			texSheetMap;
	
    };
}