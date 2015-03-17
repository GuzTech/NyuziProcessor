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

#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include "Vec3.h"
#include "Matrix.h"

using namespace librender;

#define PI			3.1415926535f
#define PIdiv180	0.01745329251994329576923690768489f

class Camera
{
public:
			Camera()
			:	vPosition( 0.0f, 0.0f, 0.0f ),
				vViewDir( 0.0f, 0.0f, 1.0f ),
				vUpVec( 0.0f, 1.0f, 0.0f ),
				vRightVec( 1.0f, 0.0f, 0.0f ),
				fRX( 0.0f ),
				fRY( 0.0f ), 
				fRZ( 0.0f )
			{}
	
	void	Render();
	void	Move( const Vec3 dir );
	void	RotateX( const float angle );
	void	RotateY( const float angle );
	void	RotateZ( const float angle );
	void	MoveFwd( const float dist );
	void	MoveUp( const float dist );
	void	StrafeRight( const float dist );

	Matrix	mViewMatrix;
	Vec3	vPosition;
	Vec3	vViewDir;
	Vec3	vUpVec;
	Vec3	vRightVec;
	float	fRX, fRY, fRZ;
};

#endif

