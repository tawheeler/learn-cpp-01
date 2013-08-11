package Screens;

import Entity.PlayerEntity;
import MysticDave.Chamber;
import MysticDave.Tile;
import MysticDave.Utils;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Input;

/**
 *
 * @author Tim
 */
public class MainScreen extends BaseScreen {
    
    public boolean keys[] = new boolean[9];
    
    public static final int UP    = 0;
    public static final int DOWN  = 1;
    public static final int LEFT  = 2;
    public static final int RIGHT = 3;
    public static final int SPACE = 4;
    
    public Chamber curChamber;
    public PlayerEntity player;
    
    public void Init() {
        keys[UP] = keys[DOWN] = keys[LEFT] = keys[RIGHT] = keys[SPACE] = false;
        curChamber = new Chamber(1);
        
        char chamberTileInd[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
                                20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
                                20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
                                20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
                                20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
                                20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
                                20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
                                20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
                                20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
                                20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22,
                                40, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 42 };
        
        int ind = 0;
	for ( int y = 0; y < 11; y ++ ) {
            for ( int x = 0; x < 12; x ++ ) {
		curChamber.GetTile( x, y ).imageAddr = chamberTileInd[ind];
                if ( x == 0 || x == 11 || y == 0 || y == 10 ) {
                    curChamber.GetTile( x, y ).blocksOccupation = true;
                }
		ind++;
            }
	}
        
        curChamber.GenerateFloorImage();
        
        player = new PlayerEntity();
	player.tileX = 5;
	player.tileY = 4;
	player.SetPixPosToMatchTilePos();
    }
    
    public void Cleanup() {
        // do nothing
    }
    
    @Override
    public void Update(Input I) {
        
        // deal with input
        keys[DOWN] = I.isKeyDown( Input.KEY_DOWN );
        keys[LEFT] = I.isKeyDown( Input.KEY_LEFT );
        keys[RIGHT] = I.isKeyDown( Input.KEY_RIGHT );
        keys[UP] = I.isKeyDown( Input.KEY_UP );
        keys[SPACE] = I.isKeyDown( Input.KEY_SPACE );
        
        if (player != null) {

            int numDirsPressed = (keys[DOWN] ? 1 : 0) + (keys[UP] ? 1 : 0) + (keys[LEFT] ? 1 : 0) + (keys[RIGHT] ? 1 : 0);

            if (numDirsPressed == 1 && !(player.IsInMotion()) ) {

                int dx = 0;
                int dy = 0;
                if (keys[DOWN]) {
                    dy = 1;
                } else if (keys[UP]) {
                    dy = -1;
                } else if (keys[RIGHT]) {
                    dx = 1;
                } else if (keys[LEFT]) {
                    dx = -1;
                }

                int desDir = Utils.DirFromDelta(dx, dy);
                if (player.GetDir() != desDir) {
                    player.SetDir(desDir);
                } else {
                    int tx = player.tileX;
                    int ty = player.tileY;
                    if (curChamber.IsInChamber(tx + dx, ty + dy)) {
                        // check if target is free
                        Tile targetTile = curChamber.GetTile(tx + dx, ty + dy);
                        if (!(targetTile.IsOccupied())) { // if free
                            targetTile.tileEntity = player;  // add to next
                            player.Move(desDir, curChamber.GetTile(tx, ty));
                        }
                    }
                }
            }

            player.Update();
        }
    }
    
    @Override
    public void Render(Graphics g) {
        g.drawImage( curChamber.GetFloorImage(), 0, 0 );
        player.visual.Render( g );
    }
    
}
