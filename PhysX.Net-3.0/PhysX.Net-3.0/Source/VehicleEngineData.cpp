#include "StdAfx.h"
#include "VehicleEngineData.h"

VehicleEngineData::VehicleEngineData(PxVehicleEngineData* engineData)
{
	if (engineData == NULL)
		throw gcnew ArgumentNullException("engineData");

	_engineData = engineData;
}
VehicleEngineData::~VehicleEngineData()
{
	this->!VehicleEngineData();
}
VehicleEngineData::!VehicleEngineData()
{
	SAFE_DELETE(_engineData);
}

bool VehicleEngineData::Disposed::get()
{
	return _engineData == NULL;
}

float VehicleEngineData::PeakTorque::get()
{
	return _engineData->mPeakTorque;
}
void VehicleEngineData::PeakTorque::set(float value)
{
	_engineData->mPeakTorque = value;
}

float VehicleEngineData::MaxOmega::get()
{
	return _engineData->mMaxOmega;
}
void VehicleEngineData::MaxOmega::set(float value)
{
	_engineData->mMaxOmega = value;
}

float VehicleEngineData::EngagedClutchDampingRate::get()
{
	return _engineData->mEngagedClutchDampingRate;
}
void VehicleEngineData::EngagedClutchDampingRate::set(float value)
{
	_engineData->mEngagedClutchDampingRate = value;
}

float VehicleEngineData::DisengagedClutchDampingRate::get()
{
	return _engineData->mDisengagedClutchDampingRate;
}
void VehicleEngineData::DisengagedClutchDampingRate::set(float value)
{
	_engineData->mDisengagedClutchDampingRate = value;
}

PxVehicleEngineData* VehicleEngineData::UnmanagedPointer::get()
{
	return _engineData;
}