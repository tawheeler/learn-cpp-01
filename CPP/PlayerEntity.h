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
#include <list>

namespace MysticDave {
    class PlayerEntity : public TileEntity {

    public:

        enum MOVE{ WALK, PUSH, TRY_PUSH };

						        PlayerEntity();
                                PlayerEntity( jsoncons::json jobj );
		virtual 		        ~PlayerEntity();

        virtual void            Cleanup();

	    int					    GetDir();
	    void				    SetDir( int dir );

	    void				    PlayAnimation( std::string animName );
        void                    MoveWithAnimation( int dir, int ticksInMove, int moveType );
	    bool				    IsPlayingAnimation();

        void                    AddInventoryItem( int id );
        void                    RemoveInventoryItem( int id );
        std::list< int > *      GetInventory() { return &inventory; }
        bool                    HasInventoryItem( int id );
        
        void                    AddQuest( std::string questName, int questState );
        void                    SetQuest( std::string questName, int questState );
        bool                    HasQuest( std::string questName );
        int                     GetQuest( std::string questName );

        virtual jsoncons::json  GetJSON();

    private:

	    AnimationVisual *	    animVis;
	
	    int					    dir;         // the direction faced
	    int *				    standingArr; // images for the various directions

        std::map< std::string, Animation * > animationMap;
        std::list< int >        inventory;   // holds all inventory items
        std::map< std::string, int > questMap; // keys quest name to quest state

        void                    Init();
    };
}