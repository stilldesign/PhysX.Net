#include "StdAfx.h"
#include "RigidDynamic.h"
#include "SolverIterationCounts.h"

RigidDynamic::RigidDynamic(PxRigidDynamic* rigidDynamic, PhysX::Physics^ owner)
	: RigidBody(rigidDynamic, owner)
{
	
}

/// <summary>
/// Moves kinematically controlled dynamic actors through the game world.
/// </summary>
void RigidDynamic::MoveKinematic(Matrix destination)
{

}

/// <summary>
/// Wakes up the actor if it is sleeping.
/// </summary>
void RigidDynamic::WakeUp([Optional] Nullable<float> wakeCounterValue)
{

}

/// <summary>
/// Forces the actor to sleep.
/// </summary>
void RigidDynamic::PutToSleep()
{

}

String^ RigidDynamic::ToString()
{
	return String::Format("Rigid dynamic actor");
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

float RigidDynamic::SleepEnergyThreshold::get()
{
	return this->UnmanagedPointer->getSleepEnergyThreshold();
}
void RigidDynamic::SleepEnergyThreshold::set(float value)
{
	this->UnmanagedPointer->setSleepEnergyThreshold(value);
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