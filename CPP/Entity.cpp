/*
========================================================================

	An abstract game object
	Grants fundamental ability to receive messages, update, 
	posseses a uid, and a type

========================================================================
*/

#include "Entity.h"

Entity::Entity( int type ) {
	//GameObjectManager* twGameObjectManager = &(GameObjectManager::GetInstance());
	//Entity::UID = twGameObjectManager->GetNextUID();
	Entity::type = type;
}

Entity::Entity( int type, int uid ) {
	Entity::UID  = uid;
	Entity::type = type;
}

Entity::~Entity() {
	// do nothing
}

void Entity::Update() {
	// do nothing
}

void Entity::Cleanup() {
	// do nothing
}