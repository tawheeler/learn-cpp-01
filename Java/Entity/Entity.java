/*
========================================================================

	An abstract game object
	Grants fundamental ability to receive messages, update, 
	posseses a uid, and a type

========================================================================
*/
package Entity;

public abstract class Entity {
    public static enum TYPE { MISC, SYGALDRY, LOGICTIMER, BLOCK, PLAYER, ENEMY, DOOR, FIREPLACE, HAZARD }
    
    public int UID;   // unique id
    public TYPE type;  // type of object

    public Entity( TYPE type ) {
        this.type = type;
    }
    
    public Entity( TYPE type , int uid ) {
        this.type = type;
        this.UID  = uid;
    }

    public void Update() {
        // do nothing
    }
    
    public void Cleanup() {
       // do nothing
    }
}
