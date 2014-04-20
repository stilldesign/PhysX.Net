#include "StdAfx.h"

#include "Force Field Linear Kernel.h"
#include "Functions.h"
#include "Scene.h"
#include "Force Field Linear Kernel Description.h"

using namespace StillDesign::PhysX;

ForceFieldLinearKernel::ForceFieldLinearKernel( NxForceFieldLinearKernel* kernel ) : ForceFieldKernel( kernel )
{
	Debug::Assert( kernel != NULL );
	
	_scene = ObjectTable::GetObject<StillDesign::PhysX::Scene^>( (intptr_t)(&kernel->getScene()) );
}

ForceFieldLinearKernelDescription^ ForceFieldLinearKernel::SaveToDescription()
{
	ForceFieldLinearKernelDescription^ desc = gcnew ForceFieldLinearKernelDescription();
	
	this->UnmanagedPointer->saveToDesc( *desc->UnmanagedPointer );
	
	desc->UserData = this->UserData;
	
	return desc;
}

StillDesign::PhysX::Scene^ ForceFieldLinearKernel::Scene::get()
{
	return _scene;
}

String^ ForceFieldLinearKernel::Name::get()
{
	return Functions::UnmanagedToManagedString( this->UnmanagedPointer->getName() );
}
void ForceFieldLinearKernel::Name::set( String^ value )
{
	this->UnmanagedPointer->setName( Functions::ManagedToUnmanagedString( value ) );
}

Vector3 ForceFieldLinearKernel::Constant::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getConstant() );
}
void ForceFieldLinearKernel::Constant::set( Vector3 value )
{
	this->UnmanagedPointer->setConstant( Math::Vector3ToNxVec3( value ) );
}

Matrix ForceFieldLinearKernel::PositionMultiplier::get()
{
	return Math::Mat33ToMatrix( &(this->UnmanagedPointer->getPositionMultiplier()) );
}
void ForceFieldLinearKernel::PositionMultiplier::set( Matrix value )
{
	this->UnmanagedPointer->setPositionMultiplier( Math::MatrixToMat33( value ) );
}

Vector3 ForceFieldLinearKernel::PositionTarget::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getPositionTarget() );
}
void ForceFieldLinearKernel::PositionTarget::set( Vector3 value )
{
	this->UnmanagedPointer->setPositionTarget( Math::Vector3ToNxVec3( value ) );
}

Matrix ForceFieldLinearKernel::VelocityMultiplier::get()
{
	return Math::Mat33ToMatrix( &(this->UnmanagedPointer->getVelocityMultiplier()) );
}
void ForceFieldLinearKernel::VelocityMultiplier::set( Matrix value )
{
	this->UnmanagedPointer->setVelocityMultiplier( Math::MatrixToMat33( value ) );
}

Vector3 ForceFieldLinearKernel::VelocityTarget::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getVelocityTarget() );
}
void ForceFieldLinearKernel::VelocityTarget::set( Vector3 value )
{
	this->UnmanagedPointer->setVelocityTarget( Math::Vector3ToNxVec3( value ) );
}

Vector3 ForceFieldLinearKernel::FalloffLinear::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getFalloffLinear() );
}
void ForceFieldLinearKernel::FalloffLinear::set( Vector3 value )
{
	this->UnmanagedPointer->setFalloffLinear( Math::Vector3ToNxVec3( value ) );
}

Vector3 ForceFieldLinearKernel::FalloffQuadratic::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getFalloffQuadratic() );
}
void ForceFieldLinearKernel::FalloffQuadratic::set( Vector3 value )
{
	this->UnmanagedPointer->setFalloffQuadratic( Math::Vector3ToNxVec3( value ) );
}

float ForceFieldLinearKernel::TorusRadius::get()
{
	return this->UnmanagedPointer->getTorusRadius();
}
void ForceFieldLinearKernel::TorusRadius::set( float value )
{
	this->UnmanagedPointer->setTorusRadius( value );
}

Vector3 ForceFieldLinearKernel::Noise::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getNoise() );
}
void  ForceFieldLinearKernel::Noise::set( Vector3 value )
{
	this->UnmanagedPointer->setNoise( Math::Vector3ToNxVec3( value ) );
}

NxForceFieldLinearKernel* ForceFieldLinearKernel::UnmanagedPointer::get()
{
	return (NxForceFieldLinearKernel*)ForceFieldKernel::UnmanagedPointer;
}