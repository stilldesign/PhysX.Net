#include "StdAfx.h"
#include "VehicleDriveSimData.h"
#include "VehicleEngineData.h"
#include "VehicleGearsData.h"
#include "VehicleClutchData.h"
#include "VehicleAutoBoxData.h"

VehicleDriveSimData::VehicleDriveSimData()
{
	_data = new PxVehicleDriveSimData();
}
VehicleDriveSimData::VehicleDriveSimData(PxVehicleDriveSimData* data)
{
	if (data == NULL)
		throw gcnew ArgumentNullException("data");

	_data = data;
}

VehicleEngineData^ VehicleDriveSimData::GetEngineData()
{
	return VehicleEngineData::ToManaged(_data->getEngineData());
}
void VehicleDriveSimData::SetEngineData(VehicleEngineData^ engine)
{
	_data->setEngineData(VehicleEngineData::ToUnmanaged(engine));
}

VehicleClutchData^ VehicleDriveSimData::GetClutchData()
{
	return VehicleClutchData::ToManaged(_data->getClutchData());
}
void VehicleDriveSimData::SetClutchData(VehicleClutchData^ clutch)
{
	_data->setClutchData(VehicleClutchData::ToUnmanaged(clutch));
}

VehicleGearsData^ VehicleDriveSimData::GetGearsData()
{
	return VehicleGearsData::ToManaged(_data->getGearsData());
}
void VehicleDriveSimData::SetGearsData(VehicleGearsData^ gears)
{
	_data->setGearsData(VehicleGearsData::ToUnmanaged(gears));
}

VehicleAutoBoxData^ VehicleDriveSimData::GetAutoBoxData()
{
	return VehicleAutoBoxData::ToManaged(_data->getAutoBoxData());
}
void VehicleDriveSimData::SetAutoBoxData(VehicleAutoBoxData^ autobox)
{
	_data->setAutoBoxData(VehicleAutoBoxData::ToUnmanaged(autobox));
}

PxVehicleDriveSimData* VehicleDriveSimData::UnmanagedPointer::get()
{
	return _data;
}