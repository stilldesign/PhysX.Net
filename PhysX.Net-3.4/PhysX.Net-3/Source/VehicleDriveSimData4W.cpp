#include "StdAfx.h"
#include "VehicleDriveSimData4W.h"
#include "VehicleDifferential4WData.h"
#include "VehicleAckermannGeometryData.h"

VehicleDriveSimData4W::VehicleDriveSimData4W()
	: VehicleDriveSimData(Create())
{
	
}
PxVehicleDriveSimData4W* VehicleDriveSimData4W::Create()
{
	return new PxVehicleDriveSimData4W();
}
VehicleDriveSimData4W::VehicleDriveSimData4W(PxVehicleDriveSimData4W* data)
	: VehicleDriveSimData(data)
{
	
}

VehicleDifferential4WData^ VehicleDriveSimData4W::GetDifferentialData()
{
	return VehicleDifferential4WData::ToManaged(this->UnmanagedPointer->getDiffData());
}
void VehicleDriveSimData4W::SetDifferentialData(VehicleDifferential4WData^ data)
{
	this->UnmanagedPointer->setDiffData(VehicleDifferential4WData::ToUnmanaged(data));
}

VehicleAckermannGeometryData^ VehicleDriveSimData4W::GetAckermannGeometryData()
{
	return VehicleAckermannGeometryData::ToManaged(this->UnmanagedPointer->getAckermannGeometryData());
}
void VehicleDriveSimData4W::SetAckermannGeometryData(VehicleAckermannGeometryData^ data)
{
	this->UnmanagedPointer->setAckermannGeometryData(VehicleAckermannGeometryData::ToUnmanaged(data));
}

PxVehicleDriveSimData4W* VehicleDriveSimData4W::UnmanagedPointer::get()
{
	return (PxVehicleDriveSimData4W*)VehicleDriveSimData::UnmanagedPointer;
}