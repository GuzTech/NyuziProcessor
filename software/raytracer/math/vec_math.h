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

#ifndef VEC_MATH_H
#define VEC_MATH_H

#include <stdint.h>

#define PI 3.1415926535

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

__attribute__((overloadable)) vecf16_t sqrtf_16( const float value );
__attribute__((overloadable)) vecf16_t sqrtf_16( const vecf16_t value );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // VEC_MATH_H
