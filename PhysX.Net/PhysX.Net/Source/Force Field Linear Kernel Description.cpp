#include "StdAfx.h"

#include "Force Field Linear Kernel Description.h"
#include "Functions.h"

using namespace StillDesign::PhysX;

ForceFieldLinearKernelDescription::ForceFieldLinearKernelDescription()
{
	_desc = new NxForceFieldLinearKernelDesc();
}
ForceFieldLinearKernelDescription::~ForceFieldLinearKernelDescription()
{
	this->!ForceFieldLinearKernelDescription();
}
ForceFieldLinearKernelDescription::!ForceFieldLinearKernelDescription()
{
	SAFE_DELETE( _desc );
	
	_userData = nullptr;
}

void ForceFieldLinearKernelDescription::SetToDefault()
{
	_desc->setToDefault();
	
	_userData = nullptr;
}
int ForceFieldLinearKernelDescription::CheckValid()
{
	return _desc->checkValid();
}
bool ForceFieldLinearKernelDescription::IsValid()
{
	return _desc->isValid();
}

String^ ForceFieldLinearKernelDescription::Name::get()
{
	return Functions::UnmanagedToManagedString( _desc->name );
}
void ForceFieldLinearKernelDescription::Name::set( String^ value )
{
	_desc->name = Functions::ManagedToUnmanagedString( value );
}

Vector3 ForceFieldLinearKernelDescription::Constant::get()
{
	return Math::NxVec3ToVector3( _desc->constant );
}
void ForceFieldLinearKernelDescription::Constant::set( Vector3 value )
{
	_desc->constant = Math::Vector3ToNxVec3( value );
}
Matrix ForceFieldLinearKernelDescription::PositionMultiplier::get()
{
	return Math::Mat33ToMatrix( &_desc->positionMultiplier );
}
void ForceFieldLinearKernelDescription::PositionMultiplier::set( Matrix value )
{
	_desc->positionMultiplier = Math::MatrixToMat33( value );
}
Vector3 ForceFieldLinearKernelDescription::PositionTarget::get()
{
	return Math::NxVec3ToVector3( _desc->positionTarget );
}
void ForceFieldLinearKernelDescription::PositionTarget::set( Vector3 value )
{
	_desc->positionTarget = Math::Vector3ToNxVec3( value );
}
Matrix ForceFieldLinearKernelDescription::VelocityMultiplier::get()
{
	return Math::Mat33ToMatrix( &_desc->velocityMultiplier );
}
void ForceFieldLinearKernelDescription::VelocityMultiplier::set( Matrix value )
{
	_desc->velocityMultiplier = Math::MatrixToMat33( value );
}
Vector3 ForceFieldLinearKernelDescription::VelocityTarget::get()
{
	return Math::NxVec3ToVector3( _desc->velocityTarget );
}
void ForceFieldLinearKernelDescription::VelocityTarget::set( Vector3 value )
{
	_desc->velocityTarget = Math::Vector3ToNxVec3( value );
}
Vector3 ForceFieldLinearKernelDescription::FalloffLinear::get()
{
	return Math::NxVec3ToVector3( _desc->falloffLinear );
}
void ForceFieldLinearKernelDescription::FalloffLinear::set( Vector3 value )
{
	_desc->falloffLinear = Math::Vector3ToNxVec3( value );
}
Vector3 ForceFieldLinearKernelDescription::FalloffQuadratic::get()
{
	return Math::NxVec3ToVector3( _desc->falloffQuadratic );
}
void ForceFieldLinearKernelDescription::FalloffQuadratic::set( Vector3 value )
{
	_desc->falloffQuadratic = Math::Vector3ToNxVec3( value );
}
float ForceFieldLinearKernelDescription::TorusRadius::get()
{
	return _desc->torusRadius;
}
void ForceFieldLinearKernelDescription::TorusRadius::set( float value )
{
	_desc->torusRadius = value;
}
Vector3 ForceFieldLinearKernelDescription::Noise::get()
{
	return Math::NxVec3ToVector3( _desc->noise );
}
void ForceFieldLinearKernelDescription::Noise::set( Vector3 value )
{
	_desc->noise = Math::Vector3ToNxVec3( value );
}

Object^ ForceFieldLinearKernelDescription::UserData::get()
{
	return _userData;
}
void ForceFieldLinearKernelDescription::UserData::set( Object^ value )
{
	_userData = value;
}

NxForceFieldLinearKernelDesc* ForceFieldLinearKernelDescription::UnmanagedPointer::get()
{
	return _desc;
}