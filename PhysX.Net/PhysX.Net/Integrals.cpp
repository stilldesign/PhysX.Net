#include "StdAfx.h"

#include "Integrals.h"

#include <NxVolumeIntegration.h> 

using namespace StillDesign::PhysX;

Integrals::operator NxIntegrals( Integrals integral )
{
	NxIntegrals i;
		i.COM = Math::Vector3ToNxVec3( integral.CenterOfMass );
		
		{
			Matrix m = integral.CenterOfMassInertiaTensor;
			NxF64 n[3][3] = 
				{
					{ m.M11, m.M12, m.M13 },
					{ m.M21, m.M22, m.M23 },
					{ m.M31, m.M32, m.M33 }
				};
			memcpy( &i.COMInertiaTensor, &n, sizeof( n ) );
		}
		
		{
			Matrix m = integral.inertiaTensor;
			NxF64 n[3][3] = 
				{
					{ m.M11, m.M12, m.M13 },
					{ m.M21, m.M22, m.M23 },
					{ m.M31, m.M32, m.M33 }
				};
			memcpy( &i.inertiaTensor, &n, sizeof( n ) );
		}
		
		i.mass = integral.Mass;
	
	return i;
}
Integrals::operator Integrals( NxIntegrals integral )
{
	Integrals i;
		i.CenterOfMass = Math::NxVec3ToVector3( integral.COM );
		
		{
			NxF64 m[3][3];
			memcpy( &m, &integral.COMInertiaTensor, sizeof( m ) );
			Matrix n;
				n.M11 = (float)m[ 0 ][ 0 ];
				n.M12 = (float)m[ 0 ][ 1 ];
				n.M13 = (float)m[ 0 ][ 2 ];
				
				n.M21 = (float)m[ 1 ][ 0 ];
				n.M22 = (float)m[ 1 ][ 1 ];
				n.M23 = (float)m[ 1 ][ 2 ];
				
				n.M31 = (float)m[ 2 ][ 0 ];
				n.M32 = (float)m[ 2 ][ 1 ];
				n.M33 = (float)m[ 2 ][ 2 ];
			
			i.CenterOfMassInertiaTensor = n;
		}
		
		{
			NxF64 m[3][3];
			memcpy( &m, &integral.COMInertiaTensor, sizeof( m ) );
			Matrix n;
				n.M11 = (float)m[ 0 ][ 0 ];
				n.M12 = (float)m[ 0 ][ 1 ];
				n.M13 = (float)m[ 0 ][ 2 ];
				
				n.M21 = (float)m[ 1 ][ 0 ];
				n.M22 = (float)m[ 1 ][ 1 ];
				n.M23 = (float)m[ 1 ][ 2 ];
				
				n.M31 = (float)m[ 2 ][ 0 ];
				n.M32 = (float)m[ 2 ][ 1 ];
				n.M33 = (float)m[ 2 ][ 2 ];
			
			i.inertiaTensor = n;
		}
		
		i.Mass = (float)integral.mass;
	
	return i;
}

Vector3 Integrals::CenterOfMass::get()
{
	return _centerOfMass;
}
void Integrals::CenterOfMass::set( Vector3 value )
{
	_centerOfMass = value;
}

float Integrals::Mass::get()
{
	return _mass;
}
void Integrals::Mass::set( float value )
{
	_mass = value;
}

Matrix Integrals::InertiaTensor::get()
{
	return inertiaTensor;
}
void Integrals::InertiaTensor::set( Matrix value )
{
	inertiaTensor = value;
}

Matrix Integrals::CenterOfMassInertiaTensor::get()
{
	return _centerOfMassInertiaTensor;
}
void Integrals::CenterOfMassInertiaTensor::set( Matrix value )
{
	_centerOfMassInertiaTensor = value;
}