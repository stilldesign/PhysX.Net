#include "StdAfx.h"
#include "VehicleGearsData.h"

VehicleGearsData::VehicleGearsData()
{
	this->Ratios = gcnew array<float>(PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);
}

PxVehicleGearsData VehicleGearsData::ToUnmanaged(VehicleGearsData^ gearsData)
{
	ThrowIfNull(gearsData, "gearsData");

	if (gearsData->Ratios == nullptr)
		throw gcnew ArgumentException(String::Format("The Ratios property must be an instance of an array and of length {0}", MaximumNumberOfGearRatios));

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