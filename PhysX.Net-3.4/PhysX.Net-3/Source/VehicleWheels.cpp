#include "StdAfx.h"
#include "VehicleWheels.h"
#include "Physics.h"
#include "Actor.h"

VehicleWheels::VehicleWheels(PxVehicleWheels* wheels, PhysX::Physics^ owner)
{
	if (wheels == NULL)
		throw gcnew ArgumentNullException("wheels");
	ThrowIfNullOrDisposed(owner, "owner");

	_wheels = wheels;

	ObjectTable::Instance->Add((intptr_t)wheels, this, owner);
}
VehicleWheels::~VehicleWheels()
{
	this->!VehicleWheels();
}
VehicleWheels::!VehicleWheels()
{
	OnDisposing(this, nullptr);

	if (this->Disposed)
		return;
	
	// The derived types will dispose of the wheel instance.
	_wheels = NULL;

	OnDisposed(this, nullptr);
}

bool VehicleWheels::Disposed::get()
{
	return (_wheels == NULL);
}

float VehicleWheels::ComputeForwardSpeed()
{
	return _wheels->computeForwardSpeed();
}
float VehicleWheels::ComputeSidewaysSpeed()
{
	return _wheels->computeSidewaysSpeed();
}

//

PhysX::Physics^ VehicleWheels::Physics::get()
{
	return ObjectTable::Instance->GetObject<PhysX::Physics^>((intptr_t)_wheels);
}

int VehicleWheels::VehicleType::get()
{
	return _wheels->getVehicleType();
}

PhysX::RigidDynamic^ VehicleWheels::Actor::get()
{
	PxRigidDynamic* actor = _wheels->getRigidDynamicActor();

	return ObjectTable::Instance->GetObject<RigidDynamic^>((intptr_t)actor);
}

PxVehicleWheels* VehicleWheels::UnmanagedPointer::get()
{
	return _wheels;
}