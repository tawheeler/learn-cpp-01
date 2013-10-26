/*
========================================================================

	A position for a tile entity
    Comprised of a grid locatio and a pixel delta

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#pragma once

#include "Globals.h"
#include "Vec2i.h"

namespace MysticDave {
    class Pos2D {
    public:

        Pos2D();
        Pos2D( int tileX, int tileY );
        Pos2D( const Pos2D& rhs );

        Pos2D& operator=( const Pos2D& rhs );

        int GetTileX() const { return tileX; } // in tile coord
        int GetTileY() const { return tileY; } // in tile coord
        int GetPixX() const { return tileX*TILE_DIM + pixDX; }  // in pix coord
        int GetPixY() const { return tileY*TILE_DIM + pixDY; }  // in pix coord
        int GetPixDX() const { return pixDX; } // in pix coord
        int GetPixDY() const { return pixDY; } // in pix coord
        int GetTileNum() const;

        void SetTileX( int tileX ) { Pos2D::tileX = tileX; };
        void SetTileY( int tileY ) { Pos2D::tileY = tileY; };
        void SetPixDX( int pixDX ) { Pos2D::pixDX = pixDX; };
        void SetPixDY( int pixDY ) { Pos2D::pixDY = pixDY; };
        void SetPosFromTile( int tileNum );
        void SetPosFromTile( int tileX, int tileY ); // sets the position to be on the tile (zeros out PixDX & PixDY)
        void SetPosFromPix( int pixX, int pixY ); //sets position to closest tile loc & appropraitely sets pixDX&Y
        void SetPixPos( int pixX, int pixY );  // sets relative pixel positon, does not change tile location
        
        void SetToClosestTile() { SetPosFromPix( GetPixX(), GetPixY() ); }

    private:
        int tileX; // tile location in grid space
        int tileY; // tile location in grid space
        int pixDX; // delta in pixels off of the tile location
        int pixDY; // delta in pixels off of the tile location
    };
}