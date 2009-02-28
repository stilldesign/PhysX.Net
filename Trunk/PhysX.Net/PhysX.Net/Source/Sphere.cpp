#include "StdAfx.h"

#include "Sphere.h"

using namespace StillDesign::PhysX;

Sphere::Sphere( float radius )
{
	this->Radius = radius;
}
Sphere::Sphere( float radius, Vector3 center )
{
	this->Radius = radius;
	this->Center = center;
}

Sphere::operator NxSphere( Sphere sphere )
{
	return NxSphere( Math::Vector3ToNxVec3( sphere.Center ), sphere.Radius );
}
Sphere::operator Sphere( NxSphere sphere )
{
	return Sphere( sphere.radius, Math::NxVec3ToVector3( sphere.center ) );
}

bool Sphere::IsValid()
{
	return this->Radius > 0;
}
bool Sphere::Contains( Vector3 point )
{
	return Vector3_LengthSquared( ( this->Center - point ) ) <= this->Radius*this->Radius;
}
bool Sphere::Contains( Sphere sphere )
{
	// If our radius is the smallest, we can't possibly contain the other sphere
	if( this->Radius < sphere.Radius )
		return false;
	
	// So r is always positive or null now
	float r = this->Radius - sphere.Radius;
	
	return Vector3_LengthSquared( ( this->Center - sphere.Center ) ) < r*r;
}

bool Sphere::Intersects( Sphere sphere )
{
	float r = this->Radius + sphere.Radius;
	
	return Vector3_LengthSquared( ( this->Center - sphere.Center ) ) < r*r;
}