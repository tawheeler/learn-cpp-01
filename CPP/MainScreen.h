/*
========================================================================

	A BaseScreen which runs the standard game mode

========================================================================
*/

#pragma once

#include <allegro5/allegro5.h>
#include "BaseScreen.h"
#include "Chamber.h"
#include "PlayerEntity.h"

class MainScreen : public BaseScreen {
public:
	bool keys[9];
	enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};

	void									Init();
	void									Cleanup();
	void									HandleEvent( ALLEGRO_EVENT evt );
	void									Update();
	void									Render() const;

	Chamber *								curChamber;
	PlayerEntity *							player;
};