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

#include <math.h>
#include "vec_math.h"

#define makevectorf __builtin_nyuzi_makevectorf

const vecf16_t vecTwoRecp = makevectorf( 0.5f );

vecf16_t sqrtf_16( const float value )
{
	vecf16_t values = makevectorf( value );
	
	return sqrtf_16( values );
}

vecf16_t sqrtf_16( const vecf16_t value )
{
	vecf16_t guess = value;
		
	for( int iteration = 0; iteration < 10; iteration++ )
	{
		guess = ( ( value / guess ) + guess ) * vecTwoRecp;// / 2.0f;
	}

	return guess;
}
