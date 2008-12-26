#include "StdAfx.h"

#include "Plane Shape Description.h"
#include "Plane Shape.h"
#include "Actor.h"

PlaneShapeDescription::PlaneShapeDescription() : ShapeDescription( new NxPlaneShapeDesc() )
{
	
}
PlaneShapeDescription::PlaneShapeDescription( Plane plane ) : ShapeDescription( new NxPlaneShapeDesc() )
{
#if GRAPHICS_XNA2
	this->Normal = plane.Normal;
#elif GRAPHICS_MDX
	this->Normal = Vector3( plane.A, plane.B, plane.C );
#endif
	
	this->Distance = plane.D;
}
PlaneShapeDescription::PlaneShapeDescription( Vector3 normal, float distance ) : ShapeDescription( new NxPlaneShapeDesc() )
{
	this->Normal = Vector3::Normalize( normal );
	this->Distance = distance;
}
PlaneShapeDescription::PlaneShapeDescription( float normalX, float normalY, float normalZ, float distance ) : ShapeDescription( new NxPlaneShapeDesc() )
{
	this->Normal = Vector3::Normalize( Vector3( normalX, normalY, normalZ ) );
	this->Distance = distance;
}

Vector3 PlaneShapeDescription::Normal::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->normal );
}
void PlaneShapeDescription::Normal::set( Vector3 value )
{
	this->UnmanagedPointer->normal = Math::Vector3ToNxVec3( value );
}
float PlaneShapeDescription::Distance::get()
{
	return this->UnmanagedPointer->d;
}
void PlaneShapeDescription::Distance::set( float value )
{
	this->UnmanagedPointer->d = value;
}

NxPlaneShapeDesc* PlaneShapeDescription::UnmanagedPointer::get()
{
	return (NxPlaneShapeDesc*)ShapeDescription::UnmanagedPointer;
}