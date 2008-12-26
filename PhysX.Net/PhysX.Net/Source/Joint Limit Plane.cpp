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
	
#if GRAPHICS_MDX
	_normal = Vector3( p.A, p.B, p.C );
#elif GRAPHICS_XNA2
	_normal = plane.Normal;
#elif GRAPHICS_XNA3
	_normal = plane.Normal;
#elif GRAPHICS_SLIMDX
	_normal = plane.Normal;
#else
	#error No Graphics Target Specified
#endif
	
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