/*
========================================================================

	The collection of objects bound in a force net
	Pushing one pushes all of them

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "TileEntity.h"
#include "Chamber.h"
#include <deque>

namespace MysticDave {
    class ForceNet {
    public:

											    ForceNet();
											    ~ForceNet();

	    bool									CanMove( int dir, Chamber * C );
	    void									Move( int dir, Chamber * C );

	    void									AddTileEntity( TileEntity * toAdd );

        int                                     CalcMoveType();
        int                                     GetSize() { return tileEntityList.size(); }
	    bool									Contains( int uid );
        TileEntity *                            GetTileEntityAtIndex( int index ) { return tileEntityList[index]; }

    private:

	    std::deque < TileEntity * >				tileEntityList;
    };
}