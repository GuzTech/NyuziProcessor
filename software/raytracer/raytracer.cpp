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

#include <stdio.h>
#include <stdint.h>
#include "math/ray.h"
#include "math/sphere.h"
#include "graphics/camera.h"
#include "graphics/light.h"

using namespace librender;

#define makevectorf __builtin_nyuzi_makevectorf
#define makevectori __builtin_nyuzi_makevectori
#define mask_cmpf_lt __builtin_nyuzi_mask_cmpf_lt
#define mask_cmpi_ult __builtin_nyuzi_mask_cmpi_ult
#define mask_cmpi_uge __builtin_nyuzi_mask_cmpi_uge
#define vector_mixi __builtin_nyuzi_vector_mixi

#define VS_WIDTH		8
#define VS_HEIGHT		8
#define HALF_VS_WIDTH	VS_WIDTH / 2
#define HALF_VS_HEIGHT	VS_HEIGHT / 2
#define FB_WIDTH		800
#define FB_HEIGHT		600

#define BACKGR_COLOR	Vec3( 0.2f, 0.2f, 0.2f )

const char *kFbBase = ( const char * ) 0x200000;

Camera *cam;
Light  *lights[ 2 ];
Sphere *spheres[ 2 ];

Vec3 raytrace( Ray r, int q );

#define EXP_A 184
#define EXP_C 16249

inline float exp( float y )
{
	union
	{
		float d;
		struct
		{
			short j, i;
		} n;
	} eco;
	
	eco.n.i = EXP_A * (y) + (EXP_C);
	eco.n.j = 0;
	
	return eco.d;
}

inline float log( float y )
{
	int *nTemp = (int *)&y;
	y = ( * nTemp ) >> 16;
	return ( y - EXP_C) / EXP_A;
}

inline float pow( float b, float p )
{
	return exp( log( b ) * p );
}

int main()
{
	printf( "Hello, World!\n" );
	
	float b = 100.0f;
	float p = 0.5f;
	
	float result = pow( b, p );
	printf( "result = %f\n", result );
	
	Sphere s1( Vec3( -1.0f, 0.0f, 1.0f ), 1.0f );
	Sphere s2( Vec3(  1.0f, 0.0f, 1.0f ), 1.0f );
	s1.color = Vec3( 1.0f, 0.0f, 0.0f );
	s2.color = Vec3( 0.3f, 0.7f, 1.0f );
	s1.reflectivity = 0.65f;
	s2.reflectivity = 0.0f;
	s1.specular = 0.0f;
	s2.specular = 0.0f;
	
	spheres[ 0 ] = &s1;
	spheres[ 1 ] = &s2;
	
	Light l1, l2;
	l1.position = Vec3( 0.0f, 2.0f, -1.0f );
	l2.position = Vec3( 1.0f, 0.0f, -3.0f );
	
	lights[ 0 ] = &l1;
	lights[ 1 ] = &l2;
	
	// Camera variables
	cam = new Camera();
	cam->Move( Vec3( 0.0f, 0.0f, -2.0f ) );
	cam->RotateY( 22.5f );
	cam->StrafeRight( 2.0f );
	cam->Render();
	
	const Vec3 upLeft(    -HALF_VS_WIDTH,  HALF_VS_HEIGHT, -6.298f );
	const Vec3 upRight(    HALF_VS_WIDTH,  HALF_VS_HEIGHT, -6.298f );
	const Vec3 downLeft(  -HALF_VS_WIDTH, -HALF_VS_HEIGHT, -6.298f );
	const Vec3 downRight(  HALF_VS_WIDTH, -HALF_VS_HEIGHT, -6.298f );
	
	const Vec3 UL = cam->mViewMatrix * upLeft;
	const Vec3 UR = cam->mViewMatrix * upRight;
	const Vec3 DL = cam->mViewMatrix * downLeft;
	//const Vec3 DR = cam->mViewMatrix * downRight;

	Ray r;			
	r.origin = cam->vPosition;
	
	// fire a ray for every pixel
	for( unsigned short y = 0; y < FB_HEIGHT; y++ )
	{
		const Vec3 dy = ( ( UL - DL ) / (float)FB_HEIGHT ) * y;
		
		for( unsigned short x = 0; x < FB_WIDTH; x++ )
		{
			// Point to the new pixel in the framebuffer
			uint32_t *ptr = ( uint32_t * )( kFbBase + ( y * FB_WIDTH + x ) * 4 );
						
			const Vec3 dx = ( ( UR - UL ) / (float)FB_WIDTH ) * x;
			
			// set the direction vector and normalize it
			const Vec3 dir = UL + dx - dy - r.origin;
			
			// Construct a ray
			r.direction = dir.normalized();

			// trace the ray
			Vec3 color = raytrace( r, 1 );
			
			*ptr = (uint32_t)
				(
					( (uint32_t)( color[ 2 ] * 255 ) << 16 ) +
					( (uint32_t)( color[ 1 ] * 255 ) << 8 ) +
					( (uint32_t)( color[ 0 ] * 255 ) )
				);
			
			asm( "dflush %0" : : "s" ( ptr++ ) );
		}
	}
	
	printf( "done\n" );
	
	delete cam;
	
	while( 1 )
	{}
	
    return 0;
}

Vec3 raytrace( Ray r, int q )
{
	// bail out when maxdepth has been reached
	if( q < 0 ) return BACKGR_COLOR;

	// the maximum distance between origin and the primitive
	float distance = 100000.0f;
	
	// temprorary variables to check if a primitive is within max distance and which
	// primitive should be drawn (because it's closer to the camera)
	float		tempdist 	= 0.0f;
	float		tempdist2	= 0.0f;
	bool		temphit 	= false;
	bool		hit 		= false;
	Sphere		nearest;
	Vec3	 	LightVector;
	Vec3	 	resultColor = BACKGR_COLOR;

	// check for every primitive if it intersects with the ray
	for( uint32_t i = 0; i < 2; ++i )
	{
		temphit = spheres[ i ]->Intersect( r, tempdist, tempdist2 );
		if( temphit && (tempdist < distance) )
		{
			distance = tempdist;
			hit = true;
			nearest = *spheres[ i ];
		}
	}

	// if a primitive has been hit
	if( hit )
	{
		// calculate intersection point
		Vec3 IntersectionPoint = r.origin + ( r.direction * distance );
		Vec3 Normal = ( IntersectionPoint - nearest.position ).normalized();
		
		// diffuse coefficient
		float diffuse = 0.0f;

		// calculate diffuse coefficient for every lightsource
		for( uint32_t al = 0; al < 2; ++al )
		{
			LightVector = ( lights[ al ]->position - IntersectionPoint ).normalized();
			diffuse += LightVector.dot( Normal );
			if( diffuse < 0.0f ) diffuse = 0.0f;
			if( diffuse > 1.0f ) diffuse = 1.0f;
		}

		// check if primitive is reflective
		float reflectivity = nearest.reflectivity;

		Vec3 refldir = r.direction - ( Normal * ( Normal.dot( r.direction ) * 2 ) );
		refldir.normalize();
		Ray reflray( IntersectionPoint, refldir );
		
		float specular = reflray.direction.dot( LightVector );
		if( specular > 0 )
		{
			specular = pow(specular, nearest.specular) * nearest.specular;
		}
		else specular = 0;
		
		// if it is calculate color of reflection
		if( reflectivity != 0.0f )
		{
			Vec3 reflcolor = raytrace( reflray, --q );
		
			resultColor = reflcolor * reflectivity + ( nearest.color * diffuse ) * ( 1.0f - reflectivity ) + specular;
		}
		else
		{
			resultColor = nearest.color * diffuse + specular;
		}
	}
	
	return resultColor;
}
