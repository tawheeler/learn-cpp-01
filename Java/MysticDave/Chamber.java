/*
========================================================================

	A room in the world
	Composed of a grid of tiles (12 x 11)

========================================================================
*/
package MysticDave;

import Managers.LogManager;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;
import org.newdawn.slick.SlickException;

public class Chamber {
    public static final int TILE_PIXEL_DIM = 64;      // how many pixels a standard tile is wide & tall
    public static final int CHAMBER_TILE_WIDTH = 12;  // how many tiles wide the chamber is (12)
    public static final int CHAMBER_TILE_HEIGHT = 11; // how many tiles tall the chamber is (11)
    
    public int chamberID; // a unique chamber identifer
    
    private Tile[] tileArr;    // array of tiles
    private int    numTiles;   // how many tiles we have
    private int    tileWidth;  // how many tiles wide the chamber is
    private int    tileHeight; // how many tiles high the chamber is
    
    private Image        floorImage; // image created by tile base images
    private TextureSheet texSheet;    // texture sheet for the tiles
    
    public Chamber( int chamberID ) {
        this.chamberID = chamberID;
        
        tileWidth = CHAMBER_TILE_WIDTH;
        tileHeight = CHAMBER_TILE_HEIGHT;
        numTiles = tileWidth * tileHeight;
        
        tileArr = new Tile[numTiles];
        for ( int i = 0; i < numTiles; i ++ ) {
            tileArr[i] = new Tile();
        }
        
        floorImage = null;
        
        texSheet = new TextureSheet( "./res/BackgroundTiles.gif", 64, 64 );
    } 
    
    public Tile GetTile( int x, int y ) {
        return tileArr[x + y*tileWidth];
    }
    
    public int GetTileWidth() {
        return tileWidth;
    }
    
    public int GetTileHeight() {
        return tileHeight;
    }
    
    public Image GetFloorImage() {
        return floorImage;
    }
    
    public void GenerateFloorImage() {
        
        // create an image if needed
        if ( floorImage == null ) {
            try {
                floorImage = new Image( tileWidth*TILE_PIXEL_DIM, tileHeight*TILE_PIXEL_DIM );
            } catch (SlickException ex) {
                LogManager.GetInstance().Write( LogManager.LOG.APP, ex.toString() );
            }
        }
          
        try {
            Graphics g = floorImage.getGraphics();

            // render each Tile's image
            int ind = 0;
            for ( int y = 0; y < tileHeight; y ++ ) {
                for ( int x = 0; x < tileWidth; x ++ ) {
                    texSheet.RenderTexture( g, (tileArr[ind]).imageAddr, x*TILE_PIXEL_DIM, y*TILE_PIXEL_DIM );
                    ind ++;
                }
            }
            
            g.flush();
        } catch (SlickException ex) {
            LogManager.GetInstance().Write( LogManager.LOG.APP, ex.toString() );
        }
    }
    
    public boolean IsInChamber( int x, int y ) {
        return ( x >= 0 && x < tileWidth && y >= 0 && y < tileHeight );
    }
    
    
}
