#include "StdAfx.h"

#include "D6 Joint Description.h"
#include "Joint Limit Soft Description.h"
#include "Joint Limit Soft Pair Description.h"
#include "Joint Drive Description.h"
#include "D6 Joint.h"

#include <NxD6JointDesc.h> 
#include <NxQuat.h> 

using namespace StillDesign::PhysX;

D6JointDescription::D6JointDescription() : JointDescription( new NxD6JointDesc() )
{
	
}
D6JointDescription::D6JointDescription( NxD6JointDesc* desc ) : JointDescription( desc )
{
	
}

D6JointMotion D6JointDescription::XMotion::get()
{
	return (D6JointMotion)this->UnmanagedPointer->xMotion;
}
void D6JointDescription::XMotion::set( D6JointMotion value )
{
	this->UnmanagedPointer->xMotion = (NxD6JointMotion)value;
}
D6JointMotion D6JointDescription::YMotion::get()
{
	return (D6JointMotion)this->UnmanagedPointer->yMotion;
}
void D6JointDescription::YMotion::set( D6JointMotion value )
{
	this->UnmanagedPointer->yMotion = (NxD6JointMotion)value;
}
D6JointMotion D6JointDescription::ZMotion::get()
{
	return (D6JointMotion)this->UnmanagedPointer->zMotion;
}
void D6JointDescription::ZMotion::set( D6JointMotion value )
{
	this->UnmanagedPointer->zMotion = (NxD6JointMotion)value;
}

D6JointMotion D6JointDescription::Swing1Motion::get()
{
	return (D6JointMotion)this->UnmanagedPointer->swing1Motion;
}
void D6JointDescription::Swing1Motion::set( D6JointMotion value )
{
	this->UnmanagedPointer->swing1Motion = (NxD6JointMotion)value;
}
D6JointMotion D6JointDescription::Swing2Motion::get()
{
	return (D6JointMotion)this->UnmanagedPointer->swing2Motion;
}
void D6JointDescription::Swing2Motion::set( D6JointMotion value )
{
	this->UnmanagedPointer->swing2Motion = (NxD6JointMotion)value;
}
D6JointMotion D6JointDescription::TwistMotion::get()
{
	return (D6JointMotion)this->UnmanagedPointer->twistMotion;
}
void D6JointDescription::TwistMotion::set( D6JointMotion value )
{
	this->UnmanagedPointer->twistMotion = (NxD6JointMotion)value;
}

JointLimitSoftDescription D6JointDescription::LinearLimit::get()
{
	return JointLimitSoftDescription::FromUnmanaged( this->UnmanagedPointer->linearLimit );
}
void D6JointDescription::LinearLimit::set( JointLimitSoftDescription value )
{
	this->UnmanagedPointer->linearLimit = JointLimitSoftDescription::ToUnmanaged( value );
}

JointLimitSoftDescription D6JointDescription::Swing1Limit::get()
{
	return JointLimitSoftDescription::FromUnmanaged( this->UnmanagedPointer->swing1Limit );
}
void D6JointDescription::Swing1Limit::set( JointLimitSoftDescription value )
{
	this->UnmanagedPointer->swing1Limit = JointLimitSoftDescription::ToUnmanaged( value );
}

JointLimitSoftDescription D6JointDescription::Swing2Limit::get()
{
	return JointLimitSoftDescription::FromUnmanaged( this->UnmanagedPointer->swing2Limit );
}
void D6JointDescription::Swing2Limit::set( JointLimitSoftDescription value )
{
	this->UnmanagedPointer->swing2Limit = JointLimitSoftDescription::ToUnmanaged( value );
}

JointLimitSoftPairDescription D6JointDescription::TwistLimit::get()
{
	return JointLimitSoftPairDescription::FromUnmanaged( this->UnmanagedPointer->twistLimit );
}
void D6JointDescription::TwistLimit::set( JointLimitSoftPairDescription value )
{
	this->UnmanagedPointer->twistLimit = JointLimitSoftPairDescription::ToUnmanaged( value );
}

JointDriveDescription D6JointDescription::XDrive::get()
{
	return JointDriveDescription::FromUnmanaged( this->UnmanagedPointer->xDrive );
}
void D6JointDescription::XDrive::set( JointDriveDescription value )
{
	this->UnmanagedPointer->xDrive = JointDriveDescription::ToUnmanaged( value );
}
JointDriveDescription D6JointDescription::YDrive::get()
{
	return JointDriveDescription::FromUnmanaged( this->UnmanagedPointer->yDrive );
}
void D6JointDescription::YDrive::set( JointDriveDescription value )
{
	this->UnmanagedPointer->yDrive = JointDriveDescription::ToUnmanaged( value );
}
JointDriveDescription D6JointDescription::ZDrive::get()
{
	return JointDriveDescription::FromUnmanaged( this->UnmanagedPointer->zDrive );
}
void D6JointDescription::ZDrive::set( JointDriveDescription value )
{
	this->UnmanagedPointer->zDrive = JointDriveDescription::ToUnmanaged( value );
}

JointDriveDescription D6JointDescription::SwingDrive::get()
{
	return JointDriveDescription::FromUnmanaged( this->UnmanagedPointer->swingDrive );
}
void D6JointDescription::SwingDrive::set( JointDriveDescription value )
{
	this->UnmanagedPointer->swingDrive = JointDriveDescription::ToUnmanaged( value );
}

JointDriveDescription D6JointDescription::TwistDrive::get()
{
	return JointDriveDescription::FromUnmanaged( this->UnmanagedPointer->twistDrive );
}
void D6JointDescription::TwistDrive::set( JointDriveDescription value )
{
	this->UnmanagedPointer->twistDrive = JointDriveDescription::ToUnmanaged( value );
}

JointDriveDescription D6JointDescription::SLerpDrive::get()
{
	return JointDriveDescription::FromUnmanaged( this->UnmanagedPointer->slerpDrive );
}
void D6JointDescription::SLerpDrive::set( JointDriveDescription value )
{
	this->UnmanagedPointer->slerpDrive = JointDriveDescription::ToUnmanaged( value );
}

Vector3 D6JointDescription::DrivePosition::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->drivePosition );
}
void D6JointDescription::DrivePosition::set( Vector3 value )
{
	this->UnmanagedPointer->drivePosition = Math::Vector3ToNxVec3( value );
}

Quaternion D6JointDescription::DriveOrientation::get()
{
	return Math::NxQuatToQuaternion( this->UnmanagedPointer->driveOrientation );
}
void D6JointDescription::DriveOrientation::set( Quaternion value )
{
	this->UnmanagedPointer->driveOrientation = Math::QuaternionNxQuat( value );
}

Vector3 D6JointDescription::DriveLinearVelocity::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->driveLinearVelocity );
}
void D6JointDescription::DriveLinearVelocity::set( Vector3 value )
{
	this->UnmanagedPointer->driveLinearVelocity = Math::Vector3ToNxVec3( value );
}

Vector3 D6JointDescription::DriveAngularVelocity::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->driveAngularVelocity );
}
void D6JointDescription::DriveAngularVelocity::set( Vector3 value )
{
	this->UnmanagedPointer->driveAngularVelocity = Math::Vector3ToNxVec3( value );
}

JointProjectionMode D6JointDescription::ProjectionMode::get()
{
	return (JointProjectionMode)this->UnmanagedPointer->projectionMode;
}
void D6JointDescription::ProjectionMode::set( JointProjectionMode value )
{
	this->UnmanagedPointer->projectionMode = (NxJointProjectionMode)value;
}

float D6JointDescription::ProjectionDistance::get()
{
	return this->UnmanagedPointer->projectionDistance;
}
void D6JointDescription::ProjectionDistance::set( float value )
{
	this->UnmanagedPointer->projectionDistance = value;
}

float D6JointDescription::ProjectionAngle::get()
{
	return this->UnmanagedPointer->projectionAngle;
}
void D6JointDescription::ProjectionAngle::set( float value )
{
	this->UnmanagedPointer->projectionAngle = value;
}

float D6JointDescription::GearRatio::get()
{
	return this->UnmanagedPointer->gearRatio;
}
void D6JointDescription::GearRatio::set( float value )
{
	this->UnmanagedPointer->gearRatio = value;
}

D6JointFlag D6JointDescription::Flags::get()
{
	return (D6JointFlag)this->UnmanagedPointer->flags;
}
void D6JointDescription::Flags::set( D6JointFlag value )
{
	this->UnmanagedPointer->flags = (NxD6JointFlag)value;
}

NxD6JointDesc* D6JointDescription::UnmanagedPointer::get()
{
	return (NxD6JointDesc*)JointDescription::UnmanagedPointer;
}