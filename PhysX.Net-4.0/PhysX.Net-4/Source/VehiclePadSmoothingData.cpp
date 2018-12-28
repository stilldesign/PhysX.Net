#include "StdAfx.h"
#include "VehiclePadSmoothingData.h"

VehiclePadSmoothingData^ VehiclePadSmoothingData::ToManaged(PxVehiclePadSmoothingData desc)
{
	auto d = gcnew VehiclePadSmoothingData();
		d->RiseRates = Util::AsManagedArray<float>(&desc.mRiseRates, PxVehicleDriveDynData::eMAX_NB_ANALOG_INPUTS);
		d->FallRates = Util::AsManagedArray<float>(&desc.mFallRates, PxVehicleDriveDynData::eMAX_NB_ANALOG_INPUTS);

	return d;
}
PxVehiclePadSmoothingData VehiclePadSmoothingData::ToUnmanaged(VehiclePadSmoothingData^ desc)
{
	PxVehiclePadSmoothingData d;
		Util::AsUnmanagedArray(desc->RiseRates, &d.mRiseRates, PxVehicleDriveDynData::eMAX_NB_ANALOG_INPUTS);
		Util::AsUnmanagedArray(desc->FallRates, &d.mFallRates, PxVehicleDriveDynData::eMAX_NB_ANALOG_INPUTS);

	return d;
}