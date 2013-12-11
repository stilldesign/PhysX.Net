#include "StdAfx.h"
#include "RigidDynamic.h"
#include "SolverIterationCounts.h"
#include "Physics.h"
#include "Scene.h"
//#include <PxSimpleFactory.h>

RigidDynamic::RigidDynamic(PxRigidDynamic* rigidDynamic, PhysX::IDisposable^ owner)
	: RigidBody(rigidDynamic, owner)
{
	
}

Nullable<Matrix> RigidDynamic::GetKinematicTarget()
{
	PxTransform t;

	if(!this->UnmanagedPointer->getKinematicTarget(t))
		return Nullable<Matrix>();

	return MathUtil::PxTransformToMatrix(&t);
}
void RigidDynamic::SetKinematicTarget(Matrix destination)
{
	this->UnmanagedPointer->setKinematicTarget(MathUtil::MatrixToPxTransform(destination));
}

void RigidDynamic::WakeUp()
{
	this->UnmanagedPointer->wakeUp();
}

void RigidDynamic::PutToSleep()
{
	this->UnmanagedPointer->putToSleep();
}

RigidDynamic^ RigidDynamic::CloneDynamic(Matrix transform)
{
	PxRigidDynamic* rigidDynamic = PxCloneDynamic(
		*this->Scene->Physics->UnmanagedPointer, 
		MathUtil::MatrixToPxTransform(transform),
		*this->UnmanagedPointer);

	return gcnew RigidDynamic(rigidDynamic, this->Physics);
}

//

float RigidDynamic::LinearDamping::get()
{
	return this->UnmanagedPointer->getLinearDamping();
}
void RigidDynamic::LinearDamping::set(float value)
{
	this->UnmanagedPointer->setLinearDamping(value);
}

float RigidDynamic::AngularDamping::get()
{
	return this->UnmanagedPointer->getAngularDamping();
}
void RigidDynamic::AngularDamping::set(float value)
{
	this->UnmanagedPointer->setAngularDamping(value);
}

float RigidDynamic::MaxAngularVelocity::get()
{
	return this->UnmanagedPointer->getMaxAngularVelocity();
}
void RigidDynamic::MaxAngularVelocity::set(float value)
{
	this->UnmanagedPointer->setMaxAngularVelocity(value);
}

float RigidDynamic::SleepThreshold::get()
{
	return this->UnmanagedPointer->getSleepThreshold();
}
void RigidDynamic::SleepThreshold::set(float value)
{
	this->UnmanagedPointer->setSleepThreshold(value);
}

PhysX::SolverIterationCounts RigidDynamic::SolverIterationCounts::get()
{
	PxU32 p, v;
	this->UnmanagedPointer->getSolverIterationCounts(p, v);

	PhysX::SolverIterationCounts counts(p, v);

	return counts;
}
void RigidDynamic::SolverIterationCounts::set(PhysX::SolverIterationCounts value)
{
	this->UnmanagedPointer->setSolverIterationCounts(value.MinimumPositionIterations, value.MinimumVelocityIterations);
}

RigidDynamicFlags RigidDynamic::Flags::get()
{
	return ToManagedEnum(RigidDynamicFlags, this->UnmanagedPointer->getRigidDynamicFlags());
}
void RigidDynamic::Flags::set(RigidDynamicFlags value)
{
	this->UnmanagedPointer->setRigidDynamicFlags(ToUnmanagedEnum2(PxRigidDynamicFlags, value));
}

PxRigidDynamic* RigidDynamic::UnmanagedPointer::get()
{
	return (PxRigidDynamic*)RigidBody::UnmanagedPointer;
}