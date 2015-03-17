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

#include "ray.h"
#include "sphere.h"

// Checks if a ray intersects with this sphere.
// Returns true if the ray intersects with this sphere, otherwise returns false.
//
// ray		[IN]  The ray that will be used.
// dist1	[OUT] The distance between the ray position and the first point of
//				  intersection.
// dist2	[OUT] The distance between the ray position and the second point of
//				  intersection.
bool Sphere::Intersect( const Ray ray, float &dist1, float &dist2 )
{
	float det, b, posLenSq;
	Vec3 p = ray.origin - position;
	
	b = -p.dot( ray.direction );
	
	posLenSq = p.dot( p );
	
	det = b * b - posLenSq + radiusSq;
	
	if( det < 0.0001f )
	{
		return false;
	}
	
	det = sqrt( det );
	dist1 = b - det;
	dist2 = b + det;
	
	if( dist2 < 0.0001f )
	{
		return false;
	}
	
	if( dist1 < 0.0001f )
	{
		dist1 = 0.0f;
	}
	
	return true;
}
