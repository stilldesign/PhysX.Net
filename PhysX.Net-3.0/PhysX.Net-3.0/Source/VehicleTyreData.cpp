#include "StdAfx.h"
#include "VehicleTyreData.h"

VehicleTyreData^ VehicleTyreData::ToManaged(PxVehicleTyreData tyreData)
{
	VehicleTyreData^ d = gcnew VehicleTyreData();
		d->LateralStiffnessX = tyreData.mLatStiffX;
		d->LateralStiffnessY = tyreData.mLatStiffY;
		d->LongitudinalStiffness = tyreData.mLongitudinalStiffness;
		d->CamberStiffness = tyreData.mCamberStiffness;
		// TODO: array of arrays
		//d->FrictionVsSlipGraph = tyreData.mFrictionVsSlipGraph;
		d->Type = tyreData.mType;

	return d;
}
PxVehicleTyreData VehicleTyreData::ToUnmanaged(VehicleTyreData^ tyreData)
{
	PxVehicleTyreData d;
		d.mLatStiffX = tyreData->LateralStiffnessX;
		d.mLatStiffY = tyreData->LateralStiffnessY;
		d.mLongitudinalStiffness = tyreData->LongitudinalStiffness;
		d.mCamberStiffness = tyreData->CamberStiffness;
		// TODO: array of arrays
		//d->FrictionVsSlipGraph = tyreData.mFrictionVsSlipGraph;
		d.mType = tyreData->Type;

	return d;
}