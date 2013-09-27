/*
========================================================================

	A texture sheet of same-sized textures

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "TextureSheet.h"
#include "ResourceManager.h"
#include "LogManager.h"

using namespace MysticDave;

TextureSheet::TextureSheet( const char * name, int width, int height ) {

	TextureSheet::textureWidth  = width;
	TextureSheet::textureHeight = height;

	TextureSheet::textureImage = (ResourceManager::GetInstance()).GetBitmap( name );
	int w = al_get_bitmap_width(textureImage);
	int h = al_get_bitmap_height(textureImage);

	TextureSheet::numWidth  = w / TextureSheet::textureWidth;
	TextureSheet::numHeight = h / TextureSheet::textureHeight;
}

TextureSheet::~TextureSheet() {
	// do nothing
}

ALLEGRO_BITMAP * TextureSheet::GetTexture( int id ) {
	int sx = id % numWidth;
	int sy = id / numWidth;

	return al_create_sub_bitmap( textureImage, sx*textureWidth, sy*textureHeight, textureWidth, textureHeight );
}

//renders via top-left corner of texture
void TextureSheet::RenderTexture( int id, float x, float y ) {
	int sx = id % numWidth;
	int sy = id / numWidth;

	al_draw_bitmap_region( textureImage, sx*textureWidth, sy*textureHeight, textureWidth, textureHeight, x, y, 0 );
}

void TextureSheet::RenderTextureByCenter( int id, float x, float y ) {

	int sx = id % numHeight;
	int sy = id / numHeight;

	al_draw_bitmap_region( textureImage, sx*textureWidth, sy*textureHeight, textureWidth, textureHeight, x - textureWidth/2, y - textureHeight/2, 0 );

}