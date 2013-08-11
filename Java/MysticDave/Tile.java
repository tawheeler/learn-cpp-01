/*
========================================================================

	A single square in the grid of a chamber

	Tied to a static floor image
	Can contain TileEntities

========================================================================
*/
package MysticDave;

import Entity.TileEntity;

public class Tile {
    
    public boolean    blocksOccupation; // whether this tile can contain TileEntities that move around (walls do not, floors do, for instance)
    public char       imageAddr;        // determines which image in the sprite sheet to use
    public TileEntity tileEntity;
    
    public Tile() {
        
    }
    
    public Tile( char imageAddr) {
        this.imageAddr = imageAddr;
    }
    
    public boolean IsOccupied() {
        boolean retval = blocksOccupation || tileEntity != null;
        return retval;
    }
}
