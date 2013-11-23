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

using jsoncons::json;
using namespace MysticDave;

void ResourceManager::StartUp() {
	LoadSamples( json::parse_file("./res/audio/audioSet.json") );
}

void ResourceManager::ShutDown() {

    // free texture sheets
    for ( auto iterTex = texSheetMap.begin(); iterTex != texSheetMap.end(); ) {
        delete iterTex->second;
        iterTex = texSheetMap.erase( iterTex );
    }

	// free bitmaps
    for ( auto iterBitmap = bitmapMap.begin(); iterBitmap != bitmapMap.end(); ) {
        al_destroy_bitmap( iterBitmap->second );
        iterBitmap = bitmapMap.erase( iterBitmap );
    }

    // free audio samples
    for ( auto iterAudio = audioMap.begin(); iterAudio != audioMap.end(); ) {
        al_destroy_sample( iterAudio->second );
        iterAudio = audioMap.erase( iterAudio );
    }
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
        if ( retval == 0 ) {
            LogManager::GetInstance().Write( LogManager::LOG_APP, " [FAILED!]\n" );
        } else {
		    bitmapMap[ str ] = retval;
            LogManager::GetInstance().Write( LogManager::LOG_APP, " [DONE]\n" );
        }
	}
	return retval;
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
		texSheetMap[ str ] = retval;
	}
	return retval;
}

void ResourceManager::PlaySample( const std::string sampleName ) {
    PlaySample( sampleName, 1.0f, 0.0f, 1.0f );
}

void ResourceManager::PlaySample( const std::string sampleName, float gain, float pan, float speed ) {
    std::map< std::string, ALLEGRO_SAMPLE *>::iterator iterAudio = audioMap.find(sampleName);
    if ( iterAudio != audioMap.end() ) {
        al_play_sample( iterAudio->second,  gain, pan, speed, ALLEGRO_PLAYMODE_ONCE, 0 ); 
    } else {
        (LogManager::GetInstance()).Write( LogManager::LOG_APP, "Failed to find sample %s\n", sampleName );
    }
}

void ResourceManager::LoadSamples( jsoncons::json jobj ) {

    for (auto it_obj = jobj.begin_members(); it_obj != jobj.end_members(); ++it_obj ) {
        ALLEGRO_SAMPLE * sample = al_load_sample( it_obj->second.as_string().c_str() );
        std::string audioName = it_obj->first;

        if ( sample != 0 ) {
            audioMap[ audioName ] = sample; // insert into map
        } else {
            (LogManager::GetInstance()).Write( LogManager::LOG_APP, "Failed to load sample %s\n", it_obj->first );
        }
    }

}