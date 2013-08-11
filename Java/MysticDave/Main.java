/*
========================================================================

	The main function, which initializes Allegro and runs the game loop

========================================================================
*/

package MysticDave;

import Managers.*;
import Screens.BaseScreen;
import Screens.MainScreen;
import org.newdawn.slick.AppGameContainer;
import org.newdawn.slick.BasicGame;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.SlickException;

/**
 * GameKernel
 *    Where the game begins.
 *    Is a Singleton
 * @author Tim
 */
public class Main extends BasicGame {
    
    private GameContainer gc;
    
    private LogManager      myLogManager;
    private ScreenManager   myScreenManager;
    private ResourceManager myResourceManager;
    
    private boolean done;
    
    public Main() {
        super("Mystic Dave");
    }
    
    public void AbortGame( String message ) {
        if ( myLogManager != null ) {
		myLogManager.Write( LogManager.LOG.APP, "%s\n", message );
	} else {
		System.out.printf( "%s \n", message );
	}
        System.exit(1);
    }
            
    @Override
    public void init(GameContainer gc) throws SlickException {
        this.gc = gc;
        
        myLogManager = LogManager.GetInstance();
	myLogManager.StartUp();
        myScreenManager = ScreenManager.GetInstance();
        myScreenManager.StartUp();
        myResourceManager = ResourceManager.GetInstance();
        myResourceManager.StartUp();
        
        BaseScreen screen = new MainScreen();
	screen.Init();
	myScreenManager.PushGameScreen( screen );
        
        myLogManager.Write( LogManager.LOG.APP, "Finished Main Initialization\n" );
        done = false;
    }

    @Override
    /**
     * Renders the game screens in order from lowest-visible
     * to top
     */
    public void render(GameContainer gc, Graphics g) throws SlickException {
        myScreenManager.Render(gc, g);
    }

    /**
     * update the game screens, starting from the top of the stack,
     * working your way down until you hit bottom, or a screen when blocks
     * updating those below
     */
    @Override
    public void update(GameContainer arg0, int delta) throws SlickException {
        myScreenManager.Update(gc.getInput());
    }
    
    public void Shutdown() {
        myResourceManager.ShutDown();
        myScreenManager.ShutDown();
        myLogManager.ShutDown();
    }


    public static void main(String[] args) throws SlickException {
        Main myMain = new Main();
        AppGameContainer app = new AppGameContainer(myMain);  //create the application game container
        app.setDisplayMode(Globals.SCREEN_WIDTH, Globals.SCREEN_HEIGHT, false);  //set to width = 800, height = 600, not in fullscreen
        app.setTargetFrameRate(Globals.FPS);  //set the target frame rate
        app.setTitle("Mystic Dave");
        app.start();
    }
}
