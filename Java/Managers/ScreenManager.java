/*
========================================================================

	A state machine for handling the screens
	Holds a stack of BaseScreen objects and controls their updating
	and rendering

========================================================================
*/

package Managers;

import Screens.BaseScreen;
import java.util.ArrayList;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;

public class ScreenManager {
    
    private ArrayList<BaseScreen> screenStack = new ArrayList();
    private static ScreenManager instance = null;  //the only instance
    
    public void StartUp() {
         // do nothing
    }
    
    public void ShutDown() {
        // clear all states
        for (int a = 0; a < screenStack.size(); a++) {
            BaseScreen gs = screenStack.get(a);
            gs.Cleanup();
        }
        screenStack.clear();
    }
    
    /**
     * Renders the game screens in order from lowest-visible
     * to top
     */
    public void Render(GameContainer gc, Graphics g) throws SlickException {

        //Higher screens can block lower ones...
        int lowestDrawableIndex = -1;
        for (BaseScreen gs : screenStack) {
            lowestDrawableIndex++;  //increment as you go deeper
            if (gs.BlocksRender()) {
                break;  //exit out
            }
        }

        //...but lower screens need to be rendered first.
        while (lowestDrawableIndex >= 0) {
            screenStack.get(lowestDrawableIndex).Render(g);  //render it
            lowestDrawableIndex--;
        }

       g.flush();
    }
    
    /**
     * update the game screens, starting from the top of the stack,
     * working your way down until you hit bottom, or a screen when blocks
     * updating those below
     */
    public void Update(Input I) throws SlickException {
        //start from the top (index 0) and work your way down (last index)
        for (int a = 0; a < screenStack.size(); a++) {
            BaseScreen gs = screenStack.get(a);
            gs.Update(I);  //update it
            if (gs.BlocksUpdate()) {
                break;  //exit the for loop, since it blocks further travel
            }
        }
    }
    
        /**
     * pushes a new game screen onto the game screen stack
     * note that the game screen stack is actually list, but to an
     * outside viewer is treated as a stack
     */
    public void PushGameScreen(BaseScreen gs) {
        screenStack.add(0, gs);  //insert it in first
    }
    
    /**
     * Obtain the singleton instance
     * @return
     */
    public static ScreenManager GetInstance(){
        if(instance == null){
            instance = new ScreenManager();
        }
        return instance;
    }
}
