/*
========================================================================

	A 2D vector class, integers

========================================================================
*/

#pragma once

class Vec2i {
public:

	int				x;
	int				y;

					Vec2i();
					Vec2i( int x, int y );
					~Vec2i();

	void			Set( int x, int y );
	void			Set( Vec2i * v );

	int				Dot( int x, int y );
	int				Dot( Vec2i * target );

	void			Neg();
	static void		Neg( Vec2i * source, Vec2i * retval );

	void			Plus( Vec2i * target );
	void			Plus( int x, int y );
	static void		Plus( Vec2i * A, Vec2i * B, Vec2i * retval );

	void			Sub( Vec2i * target );
	static void		Sub( Vec2i * A, Vec2i * B, Vec2i * retval );

	void			Mult( int val );
	static void		Mult( Vec2i * target, int val, Vec2i * retval );

	float			Norm();
	int				Norm2();

	float			Dist( Vec2i * A, Vec2i * B );
};