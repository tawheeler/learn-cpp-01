/*
========================================================================

	Handles all loaded game resources, including images, sounds etc.

========================================================================
*/
package Managers;

import MysticDave.TextureSheet;
import java.util.ArrayList;
import java.util.HashMap;
import org.newdawn.slick.Image;
import org.newdawn.slick.SlickException;

public class ResourceManager {
    
    private ArrayList < Image > bitmapList = new ArrayList();
    private ArrayList< TextureSheet > texSheetList = new ArrayList();
    
    private HashMap < String, Image > bitmapMap = new HashMap();
    private HashMap < String, TextureSheet > texSheetMap = new HashMap();
    
    
    private static ResourceManager instance = null;  //the only instance
    
    public void StartUp() {
        // do nothing
    }
    
    public void ShutDown() {
        bitmapList.clear();
        bitmapMap.clear();
        texSheetList.clear();
        texSheetMap.clear();
    }
    
    // loads it if it needs to, otherwise returns it
    public Image GetBitmap( String name ) {
        Image retval = bitmapMap.get( name );
        if ( retval == null ) {
            try {
                // create a new one
                retval = new Image( name );
                bitmapList.add(retval);
                bitmapMap.put( name, retval);
            } catch (SlickException ex) {
                LogManager.GetInstance().Write( LogManager.LOG.APP, ex.toString() );
            }
        }
        return retval;
    }
    
    // returns it if it has already been loaded
    public TextureSheet GetTextureSheet ( String name ) {
	return texSheetMap.get( name );
    }
    
     // returns if it has already been loaded, otherwise creates it
    public TextureSheet LoadTextureSheet ( String name, int texWidth, int texHeight ) {
        TextureSheet retval = texSheetMap.get( name );
        if ( retval == null ) {
            retval = new TextureSheet( name, texWidth, texHeight );
            texSheetList.add( retval );
            texSheetMap.put( name, retval );
        }
        return retval;
    }
    
    /**
     * Obtain the singleton instance
     * @return
     */
    public static ResourceManager GetInstance(){
        if(instance == null){
            instance = new ResourceManager();
        }
        return instance;
    }
    
}
