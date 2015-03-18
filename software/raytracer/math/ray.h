// 
// Copyright (C) 2015 Oguz Meteer
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
// 

#ifndef RAY_H
#define RAY_H

#include <stdio.h>
#include <Vec3.h>
#include "vec3_16.h"
#include "vec_math.h"

using namespace librender;

class Ray
{
public:
	Ray( void )
	:	origin( 0.0f, 0.0f, 0.0f ),
		direction( 0.0f, 0.0f, 0.0f )
	{}
	
	Ray( const Vec3 orig, const Vec3 dir )
	:	origin( orig ),
		direction( dir )
	{}

	Vec3 origin;
	Vec3 direction;
};

class Ray16
{
public:
	Ray16( void )
	:	origin( Vec3_16() ),
		direction( Vec3_16() )
	{}
	
	Ray16( const Vec3_16 orig, const Vec3_16 dir )
	:	origin( orig ),
		direction( dir )
	{}
	
	Vec3_16 origin;
	Vec3_16 direction;
};

#endif
