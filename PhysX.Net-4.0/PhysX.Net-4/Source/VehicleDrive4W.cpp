#include "StdAfx.h"
#include "VehicleDrive4W.h"
#include "Physics.h"

VehicleDrive4W::VehicleDrive4W(PhysX::Physics^ physics, RigidDynamic^ actor, VehicleWheelsSimData^ wheelsData, VehicleDriveSimData4W^ driveData, int numNonDrivenWheels)
	: VehicleDrive(Create(physics, actor, wheelsData, driveData, numNonDrivenWheels), physics)
{
	_simData = gcnew VehicleDriveSimData4W(&this->UnmanagedPointer->mDriveSimData);
}

PxVehicleDrive4W* VehicleDrive4W::Create(PhysX::Physics^ physics, RigidDynamic^ actor, VehicleWheelsSimData^ wheelsData, VehicleDriveSimData4W^ driveData, int numNonDrivenWheels)
{
	ThrowIfNullOrDisposed(physics, "physics");
	ThrowIfNullOrDisposed(actor, "actor");
	ThrowIfNull(wheelsData, "wheelsData");
	ThrowIfNull(driveData, "driveData");

	PxVehicleWheelsSimData* wd = wheelsData->UnmanagedPointer;
	PxVehicleDriveSimData4W* dd = driveData->UnmanagedPointer;
	
	return PxVehicleDrive4W::create(physics->UnmanagedPointer, actor->UnmanagedPointer, *wd, *dd, numNonDrivenWheels);
}

VehicleDriveSimData4W^ VehicleDrive4W::DriveSimData::get()
{
	return _simData;
}

PxVehicleDrive4W* VehicleDrive4W::UnmanagedPointer::get()
{
	return (PxVehicleDrive4W*)VehicleDrive::UnmanagedPointer;
}