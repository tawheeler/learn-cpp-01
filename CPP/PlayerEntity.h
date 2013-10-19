/*
========================================================================

	A tile entity controlled by the player
	Mystic Dave!

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "TileEntity.h"
#include "AnimationVisual.h"
#include "Animation.h"
#include "Motion.h"
#include "jsoncons/json.hpp"

namespace MysticDave {
    class PlayerEntity : public TileEntity {

    public:

						        PlayerEntity();
                                PlayerEntity( jsoncons::json jobj );
		virtual 		        ~PlayerEntity();

        virtual void            Cleanup();

	    int					    GetDir();
	    void				    SetDir( int dir );
        
        //void                    AddAction( std::string animName, int dir ); // Add the given action to the action stack
        //bool                    IsActing(); // whether it is currently playing an action

	    void				    PlayAnimation( std::string animName );
	    bool				    IsPlayingAnimation();

        virtual jsoncons::json  GetJSON();

    private:

	    AnimationVisual *	    animVis;
	
	    int					    dir;         // the direction faced
	    int *				    standingArr; // images for the various directions

        std::map< std::string, Animation * > animationMap;

        void                    Init();
    };
}