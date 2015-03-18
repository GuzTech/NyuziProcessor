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

#include "Vec3.h"

#ifndef SPHERE_H
#define SPHERE_H

using namespace librender;

class Sphere
{
public:
	Sphere()
	:	position( 0.0f, 0.0f, 0.0f ),
		radius( 0.0f ),
		radiusSq( 0.0f )
	{}
	
	Sphere( const Vec3 pos, const float radius )
	:	position( pos ),
		radius( radius ),
		radiusSq( radius * radius )
	{}
	
	void SetColor( const Vec3 color )
	{
		this->color = color;
		color16 = Vec3_16( color );
	}
	
	// Checks if a ray intersects with this sphere.
	// Returns true if the ray intersects with this sphere, otherwise returns false.
	//
	// ray		[IN]  The ray that will be used.
	// dist1	[OUT] The distance between the ray position and the first point of
	//				  intersection.
	// dist2	[OUT] The distance between the ray position and the second point of
	//				  intersection.
	__attribute__((overloadable))
	bool Intersect( const Ray ray, float &dist1, float &dist2 );
	
	__attribute__((overloadable))
	uint32_t Intersect( const Ray16 ray, vecf16_t &dist1, vecf16_t &dist2 );
	
	Vec3  position;
	float radius;
	float radiusSq;		// Radius squared
	
	Vec3	color;
	Vec3_16	color16;
	float	reflectivity;
	float	specular;
};

#endif // SPHERE_H
