#include "StdAfx.h"
#include "VehicleDriveDynData.h"

VehicleDriveDynData::VehicleDriveDynData(PxVehicleDriveDynData* data)
{
	// Do not dispose or delete this object as it is owned by PxVehicleDrive

	_data = data;
}

void VehicleDriveDynData::SetToRestState()
{
	_data->setToRestState();
}

void VehicleDriveDynData::ToggleAutoGears()
{
	_data->toggleAutoGears();
}

void VehicleDriveDynData::StartGearChange(int targetGear)
{
	_data->startGearChange(targetGear);
}

void VehicleDriveDynData::ForceGearChange(int targetGear)
{
	_data->forceGearChange(targetGear);
}

//

bool VehicleDriveDynData::UseAutoGears::get()
{
	return _data->getUseAutoGears();
}
void VehicleDriveDynData::UseAutoGears::set(bool value)
{
	_data->setUseAutoGears(value);
}

bool VehicleDriveDynData::GearUpPressed::get()
{
	return _data->getGearUp();
}
void VehicleDriveDynData::GearUpPressed::set(bool value)
{
	_data->setGearUp(value);
}

bool VehicleDriveDynData::GearDownPressed::get()
{
	return _data->getGearDown();
}
void VehicleDriveDynData::GearDownPressed::set(bool value)
{
	_data->setGearDown(value);
}

int VehicleDriveDynData::CurrentGear::get()
{
	return _data->getCurrentGear();
}

int VehicleDriveDynData::TargetGear::get()
{
	return _data->getTargetGear();
}

float VehicleDriveDynData::EngineRotationSpeed::get()
{
	return _data->getEngineRotationSpeed();
}

float VehicleDriveDynData::GearSwitchTime::get()
{
	return _data->mGearSwitchTime;
}
void VehicleDriveDynData::GearSwitchTime::set(float value)
{
	_data->mGearSwitchTime = value;
}

float VehicleDriveDynData::AutoBoxSwitchTime::get()
{
	return _data->mAutoBoxSwitchTime;
}
void VehicleDriveDynData::AutoBoxSwitchTime::set(float value)
{
	_data->mAutoBoxSwitchTime = value;
}