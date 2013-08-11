/*
========================================================================

	An entity which has a tile as its location

========================================================================
*/
package Entity;

import MysticDave.Utils;
import MysticDave.Vec2i;
import Visuals.Visual;

public class TileEntity extends Entity {
    
    public boolean blocksOccupation;
    public Vec2i   pos;
    public int     tileX;  // position in tile space
    public int     tileY;
    public Visual  visual;
    
    public TileEntity( Entity.TYPE type ) {
        super(type);
        pos = new Vec2i();
        blocksOccupation = false;
    }
    
    public TileEntity( Entity.TYPE type, int uid ) {
        super( type, uid );
        pos = new Vec2i();
        blocksOccupation = false;
    }
    
    // matches tile position from pixel position
    public void SetTilePosToMatchPixPos() {
        tileX = Utils.PixToGrid( pos.x );
	tileY = Utils.PixToGrid( pos.y );
    }
    
    public void SetPixPosToMatchTilePos() {
        pos.x = Utils.GridToPix( tileX );
	pos.y = Utils.GridToPix( tileY );
    }
    
    @Override
    public void Cleanup() {
        if ( visual != null ) {
            visual.Cleanup();
        }
    }
    
}
