#include "StdAfx.h"
#include "VehicleClutchData.h"

VehicleClutchData^ VehicleClutchData::ToManaged(PxVehicleClutchData data)
{
	VehicleClutchData^ d = gcnew VehicleClutchData();
		d->Strength = data.mStrength;

	return d;
}
PxVehicleClutchData VehicleClutchData::ToUnmanaged(VehicleClutchData^ data)
{
	ThrowIfNull(data, "data");

	PxVehicleClutchData d;
		d.mStrength = data->Strength;

	return d;
}