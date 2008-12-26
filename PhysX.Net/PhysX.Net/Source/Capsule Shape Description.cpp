#include "StdAfx.h"

#include "Capsule Shape Description.h"
#include "Scene.h"
#include "Capsule Shape.h"
#include "Actor.h"

using namespace StillDesign::PhysX;

CapsuleShapeDescription::CapsuleShapeDescription() : ShapeDescription( new NxCapsuleShapeDesc() )
{
	
}
CapsuleShapeDescription::CapsuleShapeDescription( float radius, float height ) : ShapeDescription( new NxCapsuleShapeDesc() )
{
	this->Radius = radius;
	this->Height = height;
}

float CapsuleShapeDescription::Radius::get()
{
	return this->UnmanagedPointer->radius;
}
void CapsuleShapeDescription::Radius::set( float value )
{
	this->UnmanagedPointer->radius = value;
}
float CapsuleShapeDescription::Height::get()
{
	return this->UnmanagedPointer->height;
}
void CapsuleShapeDescription::Height::set( float value )
{
	this->UnmanagedPointer->height = value;
}
CapsuleShapeFlag CapsuleShapeDescription::Flags::get()
{
	return (CapsuleShapeFlag)this->UnmanagedPointer->flags;
}
void CapsuleShapeDescription::Flags::set( CapsuleShapeFlag value )
{
	this->UnmanagedPointer->flags = (NxCapsuleShapeFlag)value;
}

NxCapsuleShapeDesc* CapsuleShapeDescription::UnmanagedPointer::get()
{
	return (NxCapsuleShapeDesc*)ShapeDescription::UnmanagedPointer;
}