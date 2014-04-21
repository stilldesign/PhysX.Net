#include "StdAfx.h"

#include "Segment.h"

using namespace StillDesign::PhysX;

Segment::Segment( Vector3 point0, Vector3 point1 )
{
	this->Point0 = point0;
	this->Point1 = point1;
}

float Segment::LengthSqaured()
{
	Vector3 d = this->Point0 - this->Point1;
	
	return d.LengthSquared();
}
Vector3 Segment::ComputePoint( float t )
{
	return Vector3::Lerp( this->Point0, this->Point1, t );
}

Vector3 Segment::Origin::get()
{
	return this->Point0;
}
Vector3 Segment::Direction::get()
{
	return Vector3::Normalize( this->Point1 - this->Point0 );
}
float Segment::Length::get()
{
	Vector3 d = this->Point0 - this->Point1;
	
	return d.Length();
}