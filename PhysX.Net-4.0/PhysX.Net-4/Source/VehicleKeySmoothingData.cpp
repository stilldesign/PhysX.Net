#include "StdAfx.h"
#include "VehicleKeySmoothingData.h"

VehicleKeySmoothingData^ VehicleKeySmoothingData::ToManaged(PxVehicleKeySmoothingData desc)
{
	auto d = gcnew VehicleKeySmoothingData();
		d->RiseRates = Util::AsManagedArray<float>(&desc.mRiseRates, PxVehicleDriveDynData::eMAX_NB_ANALOG_INPUTS);
		d->FallRates = Util::AsManagedArray<float>(&desc.mFallRates, PxVehicleDriveDynData::eMAX_NB_ANALOG_INPUTS);

	return d;
}
PxVehicleKeySmoothingData VehicleKeySmoothingData::ToUnmanaged(VehicleKeySmoothingData^ desc)
{
	ThrowIfNull(desc, "desc");

	PxVehicleKeySmoothingData d;
		Util::AsUnmanagedArray(desc->RiseRates, &d.mRiseRates, PxVehicleDriveDynData::eMAX_NB_ANALOG_INPUTS);
		Util::AsUnmanagedArray(desc->FallRates, &d.mFallRates, PxVehicleDriveDynData::eMAX_NB_ANALOG_INPUTS);

	return d;
}