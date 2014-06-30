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
		d.mCamberAtRest = data->CamberAtRest;
		d.mCamberAtMaxCompression = data->CamberAtMaxCompression;
		d.mCamberAtMaxDroop = data->CamberAtMaxDroop;

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
		d->CamberAtRest = data.mCamberAtRest;
		d->CamberAtMaxCompression = data.mCamberAtMaxCompression;
		d->CamberAtMaxDroop = data.mCamberAtMaxDroop;

	return d;
}