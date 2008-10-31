#include "StdAfx.h"

#include "Capsule.h"
#include "Segment.h"

#include <NxCapsule.h> 

using namespace StillDesign::PhysX;

Capsule::Capsule( Segment segment, float radius )
{
	_radius = radius;
	
	_p0 = segment.Point0;
	_p1 = segment.Point1;
}

Capsule::operator Capsule( NxCapsule capsule )
{
	Capsule c;
		c._radius = capsule.radius;
		c._p0 = Math::NxVec3ToVector3( capsule.p0 );
		c._p1 = Math::NxVec3ToVector3( capsule.p1 );
	
	return c;
}
Capsule::operator NxCapsule( Capsule capsule )
{
	NxCapsule c;
		c.radius = capsule.Radius;
		c.p0 = Math::Vector3ToNxVec3( capsule.Point0 );
		c.p1 = Math::Vector3ToNxVec3( capsule.Point1 );
	
	return c;
}
Capsule::operator Segment( Capsule capsule )
{
	Segment segment;
		segment.Point0 = capsule.Point0;
		segment.Point1 = capsule.Point1;
	
	return segment;
}

float Capsule::Radius::get()
{
	return _radius;
}
void Capsule::Radius::set( float value )
{
	_radius = value;
}

Vector3 Capsule::Point0::get()
{
	return _p0;
}
void Capsule::Point0::set( Vector3 value )
{
	_p0 = value;
}

Vector3 Capsule::Point1::get()
{
	return _p1;
}
void Capsule::Point1::set( Vector3 value )
{
	_p1 = value;
}