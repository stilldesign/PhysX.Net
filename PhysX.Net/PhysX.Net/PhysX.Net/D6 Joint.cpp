#include "StdAfx.h"

#include "D6 Joint.h"
#include "Scene.h"
#include "D6 Joint Description.h"

#include <NxD6Joint.h> 
#include <NxQuat.h> 

using namespace StillDesign::PhysX;

D6Joint::D6Joint( NxD6Joint* d6Joint ) : Joint( d6Joint )
{
	
}

void D6Joint::LoadFromDescription( D6JointDescription^ description )
{
	ThrowIfDescriptionIsNullOrInvalid( description, "description" );
	
	this->UnmanagedPointer->loadFromDesc( *description->UnmanagedPointer );
	
	Joint::LoadFromDescription( description );
}
D6JointDescription^ D6Joint::SaveToDescription()
{
	D6JointDescription^ desc = gcnew D6JointDescription();
	
	this->UnmanagedPointer->saveToDesc( *desc->UnmanagedPointer );
	
	Joint::SaveToDescription( desc );
	
	return desc;
}

void D6Joint::SetDrivePosition( Vector3 value )
{
	this->UnmanagedPointer->setDrivePosition( Math::Vector3ToNxVec3( value ) );
}
void D6Joint::SetDriveOrientation( Quaternion value )
{
	this->UnmanagedPointer->setDriveOrientation( Math::QuaternionNxQuat( value ) );
}
void D6Joint::SetDriveLinearVelocity( Vector3 value )
{
	this->UnmanagedPointer->setDriveLinearVelocity( Math::Vector3ToNxVec3( value ) );
}
void D6Joint::SetDriveAngularVelocity( Vector3 value )
{
	this->UnmanagedPointer->setDriveAngularVelocity( Math::Vector3ToNxVec3( value ) );
}

NxD6Joint* D6Joint::UnmanagedPointer::get()
{
	return (NxD6Joint*)Joint::UnmanagedPointer;
}