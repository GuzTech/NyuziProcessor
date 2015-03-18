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

#ifndef COLOR16_H
#define COLOR16_H

class Color16
{
public:
	Color16()
	:	color( vecu16_t() )
	{}
	
	Color16( const float value )
	{
		const uint32_t uValue = (uint32_t)( value * 255 );
		
		for( uint32_t i = 0; i < 16; ++i )
		{
			color[ i ] =
				(uint32_t)( uValue << 16 ) +
				(uint32_t)( uValue << 8 ) +
				(uint32_t)( uValue );
		}
	}
	
	Color16( const vecf16_t value )
	{
		for( uint32_t i = 0; i < 16; ++i )
		{
			const uint32_t uValue = (uint32_t)( value[ i ] * 255 );
			
			color[ i ] =
				(uint32_t)( uValue << 16 ) +
				(uint32_t)( uValue << 8 ) +
				(uint32_t)( uValue );
		}
	}

	Color16( const Vec3 value )
	{
		const uint32_t uValue0 = (uint32_t)( value[ 0 ] * 255 );
		const uint32_t uValue1 = (uint32_t)( value[ 1 ] * 255 );
		const uint32_t uValue2 = (uint32_t)( value[ 2 ] * 255 );
		
		for( uint32_t i = 0; i < 16; ++i )
		{
			color[ i ] =
				(uint32_t)( uValue2 << 16 ) +
				(uint32_t)( uValue1 << 8 ) +
				(uint32_t)( uValue0 );
		}
	}
	
	Color16( const Vec3_16 value )
	{
		for( uint32_t i = 0; i < 16; ++i )
		{
			color[ i ] =
				(uint32_t)( (uint32_t)( value[ i ][ 2 ] * 255 ) << 16 ) +
				(uint32_t)( (uint32_t)( value[ i ][ 1 ] * 255 ) << 8 ) +
				(uint32_t)( (uint32_t)( value[ i ][ 0 ] * 255 ) );
		}
	}
	
	static vecu16_t ToColor( const Vec3_16 value )
	{
		vecu16_t result;
		
		for( uint32_t i = 0; i < 16; ++i )
		{
			result[ i ] =
				(uint32_t)( (uint32_t)( value[ i ][ 2 ] * 255 ) << 16 ) +
				(uint32_t)( (uint32_t)( value[ i ][ 1 ] * 255 ) << 8 ) +
				(uint32_t)( (uint32_t)( value[ i ][ 0 ] * 255 ) );
		}
		
		return result;
	}
	
	vecu16_t	color;
};

#endif // COLOR16_H
