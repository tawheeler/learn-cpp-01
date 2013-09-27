/*
========================================================================

	An entity which has a tile as its location

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "Entity.h"
#include "Vec2i.h"
#include "Visual.h"
//#include "RuneSpace.h"
#include "Motion.h"
#include "Tile.h"
#include <string>

namespace MysticDave {
    class TileEntity : public Entity {
    public:

                                    TileEntity( std::string name, long uid );
						            ~TileEntity();

	    bool				        BlocksOccupation();
        void                        SetBlocksOccupation( bool blocks );

        Vec2i *                     GetPos();

        Visual *                    GetVisual();
        void                        SetVisual( Visual * visual );

        int                         GetRenderZ();
        void                        SetRenderZ( int z );

        bool                        IsFlammable();
        void                        SetFlammable( bool b );

        bool				        IsInMotion();
        int                         GetSourceTileLoc();  //the tile it is moving from or is currently in

        void				        AddMotion( Motion * motion );
        void                        HaltAllMotion( Motion * motion ); // halts all motions in the stack
	    void 		                MoveDir( int dir, int sourceTileLoc ); // have the TE move one tile in the specified direction
        //void                        MoveTarget( int targetTileLoc, int sourceTileLoc ); // have the TE move to the target tile

	    virtual void		        Update();
	    virtual void		        Cleanup();
        virtual void                Render( int x, int y );

        virtual void                OnEntered( TileEntity * actor ) {}
        virtual void                OnExited( TileEntity * actor ) {}

        virtual jsoncons::json      GetJSON();

    protected:
	
        int                         renderZ;
        int				            sourceTileLoc;

        bool				        blocksOccupation;
        bool                        flammable;

        Vec2i *                     pos;  // position in pixel space
        Visual*				        visual;
	    std::deque < Motion * >		motionQueue;
	    
	
    };
}