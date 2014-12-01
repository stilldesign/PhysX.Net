#include "StdAfx.h"
#include "VehicleNoDrive.h"
#include "Physics.h"
#include "VehicleWheelsSimData.h"
#include "RigidDynamic.h"

using namespace PhysX;

VehicleNoDrive::VehicleNoDrive(PxVehicleNoDrive* noDrive, PhysX::Physics^ owner)
	: VehicleWheels(noDrive, owner)
{

}

//VehicleNoDrive::VehicleNoDrive(int numberOfWheels, PhysX::Physics^ owner)
//	: VehicleWheels(Create(numberOfWheels), owner)
//{
//
//}
VehicleNoDrive::VehicleNoDrive(PhysX::Physics^ physics, RigidDynamic^ vehicleActor, VehicleWheelsSimData^ wheelsData)
	: VehicleWheels(Create(physics, vehicleActor, wheelsData), physics)
{

}

//PxVehicleNoDrive* VehicleNoDrive::Create(int numberOfWheels)
//{
//	PxVehicleNoDrive::create()
//}
PxVehicleNoDrive* VehicleNoDrive::Create(PhysX::Physics^ physics, RigidDynamic^ vehicleActor, VehicleWheelsSimData^ wheelsData)
{
	return PxVehicleNoDrive::create(physics->UnmanagedPointer, vehicleActor->UnmanagedPointer, *wheelsData->UnmanagedPointer);
}

void VehicleNoDrive::Setup(PhysX::Physics^ physics, RigidDynamic^ vehicleActor, VehicleWheelsSimData^ wheelsData)
{
	this->UnmanagedPointer->setup(physics->UnmanagedPointer, vehicleActor->UnmanagedPointer, *wheelsData->UnmanagedPointer);
}

void VehicleNoDrive::SetToRestState()
{
	this->UnmanagedPointer->setToRestState();
}

float VehicleNoDrive::GetBrakeTorque(int id)
{
	return this->UnmanagedPointer->getBrakeTorque(id);
}
void VehicleNoDrive::SetBrakeTorque(int id, float brakeTorque)
{
	this->UnmanagedPointer->setBrakeTorque(id, brakeTorque);
}

float VehicleNoDrive::GetDriveTorque(int id)
{
	return this->UnmanagedPointer->getDriveTorque(id);
}
void VehicleNoDrive::SetDriveTorque(int id, float driveTorque)
{
	this->UnmanagedPointer->setDriveTorque(id, driveTorque);
}

float VehicleNoDrive::GetSteerAngle(int id)
{
	return this->UnmanagedPointer->getSteerAngle(id);
}
void VehicleNoDrive::SetSteerAngle(int id, float steerAngle)
{
	this->UnmanagedPointer->setSteerAngle(id, steerAngle);
}

int VehicleNoDrive::SteeringAngleCount::get()
{
	return this->UnmanagedPointer->getNbSteerAngle();
}
int VehicleNoDrive::DriveTorqueCount::get()
{
	return this->UnmanagedPointer->getNbDriveTorque();
}
int VehicleNoDrive::BrakeTorqueCount::get()
{
	return this->UnmanagedPointer->getNbBrakeTorque();
}

//

PxVehicleNoDrive* VehicleNoDrive::UnmanagedPointer::get()
{
	return (PxVehicleNoDrive*)VehicleWheels::UnmanagedPointer;
}