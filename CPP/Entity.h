/*
========================================================================

	An abstract game object
	Grants fundamental ability to receive messages, update, 
	posseses a uid, and a type

========================================================================
*/

class Entity {
public:
	enum TYPE{TYPE_MISC, TYPE_SYGALDRY, TYPE_LOGICTIMER, TYPE_BLOCK, TYPE_PLAYER, TYPE_ENEMY, TYPE_DOOR, TYPE_FIREPLACE, TYPE_HAZARD };

	int					UID;   // unique id
	int					type;  // type of object

						Entity( int type );
						Entity( int type, int uid );
						~Entity();

	virtual void		Update();
	virtual void		Cleanup();
	
	//virtual void		ReceiveMessage( Message * msg ) = 0;
	
};