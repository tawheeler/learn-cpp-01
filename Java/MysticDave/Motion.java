/*
========================================================================

	A translational action something undertakes

========================================================================
*/
package MysticDave;

public class Motion {

    int	totalMotionTime;  // number of ticks the overall motion takes
    int	motionTick;       // the tick the motion is currently in

    int	startX; // [pix]
    int	startY; // [pix]
    int	destX;  // [pix]
    int	destY;  // [pix]

    Vec2i vec;    // the vector tied to the motion
    
    public Motion( Vec2i vec, int destX, int destY, int totalMotionTime ) {
        this.vec             = vec;
	this.startX          = vec.x;
	this.startY          = vec.y;
	this.destX           = destX;
	this.destY           = destY;
	this.totalMotionTime = totalMotionTime;
	this.motionTick      = totalMotionTime;
    }
    
    public void	Update() {
        //move countdown
        if ( motionTick > 0 ) {
            motionTick--;
            vec.x = GetPixelX();
            vec.y = GetPixelY();
        }
    }
    
    public boolean IsDone() {
        return motionTick <= 0;
    }
    
    private int GetPixelX() {
        float u = ((float)totalMotionTime - (float) motionTick) / totalMotionTime;
        int retval = (int) Utils.Lerp( u, startX, destX );
        return retval;
    }
    
    private int	GetPixelY() {
        float u = ((float)totalMotionTime - (float) motionTick) / totalMotionTime;
        int retval = (int) Utils.Lerp( u, startY, destY );
        return retval;
    }
    
}
