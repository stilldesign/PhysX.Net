#include "StdAfx.h"
#include "RigidDynamic.h"
#include "SolverIterationCounts.h"
#include "Physics.h"
#include "Scene.h"
#include "ActorEnum.h"

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
	if (this->Physics == nullptr)
		throw gcnew InvalidOperationException("Cannot clone a RigidDynamic if it has not been added to a scene. Try CloneDynamic(Matrix4x4, Physics) overload.");

	// We must have been added to a scene because to clone a Rigid Dyanmic we need to get the current Physics instance it belongs to
	// the only way to access this is through getScene().
	return CloneDynamic(transform, this->Physics);
}
RigidDynamic^ RigidDynamic::CloneDynamic(Matrix transform, PhysX::Physics^ physics)
{
	ThrowIfNullOrDisposed(physics, "physics");

	PxRigidDynamic* rigidDynamic = PxCloneDynamic(
		*physics->UnmanagedPointer,
		MathUtil::MatrixToPxTransform(transform),
		*this->UnmanagedPointer);

	return gcnew RigidDynamic(rigidDynamic, physics);
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

bool RigidDynamic::IsSleeping::get()
{
	return this->UnmanagedPointer->isSleeping();
}

float RigidDynamic::SleepThreshold::get()
{
	return this->UnmanagedPointer->getSleepThreshold();
}
void RigidDynamic::SleepThreshold::set(float value)
{
	this->UnmanagedPointer->setSleepThreshold(value);
}

float RigidDynamic::StabilizationThreshold::get()
{
	return this->UnmanagedPointer->getStabilizationThreshold();
}
void RigidDynamic::StabilizationThreshold::set(float value)
{
	this->UnmanagedPointer->setStabilizationThreshold(value);
}

float RigidDynamic::WakeCounter::get()
{
	return this->UnmanagedPointer->getWakeCounter();
}
void RigidDynamic::WakeCounter::set(float value)
{
	this->UnmanagedPointer->setWakeCounter(value);
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

float RigidDynamic::ContactReportThreshold::get()
{
	return this->UnmanagedPointer->getContactReportThreshold();
}
void RigidDynamic::ContactReportThreshold::set(float value)
{
	this->UnmanagedPointer->setContactReportThreshold(value);
}

PhysX::RigidDynamicLockFlags RigidDynamic::RigidDynamicLockFlags::get()
{
	return ToManagedEnum(PhysX::RigidDynamicLockFlags, this->UnmanagedPointer->getRigidDynamicLockFlags());
}
void RigidDynamic::RigidDynamicLockFlags::set(PhysX::RigidDynamicLockFlags value)
{
	this->UnmanagedPointer->setRigidDynamicLockFlags(ToUnmanagedEnum(PxRigidDynamicLockFlag, value));
}

PxRigidDynamic* RigidDynamic::UnmanagedPointer::get()
{
	return (PxRigidDynamic*)RigidBody::UnmanagedPointer;
}