#include "StdAfx.h"
#include "VehicleEngineData.h"

PxVehicleEngineData VehicleEngineData::ToUnmanaged(VehicleEngineData^ data)
{
	ThrowIfNull(data, "data");

	PxVehicleEngineData d;
		d.mDisengagedClutchDampingRate = data->DisengagedClutchDampingRate;
		d.mEngagedClutchDampingRate = data->EngagedClutchDampingRate;
		d.mMaxOmega = data->MaxOmega;
		d.mPeakTorque = data->PeakTorque;

	return d;
}
VehicleEngineData^ VehicleEngineData::ToManaged(PxVehicleEngineData data)
{
	VehicleEngineData^ d = gcnew VehicleEngineData();
		d->DisengagedClutchDampingRate = data.mDisengagedClutchDampingRate;
		d->EngagedClutchDampingRate = data.mEngagedClutchDampingRate;
		d->MaxOmega = data.mMaxOmega;
		d->PeakTorque = data.mPeakTorque;

	return d;
}