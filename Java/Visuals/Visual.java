/*
========================================================================

	An object which can be rendered on the screen

========================================================================
*/
package Visuals;

import org.newdawn.slick.Graphics;

public abstract class Visual {
    
    public Visual(){}
    
    public void Cleanup(){}
    public abstract void Render( Graphics g );
    
}
