/*
========================================================================

	A state machine for handling the screens
	Holds a stack of BaseScreen objects and controls their updating
	and rendering

========================================================================
*/

#include "ScreenManager.h"
#include <assert.h>

ScreenManager::ScreenManager() {
	// do nothing
}

ScreenManager::~ScreenManager() {
	// do nothing
}

void ScreenManager::StartUp() {
	// do nothing
}

void ScreenManager::ShutDown() {
	// clean up all states
	for ( iter = states.begin(); iter != states.end(); ) {
		(*iter)->Cleanup();
		delete (*iter);
		iter = states.erase(iter);
	}
}

ScreenManager& ScreenManager::GetInstance() {
	static ScreenManager* smSingleton = NULL;
	if ( smSingleton == NULL ) {
		smSingleton = new ScreenManager();
	}
	assert( smSingleton );
	return *smSingleton;
}

/*
================================================
HandleEvent

	Has the game screens handle events starting 
	from the top of the stack, working its way 
	down until it hits bottom, or a screen 
	which blocks updating
================================================
 */
void ScreenManager::HandleEvent( ALLEGRO_EVENT evt ) {
	//start from the top (index 0) and work your way down (last index)
    //for ( deque< twBaseScreen * >::size_type i = 0; i < states.size(); i++ ) {

	for ( iter = states.begin(); iter != states.end(); ++iter ) {
        (*iter)->HandleEvent( evt );  //update it
        if ( (*iter)->BlocksUpdate() ) {
            break;  //exit the for loop, since it blocks further travel
        }
    }
}

/*
================================================
Update

	Update the game screens, starting from the
	top of the stack, working its way down until 
	it hits bottom, or a screen which blocks
	updating
================================================
 */
void ScreenManager::Update() {
	//add screens from stateToAdd
	for ( iter = statesToAdd.begin(); iter != statesToAdd.end(); ) {
		states.push_front( (*iter) );
		iter = statesToAdd.erase(iter);
	}

	//start from the top (index 0) and work your way down (last index)
	for ( iter = states.begin(); iter != states.end(); ++iter ) {
        (*iter)->Update();  //update it
        if ( (*iter)->BlocksUpdate() ) {
            break;  //exit the for loop, since it blocks further travel
        }
    }

	//cull the dead
	for ( iter = states.begin(); iter != states.end();  ) {
        if ( (*iter)->IsDead() ) {
			(*iter)->Cleanup();
			delete (*iter);
			iter = states.erase(iter);
		} else {
			++iter;
		}
    }
}

/*
================================================
Render

	Renders the game screens in order from 
	lowest visible screen to top
================================================
 */
void ScreenManager::Render() {
	//higher screens can block lower ones...
	int lowestDrawableIndex = -1;
	for ( iter = states.begin(); iter != states.end(); ++iter ) {
		lowestDrawableIndex ++; //increment as you go deeper
		if( (*iter)->BlocksRender() ){
			break; //exit out
		}
	}

	//...but lower screens need to be rendered first
	while( lowestDrawableIndex >= 0 ){
		states[lowestDrawableIndex]->Render(); //render it
		lowestDrawableIndex--;
	}
}

void ScreenManager::PushGameScreen( BaseScreen* gs ) {
	statesToAdd.push_front( gs ); //insert it in first
}