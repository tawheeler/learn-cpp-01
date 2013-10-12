/*
========================================================================

	A base class for all game "screens"
	Each screen is considered to be a layer which can update and be
	rendered. Screens are arranged on a stack, and may block those
	below them from being updated and/or rendered

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include <allegro5/allegro5.h>

namespace MysticDave {
    class BaseScreen {

    public:
	    virtual void		Init() = 0;
	    virtual void		Cleanup() = 0;
	    void				SetBlockUpdate( bool val );
	    void				SetBlockRender( bool val );
	    bool				BlocksUpdate() const;
	    bool				BlocksRender() const;
	    virtual void		Update() = 0;
	    virtual void		Render() const = 0;

	    bool				IsDead();
	    void				SetDead();

    protected:
						    BaseScreen();

    private:
	    bool				blocksRender; //whether it blocks screens below it from rendering
	    bool				blocksUpdate; //whether it blocks screens below it from updating
	
	    bool				isDead;       //whether to destroy or not

    };
}