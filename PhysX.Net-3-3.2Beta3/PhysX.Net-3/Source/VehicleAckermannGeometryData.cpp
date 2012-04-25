#include "StdAfx.h"
#include "VehicleAckermannGeometryData.h"

VehicleAckermannGeometryData::VehicleAckermannGeometryData(PxVehicleAckermannGeometryData* data)
{
	if (data == NULL)
		throw gcnew ArgumentNullException("data");

	_data = data;
}
VehicleAckermannGeometryData::~VehicleAckermannGeometryData()
{
	this->!VehicleAckermannGeometryData();
}
VehicleAckermannGeometryData::!VehicleAckermannGeometryData()
{
	SAFE_DELETE(_data);
}

bool VehicleAckermannGeometryData::Disposed::get()
{
	return _data == NULL;
}

float VehicleAckermannGeometryData::Accuracy::get()
{
	return _data->mAccuracy;
}
void VehicleAckermannGeometryData::Accuracy::set(float value)
{
	_data->mAccuracy = value;
}

float VehicleAckermannGeometryData::FrontWidth::get()
{
	return _data->getFrontWidth();
}

float VehicleAckermannGeometryData::AxleSeparation::get()
{
	return _data->getAxleSeparation();
}

PxVehicleAckermannGeometryData* VehicleAckermannGeometryData::UnmanagedPointer::get()
{
	return _data;
}