/*
========================================================================

	A base class for all game "screens"
	Each screen is considered to be a layer which can update and be
	rendered. Screens are arranged on a stack, and may block those
	below them from being updated and/or rendered

========================================================================
*/

#include "BaseScreen.h"

BaseScreen::BaseScreen() {
	blocksRender = true;
	blocksUpdate = true;
	isDead = false;
}

void BaseScreen::Init() {
	//do nothing
}

void BaseScreen::SetBlockUpdate( bool val ) {
	blocksUpdate = val;
}

void BaseScreen::SetBlockRender( bool val ) {
	blocksRender = val;
}

bool BaseScreen::BlocksUpdate() const {
	return blocksUpdate;
}

bool BaseScreen::BlocksRender() const {
	return blocksRender;
}

bool BaseScreen::IsDead() {
	return isDead;
}

void BaseScreen::SetDead() {
	isDead = true;
}