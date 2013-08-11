/*
========================================================================

	An entity controlled by the player
	Mystic Dave!

========================================================================
*/
package Entity;

import Managers.ResourceManager;
import MysticDave.*;
import Visuals.AnimationVisual;

public class PlayerEntity extends TileEntity {
    
    private AnimationVisual animVis;
    private Motion motion;
    private Tile sourceTile;  // the tile moved from, so we can free it after
    
    private int dir;           // the direction faced
    private int[] standingArr; // images for the various directions
    
    private Animation animNorth;
    private Animation animEast;
    private Animation animSouth;
    private Animation animWest;
    
    public PlayerEntity() {
        super( Entity.TYPE.PLAYER, 1 );
        animVis = new AnimationVisual( pos, ResourceManager.GetInstance().GetBitmap("./res/Sprites/Dave2/Dave_S_L.png") );
        visual = animVis;
        motion = null;
        sourceTile = null;
	dir = Utils.DIR_SOUTH;

	standingArr = new int[4];
	standingArr[Utils.DIR_NORTH] = 3;
	standingArr[Utils.DIR_EAST]  = 1;
	standingArr[Utils.DIR_SOUTH] = 7;
	standingArr[Utils.DIR_WEST]  = 29;

	// note: resource manager will delete this
	TextureSheet tex = (ResourceManager.GetInstance()).LoadTextureSheet("./res/Sprites/DaveSpriteSheet.png", Globals.TILE_DIM, Globals.TILE_DIM);

	animNorth = new Animation( 2, tex );
	animNorth.frameDurations[0] = 12; animNorth.frameIDs[0] = 11;
	animNorth.frameDurations[1] = 12; animNorth.frameIDs[1] = 3;
	animNorth.Init();

	animEast = new Animation( 2, tex );
	animEast.frameDurations[0] = 12; animEast.frameIDs[0] = 8;
	animEast.frameDurations[1] = 12; animEast.frameIDs[1] = 1;
	animEast.Init();

	animSouth = new Animation( 2, tex );
	animSouth.frameDurations[0] = 12; animSouth.frameIDs[0] = 15;
	animSouth.frameDurations[1] = 12; animSouth.frameIDs[1] = 7;
	animSouth.Init();
        
	animWest = new Animation( 2, tex );
	animWest.frameDurations[0] = 12; animWest.frameIDs[0] = 22;
	animWest.frameDurations[1] = 12; animWest.frameIDs[1] = 29;
	animWest.Init();
    }
    
    @Override
    public void Update() {
        if (motion != null) {
            motion.Update();

            if (motion.IsDone()) {
                motion = null;
                if (sourceTile != null) {
                    sourceTile.tileEntity = null;  // free it
                    sourceTile = null;
                }
                SetTilePosToMatchPixPos();  //update position
            }
        }
    }
    
    public int GetDir() {
        return dir;
    }
    
    public void SetDir( int dir ) {
        this.dir = dir;
        animVis.SetBitmap( (ResourceManager.GetInstance()).GetTextureSheet("./res/Sprites/DaveSpriteSheet.png").GetTexture( standingArr[dir] ) );
    }
    
    public void PlayAnimation( Animation anim ) {
        animVis.PlayAnimation( anim );
    }
    
    public void AddMotion( Motion motion ) {
	this.motion = motion;
    }
    
    public void Move( int dir, Tile curTile ) {
        switch (dir) {
            case Utils.DIR_NORTH:
                animVis.PlayAnimation(animNorth);
                motion = new Motion(pos, pos.x, pos.y - Globals.TILE_DIM, animNorth.totalDuration);
                break;
            case Utils.DIR_EAST:
                animVis.PlayAnimation(animEast);
                motion = new Motion(pos, pos.x + Globals.TILE_DIM, pos.y, animEast.totalDuration);
                break;
            case Utils.DIR_SOUTH:
                animVis.PlayAnimation(animSouth);
                motion = new Motion(pos, pos.x, pos.y + Globals.TILE_DIM, animSouth.totalDuration);
                break;
            case Utils.DIR_WEST:
                animVis.PlayAnimation(animWest);
                motion = new Motion(pos, pos.x - Globals.TILE_DIM, pos.y, animWest.totalDuration);
                break;
        }

        sourceTile = curTile;
    }
    
    public boolean IsPlayingAnimation() {
        return animVis.IsPlayingAnimation();
    }
    
    public boolean IsInMotion() {
        return motion != null;
    }
    
}
