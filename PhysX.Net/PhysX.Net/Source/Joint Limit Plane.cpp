#include "StdAfx.h"

#include "Joint Limit Plane.h"

using namespace StillDesign::PhysX;

LimitPlane::LimitPlane( Vector3 normal, Vector3 pointInPlane, float restitution )
{
	_normal = normal;
	_d = -Vector3::Dot( pointInPlane, normal );
	
	_restitution = restitution;
}
LimitPlane::LimitPlane( Plane plane, float restitution )
{
	Plane p = Plane::Normalize( plane );
	
	_normal = p.Normal;
	
	_d = p.D;
	_restitution = restitution;
}

LimitPlane::operator Plane( LimitPlane limitPlane )
{
	return Plane( limitPlane.Normal.X, limitPlane.Normal.Y, limitPlane.Normal.Z, limitPlane.Distance );
}

Vector3 LimitPlane::PointInPlane()
{
	return -this->Normal * this->Distance;
}

Vector3 LimitPlane::Normal::get()
{
	return _normal;
}
void LimitPlane::Normal::set( Vector3 value )
{
	_normal = value;
}

float LimitPlane::Distance::get()
{
	return _d;
}
void LimitPlane::Distance::set( float value )
{
	_d = value;
}

float LimitPlane::Resitution::get()
{
	return _restitution;
}
void LimitPlane::Resitution::set( float value )
{
	_restitution = value;
}