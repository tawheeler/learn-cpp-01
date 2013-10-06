/*
========================================================================

	Handles all loaded game resources, including images, sounds etc.

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "ResourceManager.h"
#include "LogManager.h"
#include <assert.h>

using namespace MysticDave;

void ResourceManager::StartUp() {
	// do nothing
}

void ResourceManager::ShutDown() {
	
	// free texture sheets first
	std::deque < TextureSheet * >::iterator iterTex;
	for ( iterTex = texSheetList.begin(); iterTex != texSheetList.end(); ) {
		delete (*iterTex);
		iterTex = texSheetList.erase(iterTex);
	}
	texSheetList.clear();

	// free bitmaps second
	std::deque < ALLEGRO_BITMAP * >::iterator iter;
	for ( iter = bitmapList.begin(); iter != bitmapList.end(); ) {
		al_destroy_bitmap( *iter );
		iter = bitmapList.erase(iter);
	}
	bitmapList.clear();
}

ResourceManager& ResourceManager::GetInstance() {
	static ResourceManager* lmSingleton = NULL;
	if ( lmSingleton == NULL ) {
		lmSingleton = new ResourceManager();
	}
	assert( lmSingleton );
	return *lmSingleton;
}

ALLEGRO_BITMAP * ResourceManager::GetBitmap( const char * name ) {
	std::string str = (name);
	std::map < std::string, ALLEGRO_BITMAP * >::iterator mapIter = bitmapMap.find(str);
	ALLEGRO_BITMAP * retval;
	if ( mapIter != bitmapMap.end() ) {
	   //element found;
	   retval = mapIter->second;
	} else { // not found load it
        LogManager::GetInstance().Write( LogManager::LOG_APP, "Loading Bitmap %s...", name );
		retval = al_load_bitmap( name );
		bitmapList.push_back( retval );
		bitmapMap[ str ] = retval;
        LogManager::GetInstance().Write( LogManager::LOG_APP, " [DONE]\n" );
	}
	return retval;
}

 // returns it if it has already been loaded
TextureSheet * ResourceManager::GetTextureSheet ( const char * name ) {
	std::string str = (name);
	std::map < std::string, TextureSheet * >::iterator iter = texSheetMap.find(str);
	if ( iter != texSheetMap.end() ) {
		//element found
		return iter->second;
	} else {
		return 0; //element not found
	}
}

 // returns it if it has already been loaded
TextureSheet * ResourceManager::LoadTextureSheet ( const char * name, int texWidth, int texHeight ) {
	std::string str = (name);
	std::map < std::string, TextureSheet * >::iterator iter = texSheetMap.find(str);
	TextureSheet * retval;
	if ( iter != texSheetMap.end() ) {
		//element found
		retval = iter->second;
	} else {
		//create and return
		retval = new TextureSheet( name, texWidth, texHeight );
		texSheetList.push_back( retval );
		texSheetMap[ str ] = retval;
	}
	return retval;
}