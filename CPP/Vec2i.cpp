/*
========================================================================

	A 2D vector class, integers

    Author: Tim Wheeler
    Contact: timwheeleronline@gmail.com

========================================================================
*/

#include "Vec2i.h"
#include <math.h>

using namespace MysticDave;

Vec2i::Vec2i() {
	x = y = 0;
}

Vec2i::Vec2i( int x, int y ) {
	Vec2i::x = x;
	Vec2i::y = y;
}

Vec2i::~Vec2i() {
	// do nothing
}

void Vec2i::Set( int x, int y ) {
	Vec2i::x = x;
	Vec2i::y = y;
}

void Vec2i::Set( Vec2i * v ) {
	Vec2i::x = v->x;
	Vec2i::y = v->y;
}

int	Vec2i::Dot( int x, int y ) {
	return Vec2i::x * x + Vec2i::y * y;
}

int	Vec2i::Dot( Vec2i * target ) {
	return (x * target->x) + (y * target->y);
}

void Vec2i::Neg() {
	x = -x;
	y = -y;
}

void Vec2i::Neg( Vec2i * source, Vec2i * retval ) {
	retval->x = -source->x;
	retval->y = -source->y;
}

void Vec2i::Plus( Vec2i * target ) {
	Vec2i::x += target->x;
	Vec2i::y += target->y;
}

void Vec2i::Plus( int x, int y ) {
	Vec2i::x += x;
	Vec2i::y += y;
}

void Vec2i::Plus( Vec2i * A, Vec2i * B, Vec2i * retval ) {
	retval->x = A->x + B->x;
	retval->y = A->y + B->y;
}

void Vec2i::Sub( Vec2i * target ) {
	Vec2i::x -= target->x;
	Vec2i::y -= target->y;
}

void Vec2i::Sub( Vec2i * A, Vec2i * B, Vec2i * retval ) {
	retval->x = A->x - B->x;
	retval->y = A->y - B->y;
}

void Vec2i::Mult( int val ) {
	x *= val;
	y *= val;
}

void Vec2i::Mult( Vec2i * target, int val, Vec2i * retval ) {
	retval->x = target->x * val;
	retval->y = target->y * val;
}

float Vec2i::Norm() {
	return sqrt( (float)(x*x + y*y) );
}

int Vec2i::Norm2() {
	return x*x + y*y;
}

float Vec2i::Dist( Vec2i * A, Vec2i * B ) {
	int dx = A->x - B->x;
	int dy = A->y - B->y;
	return sqrt( (float)(dx*dx + dy*dy) );
}


