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

#include "camera.h"

void Camera::Render()
{
	printf( "Render\n" );
	Vec3 vViewPoint = vPosition + vViewDir;
	
	mViewMatrix.LookAt( vPosition, vViewPoint, vUpVec.normalized() );
	
	vRightVec.print();
	vUpVec.print();
	vViewDir.print();
	vPosition.print();
}

void Camera::Move( const Vec3 dir )
{
	printf( "Move\n" );
	vPosition += dir;
	
	vRightVec.print();
	vUpVec.print();
	vViewDir.print();
	vPosition.print();
}

void Camera::RotateX( const float angle )
{
	printf( "RotateX\n" );
	fRX += angle;
	vViewDir = ( vViewDir * cos( angle * PIdiv180 ) +
				 vUpVec   * sin( angle * PIdiv180 ) );
	vViewDir.normalize();
	vUpVec = vViewDir.crossProduct( vRightVec ) * -1.0f;
	
	vRightVec.print();
	vUpVec.print();
	vViewDir.print();
	vPosition.print();
}

void Camera::RotateY( const float angle )
{
	printf( "RotateY\n" );
	fRY += angle;
	vViewDir = ( vViewDir  * cos( angle * PIdiv180 ) +
				 vRightVec * sin( angle * PIdiv180 ) );
	vViewDir.normalize();
	vRightVec = vViewDir.crossProduct( vUpVec ) * -1.0f;
	
	vRightVec.print();
	vUpVec.print();
	vViewDir.print();
	vPosition.print();
}

void Camera::RotateZ( const float angle )
{
	printf( "RotateZ\n" );
	fRZ += angle;
	vRightVec = ( vRightVec * cos( angle * PIdiv180 ) +
				  vUpVec    * sin( angle * PIdiv180 ) );
	vRightVec.normalize();
	vUpVec = vViewDir.crossProduct( vRightVec ) * -1.0f;
	
	vRightVec.print();
	vUpVec.print();
	vViewDir.print();
	vPosition.print();
}

void Camera::MoveFwd( const float dist )
{
	vPosition += ( vViewDir * dist );
}

void Camera::MoveUp( const float dist )
{
	vPosition += ( vUpVec * dist );
}

void Camera::StrafeRight( const float dist )
{
	printf( "StrafeRight\n" );
	vPosition += ( vRightVec * dist );
	
	vRightVec.print();
	vUpVec.print();
	vViewDir.print();
	vPosition.print();
}

