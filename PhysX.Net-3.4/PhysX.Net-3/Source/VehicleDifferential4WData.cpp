#include "StdAfx.h"
#include "VehicleDifferential4WData.h"

PxVehicleDifferential4WData VehicleDifferential4WData::ToUnmanaged(VehicleDifferential4WData^ data)
{
	PxVehicleDifferential4WData d;
		d.mFrontRearSplit = data->FrontRearSplit;
		d.mCentreBias = data->CentreBias;
		d.mFrontBias = data->FrontBias;
		d.mRearBias = data->RearBias;
		d.mType = ToUnmanagedEnum(PxVehicleDifferential4WData, data->Type);
	
	return d;
}
VehicleDifferential4WData^ VehicleDifferential4WData::ToManaged(PxVehicleDifferential4WData data)
{
	VehicleDifferential4WData^ d = gcnew VehicleDifferential4WData();
		d->FrontRearSplit = data.mFrontRearSplit;
		d->CentreBias = data.mCentreBias;
		d->FrontBias = data.mFrontBias;
		d->RearBias = data.mRearBias;
		d->Type = ToManagedEnum(VehicleDifferentialType, data.mType);

	return d;
}