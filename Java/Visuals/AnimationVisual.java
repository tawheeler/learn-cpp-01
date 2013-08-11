/*
========================================================================

	A visual which shows animations

========================================================================
*/
package Visuals;

import MysticDave.Animation;
import MysticDave.Chamber;
import MysticDave.Vec2i;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;

public class AnimationVisual extends Visual {
    
    private Vec2i pos;
    private Image bitmap;
    private int   halfWidth;
    private int   halfHeight;
    
    private Animation animation;
    private int       frameTick;
    private int       frameIndex;
    
    public AnimationVisual( Vec2i pos, Image bitmap ) {
        this.pos = pos;
        this.bitmap = bitmap;
        this.halfWidth = bitmap.getWidth()/2;
        this.halfHeight = bitmap.getHeight()/2;
        
        this.animation = null;
        this.frameIndex = 0;
        this.frameTick = 0;
    }
    
    @Override
    public void Render( Graphics g ) {
        boolean renderAnim = false;
	       if (animation != null) {
            frameTick--;
            if (frameTick <= 0) { // move to a new frame, if possible
                frameIndex++; // move to next frame
                if (frameIndex >= animation.numFrames) { // ran out of frames
                    animation = null; // done with animations
                } else {
                    frameTick = animation.frameDurations[frameIndex];
                    renderAnim = true;
                }
            } else {
                renderAnim = true;
            }
        }

        if (renderAnim) {
            animation.tex.RenderTexture(g, animation.frameIDs[frameIndex], pos.x, pos.y);
        } else {
            g.drawImage(bitmap, pos.x, pos.y);
        }
    }
    
    public void PlayAnimation( Animation anim ) {
        this.animation = anim;
	frameIndex = 0;
	frameTick = animation.frameDurations[0];
    }    
    
    public void SetBitmap( Image bitmap ) {
        this.bitmap = bitmap;
	this.halfWidth = bitmap.getWidth() / 2;
	this.halfHeight = bitmap.getHeight() / 2;
    }
    
    public boolean IsPlayingAnimation() { 
        return animation != null;
    }
}
