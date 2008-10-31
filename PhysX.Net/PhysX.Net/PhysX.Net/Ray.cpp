#include "StdAfx.h"

#include "Ray.h"
#include "Math.h"

#include <NxRay.h>

UsingFrameworkNamespace
using namespace StillDesign::PhysX;

// Ray
StillDesign::PhysX::Ray::Ray( Vector3 origin, Vector3 direction )
{
	_origin = origin;
	_direction = direction;
}

StillDesign::PhysX::Ray::operator NxRay( Ray ray )
{
	return NxRay( Math::Vector3ToNxVec3( ray.Origin ), Math::Vector3ToNxVec3( ray.Direction ) );
}
StillDesign::PhysX::Ray::operator StillDesign::PhysX::Ray( NxRay ray )
{
	return Ray( Math::NxVec3ToVector3( ray.orig ), Math::NxVec3ToVector3( ray.dir ) );
}

// Properties
Vector3 StillDesign::PhysX::Ray::Origin::get()
{
	return _origin;
}
void StillDesign::PhysX::Ray::Origin::set( Vector3 value )
{
	_origin = value;
}

Vector3 StillDesign::PhysX::Ray::Direction::get()
{
	return _direction;
}
void StillDesign::PhysX::Ray::Direction::set( Vector3 value )
{
	_direction = value;
}

//

RaycastResult::RaycastResult( bool hit, Vector3 hitPosition )
{
	_hit = hit;
	_hitPosition = hitPosition;
}

bool RaycastResult::Hit::get()
{
	return _hit;
}
Vector3 RaycastResult::HitPosition::get()
{
	return _hitPosition;
}