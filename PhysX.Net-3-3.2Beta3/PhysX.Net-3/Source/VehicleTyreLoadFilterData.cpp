#include "StdAfx.h"
#include "VehicleTyreLoadFilterData.h"

VehicleTyreLoadFilterData^ VehicleTyreLoadFilterData::ToManaged(PxVehicleTyreLoadFilterData data)
{
	VehicleTyreLoadFilterData^ d = gcnew VehicleTyreLoadFilterData();
		d->MinNormalisedLoad = data.mMinNormalisedLoad;
		d->MaxNormalisedLoad = data.mMaxNormalisedLoad;
		d->MaxFilteredNormalisedLoad = data.mMaxFilteredNormalisedLoad;

	return d;
}
PxVehicleTyreLoadFilterData VehicleTyreLoadFilterData::ToUnmanaged(VehicleTyreLoadFilterData^ data)
{
	ThrowIfNull(data, "data");

	PxVehicleTyreLoadFilterData d;
		d.mMinNormalisedLoad = data->MinNormalisedLoad;
		d.mMaxNormalisedLoad = data->MaxNormalisedLoad;
		d.mMaxFilteredNormalisedLoad = data->MaxFilteredNormalisedLoad;

	return d;
}

float VehicleTyreLoadFilterData::Denominator::get()
{
	// Code from PxVehicle.h line 342
	return 1.0f/(MaxNormalisedLoad-MinNormalisedLoad);
}