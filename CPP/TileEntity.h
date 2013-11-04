/*
========================================================================

	An entity which has a tile as its location

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "Entity.h"
#include "Pos2D.h"
#include "Visual.h"
#include "Motion.h"
#include <deque>
#include <string>

namespace MysticDave {
    class Chamber;

    class TileEntity : public Entity {
    public:

                                    TileEntity( std::string name, int uid );
                                    TileEntity( jsoncons::json jobj );
		virtual                     ~TileEntity();

	    bool				        BlocksOccupation();
        void                        SetBlocksOccupation( bool blocks );

        Pos2D *                     GetPos() const { return pos; }
        Visual *                    GetVisual() const { return visual; }
        void                        SetVisual( Visual * visual );

        int                         GetRenderZ() const { return renderZ; }
        void                        SetRenderZ( int z ) { TileEntity::renderZ = z; }

        bool                        IsFlammable() const { return flammable; }
        void                        SetFlammable( bool b ) { TileEntity::flammable = b; }

        bool				        IsInMotion() const;
        int                         GetSourceTileLoc() const { return sourceTileLoc; }  //the tile it is moving from or is currently in

        bool                        CanMove( int dir, Chamber * C );
        void				        AddMotion( Motion * motion );
        //void                        HaltAllMotion( Motion * motion ); // halts all motions in the stack
	    void 		                MoveDir( int dir, int ticksInMove ); // have the TE move one tile in the specified direction
        //void                        MoveTarget( int targetTileLoc, int sourceTileLoc ); // have the TE move to the target tile

	    virtual void		        Update();
	    virtual void		        Cleanup();
        virtual void                Render( int x, int y );

        virtual void                OnEntered( TileEntity * actor ) {} // called when actor enteres the space this TE is in
        virtual void                OnExited( TileEntity * actor ) {}  // called when actor leaves the space this TE is in
        virtual void                OnMoveCompleted( Motion * completedMotion ); // called whenever this tile entity completes a motion

        virtual void                OnInput( const std::string I );

        virtual jsoncons::json      GetJSON();

    protected:
	
        int                         renderZ;
        int				            sourceTileLoc;

        bool				        blocksOccupation;
        bool                        flammable;

        Pos2D *                     pos;  // position in pixel space
        Visual*				        visual;
	    std::deque < Motion * >		motionQueue;

        void                        Init();
    };
}