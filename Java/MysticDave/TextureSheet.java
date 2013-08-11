/*
========================================================================

	A texture sheet of same-sized textures

========================================================================
*/
package MysticDave;

import Managers.ResourceManager;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;


public class TextureSheet {
    
    private Image textureImage;
    private int textureWidth;  // number of pixels each texture is wide
    private int textureHeight; // number of pixels each texture is tall
    private int numWidth;      // number of textures across image
    private int numHeight;     // number of textures down image
    
    public TextureSheet( String name, int width, int height ) {
        this.textureWidth  = width;
	this.textureHeight = height;

	this.textureImage = (ResourceManager.GetInstance()).GetBitmap( name );
	int w = textureImage.getWidth();
	int h = textureImage.getHeight();

	this.numWidth  = w / this.textureWidth;
	this.numHeight = h / this.textureHeight;
    }
    
    public Image GetTexture( int id ) {
        int sx = id % numWidth;
	int sy = id / numWidth;

	return textureImage.getSubImage( sx*textureWidth, sy*textureWidth, textureWidth, textureHeight );
    }
    
    public void RenderTexture( Graphics g, int id, float x, float y ) {
        int sx = (id % numWidth) * textureWidth;
	int sy = (id / numWidth) * textureHeight;
        
        g.drawImage( textureImage, x, y, x + textureWidth, y + textureHeight, sx, sy, sx+textureWidth, sy+textureHeight );
    }
    
    public void RenderTextureByCenter( Graphics g, int id, float x, float y ) {
        int sx = (id % numWidth) * textureWidth;
	int sy = (id / numWidth) * textureHeight;

        g.drawImage( textureImage, x - textureWidth/2, y - textureHeight/2, x + textureWidth/2, y + textureHeight/2, sx, sy, sx+textureWidth, sy+textureHeight );
    }
    
}
