/*
========================================================================

	A visual the size of a tile, so is rendered in tilespace

========================================================================
*/
package Visuals;

import MysticDave.Chamber;
import MysticDave.Vec2i;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;

public class TileBitmapVisual extends BitmapVisual {
    
    public TileBitmapVisual( Vec2i pos, Image bitmap ) {
        super( pos, bitmap );
    }
    
    @Override
    public void Render( Graphics g ) {
        g.drawImage( bitmap, pos.x*Chamber.TILE_PIXEL_DIM, pos.y*Chamber.TILE_PIXEL_DIM );
    }
    
}
