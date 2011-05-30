#include "StdAfx.h"
#include "Vehicle4W.h"

Vehicle4W::Vehicle4W(PxVehicle4W* vehicle)
{
	_vehicle = vehicle;
}
Vehicle4W::~Vehicle4W()
{
	this->!Vehicle4W();
}
Vehicle4W::!Vehicle4W()
{
	if (Disposed)
		return;

	_vehicle = NULL;
}

bool Vehicle4W::Disposed::get()
{
	return _vehicle == NULL;
}

bool Vehicle4W::UseAutoGears::get()
{
	return _vehicle->mUseAutoGears;
}
void Vehicle4W::UseAutoGears::set(bool value)
{
	_vehicle->mUseAutoGears = value;
}

bool Vehicle4W::GearUpPressed::get()
{
	return _vehicle->mGearUpPressed;
}
void Vehicle4W::GearUpPressed::set(bool value)
{
	_vehicle->mGearUpPressed = value;
}

bool Vehicle4W::GearDownPressed::get()
{
	return _vehicle->mGearDownPressed;
}
void Vehicle4W::GearDownPressed::set(bool value)
{
	_vehicle->mGearDownPressed = value;
}

int Vehicle4W::CurrentGear::get()
{
	return _vehicle->mCurrentGear;
}
void Vehicle4W::CurrentGear::set(int value)
{
	_vehicle->mCurrentGear = value;
}

int Vehicle4W::TargetGear::get()
{
	return _vehicle->mTargetGear;
}
void Vehicle4W::TargetGear::set(int value)
{
	_vehicle->mTargetGear = value;
}

array<float>^ Vehicle4W::InternalDynamics::get()
{
	return Util::AsManagedArray<float>(_vehicle->mInternalDynamics, PxVehicle4WSimulationData::eNUM_WHEELS + 1);
}
void Vehicle4W::InternalDynamics::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mInternalDynamics, PxVehicle4WSimulationData::eNUM_WHEELS + 1);
}

array<float>^ Vehicle4W::TyreLowForwardSpeedTimers::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mTyreLowForwardSpeedTimers, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::TyreLowForwardSpeedTimers::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mTyreLowForwardSpeedTimers, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<float>^ Vehicle4W::WheelRotationAngles::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mWheelRotationAngles, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::WheelRotationAngles::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mWheelRotationAngles, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<float>^ Vehicle4W::SuspensionJounces::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mSuspJounces, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::SuspensionJounces::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mSuspJounces, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<float>^ Vehicle4W::LongitudinalSlips::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mLongSlips, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::LongitudinalSlips::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mLongSlips, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<float>^ Vehicle4W::LaterialSlips::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mLatSlips, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::LaterialSlips::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mLatSlips, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<float>^ Vehicle4W::TypeFrictions::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mTyreFrictions, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::TypeFrictions::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mTyreFrictions, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<int>^ Vehicle4W::TyreSurfaceTypes::get()
{
	return Util::AsManagedArray<int>(&_vehicle->mTyreSurfaceTypes, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::TyreSurfaceTypes::set(array<int>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mTyreSurfaceTypes, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<Vector3>^ Vehicle4W::SuspensionLineStarts::get()
{
	return Util::AsManagedArray<Vector3>(&_vehicle->mSuspLineStarts, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::SuspensionLineStarts::set(array<Vector3>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mSuspLineStarts, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<Vector3>^ Vehicle4W::SuspensionLineDirections::get()
{
	return Util::AsManagedArray<Vector3>(&_vehicle->mSuspLineDirs, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::SuspensionLineDirections::set(array<Vector3>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mSuspLineDirs, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<float>^ Vehicle4W::SuspensionLineLengths::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mSuspLineLengths, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::SuspensionLineLengths::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mSuspLineLengths, PxVehicle4WSimulationData::eNUM_WHEELS);
}

float Vehicle4W::GearSwitchTime::get()
{
	return _vehicle->mGearSwitchTime;
}
void Vehicle4W::GearSwitchTime::set(float value)
{
	_vehicle->mGearSwitchTime = value;
}

float Vehicle4W::AutoBoxSwitchTime::get()
{
	return _vehicle->mAutoBoxSwitchTime;
}
void Vehicle4W::AutoBoxSwitchTime::set(float value)
{
	_vehicle->mAutoBoxSwitchTime = value;
}

PxVehicle4W* Vehicle4W::UnmanagedPointer::get()
{
	return _vehicle;
}