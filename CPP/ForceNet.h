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

        int                                     GetSize() { return tileEntityList.size(); }
	    bool									Contains( int uid );

    private:
	    std::deque < TileEntity * >				tileEntityList;
    };
}