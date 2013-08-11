/*
========================================================================

	A sequence of sprites to play through
	Each frame has a set duration

========================================================================
*/
package MysticDave;

public class Animation {
    
    public int numFrames;
    
    public char[]       frameIDs;
    public TextureSheet tex;
    public int[]        frameDurations;
    public int          totalDuration;    
    
    public Animation( int numFrames, TextureSheet tex ) {
        this.numFrames = numFrames;
        this.tex       = tex;
        this.frameDurations = new int[numFrames];
        this.frameIDs  = new char[numFrames];
    }
    
    public void Init() {
        totalDuration = 0;
        for ( int i = 0; i < numFrames; i ++ ) {
            totalDuration += frameDurations[i];
        }
    }
    
}
