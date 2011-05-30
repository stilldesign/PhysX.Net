#include "StdAfx.h"
#include "VehicleGearsData.h"

PxVehicleGearsData VehicleGearsData::ToUnmanaged(VehicleGearsData^ gearsData)
{
	PxVehicleGearsData d;
		Util::AsUnmanagedArray(gearsData->Ratios, &d.mRatios, PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);
		d.mFinalRatio = gearsData->FinalRatio;
		d.mNumRatios = gearsData->NumberOfRatios;
		d.mSwitchTime = gearsData->SwitchTime;

	return d;
}
VehicleGearsData^ VehicleGearsData::ToManaged(PxVehicleGearsData gearsData)
{
	VehicleGearsData^ d = gcnew VehicleGearsData();
		d->Ratios = Util::AsManagedArray<float>(&gearsData.mRatios, PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);
		d->FinalRatio = gearsData.mFinalRatio;
		d->NumberOfRatios = gearsData.mNumRatios;
		d->SwitchTime = gearsData.mSwitchTime;

	return d;
}