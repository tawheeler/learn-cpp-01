/*
========================================================================

	A BaseScreen which allows the user to edit a given chamber

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "ChamberEditorScreen.h"
#include "LogManager.h"
#include "Globals.h"
#include "jsoncons/json.hpp"
#include "InputManager.h"

using jsoncons::json;
using namespace MysticDave;

void ChamberEditorScreen::Init() {
    keysPressed = (InputManager::GetInstance()).GetKeysPressed();
    keysToggled = (InputManager::GetInstance()).GetKeysToggled();
}

void ChamberEditorScreen::Cleanup() {
	// do nothing
}

void ChamberEditorScreen::Update() {

    Chamber * curChamber = (ChamberManager::GetInstance()).GetCurrentChamber();

}

void ChamberEditorScreen::Render() const {
	(ChamberManager::GetInstance()).GetCurrentChamber()->Render( 0, 0 );
}