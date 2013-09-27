/*
========================================================================

	A texture sheet of same-sized textures

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

namespace MysticDave {
    class TextureSheet {

    public:

											    TextureSheet( const char * name, int width, int height );
											    ~TextureSheet();

	    ALLEGRO_BITMAP *						GetTexture( int id );
	    void									RenderTexture( int id, float x, float y );         // renders texture by its top-left point
	    void									RenderTextureByCenter( int id, float x, float y ); // renders texture by its center point

    private:
	    ALLEGRO_BITMAP *						textureImage;
	    int										textureWidth;  // number of pixels each texture is wide
	    int										textureHeight; // number of pixels each texture is tall
	    int										numWidth;      // number of textures across image
	    int										numHeight;     // number of textures down image

    };
}