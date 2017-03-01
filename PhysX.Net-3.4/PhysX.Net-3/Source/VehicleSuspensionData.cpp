#include "StdAfx.h"
#include "VehicleSuspensionData.h"

PxVehicleSuspensionData VehicleSuspensionData::ToUnmanaged(VehicleSuspensionData^ data)
{
	ThrowIfNull(data, "data");

	PxVehicleSuspensionData d;
		d.mSpringStrength = data->SpringStrength;
		d.mSpringDamperRate = data->SpringDamperRate;
		d.mMaxCompression = data->MaxCompression;
		d.mMaxDroop = data->MaxDroop;
		d.mSprungMass = data->SprungMass;

	return d;
}
VehicleSuspensionData^ VehicleSuspensionData::ToManaged(PxVehicleSuspensionData data)
{
	VehicleSuspensionData^ d = gcnew VehicleSuspensionData();
		d->SpringStrength = data.mSpringStrength;
		d->SpringDamperRate = data.mSpringDamperRate;
		d->MaxCompression = data.mMaxCompression;
		d->MaxDroop = data.mMaxDroop;
		d->SprungMass = data.mSprungMass;

	return d;
}