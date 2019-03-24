#include "StdAfx.h"
#include "VehicleTyreData.h"

VehicleTireData^ VehicleTireData::ToManaged(PxVehicleTireData tireData)
{
	auto d = gcnew VehicleTireData();
		d->LateralStiffnessX = tireData.mLatStiffX;
		d->LateralStiffnessY = tireData.mLatStiffY;
		d->LongitudinalStiffnessPerUnitGravity = tireData.mLongitudinalStiffnessPerUnitGravity;
		d->CamberStiffnessPerUnitGravity = tireData.mCamberStiffnessPerUnitGravity;
		// TODO:
		//Util::AsUnmanagedArray(d->FrictionVsSlipGraph, &tireData.mFrictionVsSlipGraph, 3*2);
		d->Type = tireData.mType;

	return d;
}
PxVehicleTireData VehicleTireData::ToUnmanaged(VehicleTireData^ tireData)
{
	ThrowIfNull(tireData, "tireData");

	PxVehicleTireData d;
		d.mLatStiffX = tireData->LateralStiffnessX;
		d.mLatStiffY = tireData->LateralStiffnessY;
		d.mLongitudinalStiffnessPerUnitGravity = tireData->LongitudinalStiffnessPerUnitGravity;
		d.mCamberStiffnessPerUnitGravity = tireData->CamberStiffnessPerUnitGravity;
		// TODO:
		//d->FrictionVsSlipGraph = Util::AsManagedArray(&tireData.mFrictionVsSlipGraph[0][0], 3*2);
		d.mType = tireData->Type;

	return d;
}