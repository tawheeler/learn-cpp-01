/*
========================================================================

	A base class for all game "screens"
	Each screen is considered to be a layer which can update and be
	rendered. Screens are arranged on a stack, and may block those
	below them from being updated and/or rendered

========================================================================
*/
package Screens;

import org.newdawn.slick.Graphics;
import org.newdawn.slick.Input;

/**
 *
 * @author Tim
 */
public abstract class BaseScreen {
    
    protected boolean blocksRender; //whether it blocks screens below it from rendering
    protected boolean blocksUpdate; //whether it blocks screens below it from updating
    protected boolean isDead;       //whether to destroy or not
    
    public abstract void Init();
    public abstract void Cleanup();
    
    public void SetBlockUpdate( boolean val ) {
        blocksUpdate = val;
    }
    
    public void SetBlockRender( boolean val ) {
        blocksRender = val;
    }
    
    public boolean BlocksUpdate() {
        return blocksUpdate;
    }
    
    public boolean BlocksRender() {
        return blocksRender;
    }
    
    public boolean IsDead() {
        return isDead;
    }
    
    public void SetDead() {
        isDead = true;
    }
    
    public abstract void Update(Input I);
    public abstract void Render(Graphics g);
}
