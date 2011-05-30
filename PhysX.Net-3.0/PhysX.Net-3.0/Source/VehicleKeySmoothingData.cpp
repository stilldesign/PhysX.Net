#include "StdAfx.h"
#include "VehicleKeySmoothingData.h"

VehicleKeySmoothingData^ VehicleKeySmoothingData::ToManaged(PxVehicleKeySmoothingData desc)
{
	VehicleKeySmoothingData^ d = gcnew VehicleKeySmoothingData();
		d->RiseRates = Util::AsManagedArray<float>(&desc.mRiseRates, PxVehicleControlInputs::eMAX_NUM_VEHICLE_ANALOG_INPUTS);
		d->FallRates = Util::AsManagedArray<float>(&desc.mFallRates, PxVehicleControlInputs::eMAX_NUM_VEHICLE_ANALOG_INPUTS);

	return d;
}
PxVehicleKeySmoothingData VehicleKeySmoothingData::ToUnmanaged(VehicleKeySmoothingData^ desc)
{
	PxVehicleKeySmoothingData d;
		Util::AsUnmanagedArray(desc->RiseRates, &d.mRiseRates, PxVehicleControlInputs::eMAX_NUM_VEHICLE_ANALOG_INPUTS);
		Util::AsUnmanagedArray(desc->FallRates, &d.mFallRates, PxVehicleControlInputs::eMAX_NUM_VEHICLE_ANALOG_INPUTS);

	return d;
}