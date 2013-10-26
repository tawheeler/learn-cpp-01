/*
========================================================================

	A position for a tile entity
    Comprised of a grid locatio and a pixel delta

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "Pos2D.h"
#include "Utils.h"
#include "Chamber.h"

using namespace MysticDave;

Pos2D::Pos2D() 
    :tileX(0),
     tileY(0),
     pixDX(0),
     pixDY(0)
{}

Pos2D::Pos2D( int tileX, int tileY )
    :tileX(tileX),
     tileY(tileY),
     pixDX(0),
     pixDY(0)
{}

Pos2D::Pos2D( const Pos2D& rhs )
    :tileX( rhs.GetTileX() ),
     tileY( rhs.GetTileY() ),
     pixDX( rhs.GetPixDX() ),
     pixDY( rhs.GetPixDY() )
{ }

Pos2D& Pos2D::operator=( const Pos2D& rhs ) {
    
    if ( this == &rhs ) {
        return *this;
    }

    this->tileX = rhs.GetTileX();
    this->tileY = rhs.GetTileX();
    this->pixDX = rhs.GetPixDX();
    this->pixDY = rhs.GetPixDY();

    return *this;
}

int Pos2D::GetTileNum() const {
    return Chamber::GetTileNumFromPos( tileX, tileY );
}

void Pos2D::SetPosFromTile( int tileNum ) {
    Pos2D::tileX = Chamber::GetTileXFromNum(tileNum);
    Pos2D::tileY = Chamber::GetTileYFromNum(tileNum);
    pixDX = 0;
    pixDY = 0;
}

void Pos2D::SetPosFromTile( int tileX, int tileY ) {
    Pos2D::tileX = tileX;
    Pos2D::tileY = tileY;
    pixDX = 0;
    pixDY = 0;
}

void Pos2D::SetPosFromPix( int pixX, int pixY ) {
    tileX = UTIL::PixToGrid( pixX );
    tileY = UTIL::PixToGrid( pixY );
    pixDX = pixX - tileX*TILE_DIM;
    pixDY = pixY - tileY*TILE_DIM;
}

void Pos2D::SetPixPos( int pixX, int pixY ) {
    pixDX = pixX - tileX*TILE_DIM;
    pixDY = pixY - tileY*TILE_DIM;
}