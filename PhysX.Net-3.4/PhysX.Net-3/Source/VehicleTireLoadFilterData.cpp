#include "StdAfx.h"
#include "VehicleTireLoadFilterData.h"

VehicleTireLoadFilterData^ VehicleTireLoadFilterData::ToManaged(PxVehicleTireLoadFilterData data)
{
	auto d = gcnew VehicleTireLoadFilterData();
		d->MinNormalisedLoad = data.mMinNormalisedLoad;
		d->MaxNormalisedLoad = data.mMaxNormalisedLoad;
		d->MaxFilteredNormalisedLoad = data.mMaxFilteredNormalisedLoad;

	return d;
}
PxVehicleTireLoadFilterData VehicleTireLoadFilterData::ToUnmanaged(VehicleTireLoadFilterData^ data)
{
	ThrowIfNull(data, "data");

	PxVehicleTireLoadFilterData d;
		d.mMinNormalisedLoad = data->MinNormalisedLoad;
		d.mMaxNormalisedLoad = data->MaxNormalisedLoad;
		d.mMaxFilteredNormalisedLoad = data->MaxFilteredNormalisedLoad;

	return d;
}

float VehicleTireLoadFilterData::Denominator::get()
{
	// Code from PxVehicle.h line 342
	return 1.0f/(MaxNormalisedLoad-MinNormalisedLoad);
}