#include "StdAfx.h"
#include "VehicleEngineData.h"

PxVehicleEngineData VehicleEngineData::ToUnmanaged(VehicleEngineData^ data)
{
	ThrowIfNull(data, "data");

	PxVehicleEngineData d;
		d.mPeakTorque = data->PeakTorque;
		d.mMaxOmega = data->MaxOmega;
		d.mDampingRateFullThrottle = data->DampingRateFullThrottle;
		d.mDampingRateZeroThrottleClutchEngaged = data->DampingRateZeroThrottleClutchEngaged;
		d.mDampingRateZeroThrottleClutchDisengaged = data->DampingRateZeroThrottleClutchDisengaged;

	return d;
}
VehicleEngineData^ VehicleEngineData::ToManaged(PxVehicleEngineData data)
{
	auto d = gcnew VehicleEngineData();
		d->PeakTorque = data.mPeakTorque;
		d->MaxOmega = data.mMaxOmega;
		d->DampingRateFullThrottle = data.mDampingRateFullThrottle;
		d->DampingRateZeroThrottleClutchEngaged = data.mDampingRateZeroThrottleClutchEngaged;
		d->DampingRateZeroThrottleClutchDisengaged = data.mDampingRateZeroThrottleClutchDisengaged;

	return d;
}