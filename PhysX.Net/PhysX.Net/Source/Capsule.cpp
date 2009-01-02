#include "StdAfx.h"

#include "Capsule.h"
#include "Segment.h"

#include <NxCapsule.h> 

using namespace StillDesign::PhysX;

Capsule::Capsule( Segment segment, float radius )
{
	this->Point0 = segment.Point0;
	this->Point1 = segment.Point1;
	
	this->Radius = radius;
}
Capsule::Capsule( Vector3 p0, Vector3 p1, float radius )
{
	this->Point0 = p0;
	this->Point1 = p1;
	
	this->Radius = radius;
}

Capsule::operator Capsule( NxCapsule capsule )
{
	Capsule c;
		c.Radius = capsule.radius;
		c.Point0 = Math::NxVec3ToVector3( capsule.p0 );
		c.Point1 = Math::NxVec3ToVector3( capsule.p1 );
	
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