// 
// Copyright 2015 Oguz Meteer
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 

#ifndef VEC3_16_H
#define VEC3_16_H

#include <math.h>
#include <Vec3.h>
#include "vec_math.h"

#define makevectorf __builtin_nyuzi_makevectorf

using namespace librender;

class Vec3_16
{
public:
	Vec3_16( void )
	{
		x = makevectorf( 0.0f );
		y = makevectorf( 0.0f );
		z = makevectorf( 0.0f );
	}
	
	Vec3_16( const float a, const float b, const float c )
	{
		x = makevectorf( a );
		y = makevectorf( b );
		z = makevectorf( c );
	}
	
	Vec3_16( const Vec3 value )
	{
		x = makevectorf( value[ 0 ] );
		y = makevectorf( value[ 1 ] );
		z = makevectorf( value[ 2 ] );
	}
	
	Vec3_16( const vecf16_t value1,
			 const vecf16_t value2,
			 const vecf16_t value3 )
	{
		x = value1;
		y = value2;
		z = value3;
	}
	
	Vec3_16 operator + ( const Vec3_16 &other ) const
	{
		Vec3_16 result;
		
		result = *this + other;
		
		return result;
	}
	
	Vec3_16 operator + ( const float other ) const
	{
		Vec3_16 result;
		
		result.x = x + makevectorf( other );
		result.y = y + makevectorf( other );
		result.z = z + makevectorf( other );
		
		return result;
	}
	
	void operator += ( const Vec3_16 &other )
	{
		*this += other;
	}
	
	void operator += ( const float other )
	{
		x = x + makevectorf( other );
		y = y + makevectorf( other );
		z = z + makevectorf( other );
	}

	Vec3_16 operator - ( const Vec3_16 &other ) const
	{
		Vec3_16 result;
		
		result.x = x - other.x;
		result.y = y - other.y;
		result.z = z - other.z;
		
		return result;
	}
	
	Vec3_16 operator - ( const float other ) const
	{
		Vec3_16 result;
		
		result.x = x - makevectorf( other );
		result.y = y - makevectorf( other );
		result.z = z - makevectorf( other );
		
		return result;
	}
	
	void operator -= ( const Vec3_16 &other )
	{
		x = x - other.x;
		y = y - other.y;
		z = z - other.z;
	}
	
	void operator -= ( const float other )
	{
		x = x - makevectorf( other );
		y = y - makevectorf( other );
		z = z - makevectorf( other );
	}
	
	Vec3_16 operator * ( const float other ) const
	{
		Vec3_16 result;
		
		result.x = x * makevectorf( other );
		result.y = y * makevectorf( other );
		result.z = z * makevectorf( other );
		
		return result;
	}
	
	Vec3_16 operator * ( const vecf16_t other ) const
	{
		Vec3_16 result;
		
		result.x = x * other;
		result.y = y * other;
		result.z = z * other;
		
		return result;
	}
	
	void operator *= ( const float other )
	{
		x = x * makevectorf( other );
		y = y * makevectorf( other );
		z = z * makevectorf( other );
	}

	Vec3_16 operator / ( float other ) const
	{
		Vec3_16 result;
		
		vecf16_t denom = makevectorf( 1.0f ) / makevectorf( other );
		
		result.x = x * denom;
		result.y = y * denom;
		result.z = z * denom;

		return result;
	}
	
	void operator /= ( const float other )
	{
		x = x / makevectorf( other );
		y = y / makevectorf( other );
		z = z / makevectorf( other );
	}

	vecf16_t magnitude() const
	{
		vecf16_t magSquared = makevectorf( 0.0 );
		
		magSquared = magSquared + ( x * x );
		magSquared = magSquared + ( y * y );
		magSquared = magSquared + ( z * z );
				
		return sqrtf_16( magSquared );
	}

	Vec3_16 normalized() const
	{
		Vec3_16 result;
		vecf16_t mag_reciprocal = makevectorf( 1.0f ) / magnitude();
		
		result.x = x * mag_reciprocal;
		result.y = y * mag_reciprocal;
		result.z = z * mag_reciprocal;
		
		return result;
	}
	
	void normalize()
	{
		vecf16_t mag_reciprocal = makevectorf( 1.0f ) / magnitude();
		
		x = x * mag_reciprocal;
		y = y * mag_reciprocal;
		z = z * mag_reciprocal;
	}
	
	Vec3 operator [] ( uint8_t index ) const
	{
		return Vec3( x[ index ], y[ index ], z[ index ] );
	}
	
	Vec3_16 crossProduct( const Vec3_16 &other ) const
	{
		Vec3_16 result;
		
		result.x = ( y * other.z ) - ( z * other.y );
		result.y = ( z * other.x ) - ( x * other.z );
		result.z = ( x * other.y ) - ( y * other.x );
		
		return result;
	}

	Vec3_16 operator - () const
	{
		const vecf16_t zero = makevectorf( 0.0f );
		
		return Vec3_16( zero - x, zero - y, zero - z );
	}

	void print() const
	{
		for( uint8_t i = 0; i < 16; ++i )
		{
			printf( "%f %f %f\n", x[ i ], y[ i ], z[ i ] );
		}
	}
	
	vecf16_t dot( const Vec3_16 vec ) const
	{
		return ( x * vec.x ) + ( y * vec.y ) + ( z * vec.z );
	}

private:
	vecf16_t x, y, z;
};

#endif // VEC3_16_H
