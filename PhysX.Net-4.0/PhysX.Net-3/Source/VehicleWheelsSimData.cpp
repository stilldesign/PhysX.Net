#include "StdAfx.h"
#include "VehicleWheelsSimData.h"
#include "VehicleSuspensionData.h"
#include "VehicleWheelData.h"
#include "VehicleTyreData.h"
#include "VehicleTireLoadFilterData.h"
#include "VehicleAntiRollBarData.h"

VehicleWheelsSimData::VehicleWheelsSimData(int numberOfWheels)
{
	_data = PxVehicleWheelsSimData::allocate(numberOfWheels);
}

void VehicleWheelsSimData::SetChassisMass(float chassisMass)
{
	_data->setChassisMass(chassisMass);
}

void VehicleWheelsSimData::CopyWheelData(VehicleWheelsSimData^ sourceData, int sourceWheelIndex, int targetWheelIndex)
{
	_data->copy(*sourceData->_data, sourceWheelIndex, targetWheelIndex);
}

VehicleSuspensionData^ VehicleWheelsSimData::GetSuspensionData(int id)
{
	return VehicleSuspensionData::ToManaged(_data->getSuspensionData(id));
}
void VehicleWheelsSimData::SetSuspensionData(int id, VehicleSuspensionData^ data)
{
	_data->setSuspensionData(id, VehicleSuspensionData::ToUnmanaged(data));
}

VehicleWheelData^ VehicleWheelsSimData::GetWheelData(int id)
{
	return VehicleWheelData::ToManaged(_data->getWheelData(id));
}
void VehicleWheelsSimData::SetWheelData(int id, VehicleWheelData^ data)
{
	_data->setWheelData(id, VehicleWheelData::ToUnmanaged(data));
}

VehicleTireData^ VehicleWheelsSimData::GetTireData(int id)
{
	return VehicleTireData::ToManaged(_data->getTireData(id));
}
void VehicleWheelsSimData::SetTireData(int id, VehicleTireData^ data)
{
	_data->setTireData(id, VehicleTireData::ToUnmanaged(data));
}

Vector3 VehicleWheelsSimData::GetSuspensionTravelDirection(int id)
{
	return MV(_data->getSuspTravelDirection(id));
}
void VehicleWheelsSimData::SetSuspensionTravelDirection(int id, Vector3 direction)
{
	_data->setSuspTravelDirection(id, UV(direction));
}

Vector3 VehicleWheelsSimData::GetSuspensionForceApplicationPointOffset(int id)
{
	return MV(_data->getSuspForceAppPointOffset(id));
}
void VehicleWheelsSimData::SetSuspensionForceApplicationPointOffset(int id, Vector3 offset)
{
	_data->setSuspForceAppPointOffset(id, UV(offset));
}

Vector3 VehicleWheelsSimData::GetTireForceApplicationPointOffset(int id)
{
	return MV(_data->getTireForceAppPointOffset(id));
}
void VehicleWheelsSimData::SetTireForceApplicationPointOffset(int id, Vector3 offset)
{
	_data->setTireForceAppPointOffset(id, UV(offset));
}

Vector3 VehicleWheelsSimData::GetWheelCentreOffset(int id)
{
	return MV(_data->getWheelCentreOffset(id));
}
void VehicleWheelsSimData::SetWheelCentreOffset(int id, Vector3 offset)
{
	_data->setWheelCentreOffset(id, UV(offset));
}

VehicleTireLoadFilterData^ VehicleWheelsSimData::GetTireLoadFilterData()
{
	return VehicleTireLoadFilterData::ToManaged(_data->getTireLoadFilterData());
}
void VehicleWheelsSimData::SetTireLoadFilterData(VehicleTireLoadFilterData^ filterData)
{
	_data->setTireLoadFilterData(VehicleTireLoadFilterData::ToUnmanaged(filterData));
}

void VehicleWheelsSimData::DisableWheel(int wheel)
{
	_data->disableWheel(wheel);
}

bool VehicleWheelsSimData::IsWheelDisabled(int wheel)
{
	return _data->getIsWheelDisabled(wheel);
}

int VehicleWheelsSimData::GetWheelShapeMapping(int wheelId)
{
	return _data->getWheelShapeMapping(wheelId);
}
void VehicleWheelsSimData::SetWheelShapeMapping(int wheelId, int shapeId)
{
	_data->setWheelShapeMapping(wheelId, shapeId);
}

int VehicleWheelsSimData::AddAntiRollBarData(VehicleAntiRollBarData^ data)
{
	return _data->addAntiRollBarData(VehicleAntiRollBarData::ToUnmanaged(data));
}
VehicleAntiRollBarData^ VehicleWheelsSimData::GetAntiRollBarData(int antiRollBarId)
{
	return VehicleAntiRollBarData::ToManaged(_data->getAntiRollBarData(antiRollBarId));
}
void VehicleWheelsSimData::GetAntiRollBarData(int antiRollBarId, VehicleAntiRollBarData^ data)
{
	_data->setAntiRollBarData(antiRollBarId, VehicleAntiRollBarData::ToUnmanaged(data));
}
int VehicleWheelsSimData::NumberOfAntiRollBars::get()
{
	return _data->getNbAntiRollBars();
}

int VehicleWheelsSimData::NumberOfWheels::get()
{
	return _data->getNbWheels();
}

PxVehicleWheelsSimData* VehicleWheelsSimData::UnmanagedPointer::get()
{
	return _data;
}