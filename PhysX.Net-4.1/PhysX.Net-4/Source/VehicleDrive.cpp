#include "StdAfx.h"
#include "VehicleDrive.h"
#include "Physics.h"

VehicleDrive::VehicleDrive(PxVehicleDrive* drive, PhysX::Physics^ owner)
	: VehicleWheels(drive, owner)
{
	_driveDynData = gcnew VehicleDriveDynData(&drive->mDriveDynData);
}

VehicleDriveDynData^ VehicleDrive::DriveDynData::get()
{
	return _driveDynData;
}