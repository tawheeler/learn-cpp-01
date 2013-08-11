/*
========================================================================

	A visual which always shows a static bitmap image

========================================================================
*/
package Visuals;

import MysticDave.Vec2i;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;

public class BitmapVisual extends Visual {
    
    protected Vec2i pos;
    protected Image bitmap;
    protected int halfWidth;
    protected int halfHeight;
    
    public BitmapVisual( Vec2i pos, Image bitmap ) {
        this.pos = pos;
        this.bitmap = bitmap;
        halfWidth = bitmap.getWidth()/2;
        halfHeight = bitmap.getHeight()/2;
    }
    
    @Override
    public void Render( Graphics g ) {
        g.drawImage( bitmap, pos.x - halfWidth, pos.y-halfHeight );
    }
    
}
