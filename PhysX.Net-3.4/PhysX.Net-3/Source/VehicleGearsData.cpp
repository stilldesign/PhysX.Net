#include "StdAfx.h"
#include "VehicleGearsData.h"

VehicleGearsData::VehicleGearsData()
{
	this->Ratios = gcnew array<float>(PxVehicleGearsData::eGEARSRATIO_COUNT);
}

PxVehicleGearsData VehicleGearsData::ToUnmanaged(VehicleGearsData^ gearsData)
{
	ThrowIfNull(gearsData, "gearsData");

	if (gearsData->Ratios == nullptr)
		throw gcnew ArgumentException(String::Format("The Ratios property must be an instance of an array and of length {0}", MaximumNumberOfGearRatios));

	PxVehicleGearsData d;
		Util::AsUnmanagedArray(gearsData->Ratios, &d.mRatios, PxVehicleGearsData::eGEARSRATIO_COUNT);
		d.mFinalRatio = gearsData->FinalRatio;
		d.mNbRatios = gearsData->NumberOfRatios;
		d.mSwitchTime = gearsData->SwitchTime;

	return d;
}
VehicleGearsData^ VehicleGearsData::ToManaged(PxVehicleGearsData gearsData)
{
	VehicleGearsData^ d = gcnew VehicleGearsData();
		d->Ratios = Util::AsManagedArray<float>(&gearsData.mRatios, PxVehicleGearsData::eGEARSRATIO_COUNT);
		d->FinalRatio = gearsData.mFinalRatio;
		d->NumberOfRatios = gearsData.mNbRatios;
		d->SwitchTime = gearsData.mSwitchTime;

	return d;
}