#include "StdAfx.h"

#include "Capsule Controller.h"
#include "Capsule Controller Description.h"

#include <NxCapsuleController.h>

using namespace StillDesign::PhysX;

CapsuleControllerDescription::CapsuleControllerDescription( float radius, float height ) : ControllerDescription( new NxCapsuleControllerDesc() )
{
	this->Radius = radius;
	this->Height = height;
}
CapsuleControllerDescription::~CapsuleControllerDescription()
{
	this->!CapsuleControllerDescription();
}
CapsuleControllerDescription::!CapsuleControllerDescription()
{
	if( this->UnmanagedPointer != NULL )
	{
		delete this->UnmanagedPointer;
	}
}

float CapsuleControllerDescription::Radius::get()
{
	return this->UnmanagedPointer->radius;
}
void CapsuleControllerDescription::Radius::set( float value )
{
	this->UnmanagedPointer->radius = value;
}

float CapsuleControllerDescription::Height::get()
{
	return this->UnmanagedPointer->height;
}
void CapsuleControllerDescription::Height::set( float value )
{
	this->UnmanagedPointer->height = value;
}

CapsuleClimbingMode CapsuleControllerDescription::ClimbingMode::get()
{
	return (CapsuleClimbingMode)this->UnmanagedPointer->climbingMode;
}
void CapsuleControllerDescription::ClimbingMode::set( CapsuleClimbingMode value )
{
	this->UnmanagedPointer->climbingMode = (NxCapsuleClimbingMode)value;
}

NxCapsuleControllerDesc* CapsuleControllerDescription::UnmanagedPointer::get()
{
	return (NxCapsuleControllerDesc*)ControllerDescription::UnmanagedPointer;
}