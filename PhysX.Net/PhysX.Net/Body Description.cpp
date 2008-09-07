#include "StdAfx.h"

#include "Actor.h"
#include "Body Description.h"

#include <NxBodyDesc.h> 

using namespace StillDesign::PhysX;

BodyDescription::BodyDescription()
{
	_desc = new NxBodyDesc();
}
BodyDescription::BodyDescription( float mass )
{
	_desc = new NxBodyDesc();
		_desc->mass = mass;
}
BodyDescription::BodyDescription( NxBodyDesc* bodyDesc )
{
	Debug::Assert( bodyDesc != NULL );
	
	_desc = bodyDesc;
}
BodyDescription::~BodyDescription()
{
	this->!BodyDescription();
}
BodyDescription::!BodyDescription()
{
	SAFE_DELETE( _desc );
}

void BodyDescription::SetToDefault()
{
	_desc->setToDefault();
}
bool BodyDescription::IsValid()
{
	return _desc->isValid();
}

Matrix BodyDescription::MassLocalPose::get()
{
	return Math::Mat34ToMatrix( &_desc->massLocalPose );
}
void BodyDescription::MassLocalPose::set( Matrix value )
{
	_desc->massLocalPose = Math::MatrixToMat34( value );
}
Vector3 BodyDescription::MassSpaceInertia::get()
{
	return Math::NxVec3ToVector3( _desc->massSpaceInertia );
}
void BodyDescription::MassSpaceInertia::set( Vector3 value )
{
	_desc->massSpaceInertia = Math::Vector3ToNxVec3( value );
}

float BodyDescription::Mass::get()
{
	return _desc->mass;
}
void BodyDescription::Mass::set( float value )
{
	_desc->mass = value;
}

Vector3 BodyDescription::LinearVelocity::get()
{
	return Math::NxVec3ToVector3( _desc->linearVelocity );
}
void BodyDescription::LinearVelocity::set( Vector3 value )
{
	_desc->linearVelocity = Math::Vector3ToNxVec3( value );
}
Vector3 BodyDescription::AngularVelocity::get()
{
	return Math::NxVec3ToVector3( _desc->angularVelocity );
}
void BodyDescription::AngularVelocity::set( Vector3 value )
{
	_desc->linearVelocity = Math::Vector3ToNxVec3( value );
}

float BodyDescription::WakeUpCounter::get()
{
	return _desc->wakeUpCounter;
}
void BodyDescription::WakeUpCounter::set( float value )
{
	_desc->wakeUpCounter = value;
}

float BodyDescription::LinearDamping::get()
{
	return _desc->linearDamping;
}
void BodyDescription::LinearDamping::set( float value )
{
	_desc->linearDamping = value;
}
float BodyDescription::AngularDamping::get()
{
	return _desc->angularDamping;
}
void BodyDescription::AngularDamping::set( float value )
{
	_desc->angularDamping = value;
}

float BodyDescription::MaxAngularVelocity::get()
{
	return _desc->maxAngularVelocity;
}
void BodyDescription::MaxAngularVelocity::set( float value )
{
	_desc->maxAngularVelocity = value;
}

float BodyDescription::CCDMotionThreshold::get()
{
	return _desc->wakeUpCounter;
}
void BodyDescription::CCDMotionThreshold::set( float value )
{
	_desc->wakeUpCounter = value;
}

BodyFlag BodyDescription::BodyFlags::get()
{
	return (BodyFlag)_desc->flags;
}
void BodyDescription::BodyFlags::set( BodyFlag value )
{
	_desc->flags = (unsigned int)value;
}

float BodyDescription::SleepLinearVelocity::get()
{
	return _desc->sleepLinearVelocity;
}
void BodyDescription::SleepLinearVelocity::set( float value )
{
	_desc->sleepLinearVelocity = value;
}

float BodyDescription::SleepAngularVelocity::get()
{
	return _desc->sleepAngularVelocity;
}
void BodyDescription::SleepAngularVelocity::set( float value )
{
	_desc->sleepAngularVelocity = value;
}

unsigned int BodyDescription::SolverIterationCount::get()
{
	return _desc->solverIterationCount;
}
void BodyDescription::SolverIterationCount::set( unsigned int value )
{
	_desc->solverIterationCount = value;
}

float BodyDescription::SleepEnergyThreshold::get()
{
	return _desc->sleepEnergyThreshold;
}
void BodyDescription::SleepEnergyThreshold::set( float value )
{
	_desc->sleepEnergyThreshold = value;
}

float BodyDescription::SleepDamping::get()
{
	return _desc->sleepDamping;
}
void BodyDescription::SleepDamping::set( float value )
{
	_desc->sleepDamping = value;
}

float BodyDescription::ContactReportThreshold::get()
{
	return _desc->contactReportThreshold;
}
void BodyDescription::ContactReportThreshold::set( float value )
{
	_desc->contactReportThreshold = value;
}

NxBodyDesc* BodyDescription::UnmanagedPointer::get()
{
	return _desc;
}