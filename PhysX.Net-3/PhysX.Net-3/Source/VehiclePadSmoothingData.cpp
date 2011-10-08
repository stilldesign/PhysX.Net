#include "StdAfx.h"
#include "VehiclePadSmoothingData.h"

VehiclePadSmoothingData^ VehiclePadSmoothingData::ToManaged(PxVehiclePadSmoothingData desc)
{
	VehiclePadSmoothingData^ d = gcnew VehiclePadSmoothingData();
		d->RiseRates = Util::AsManagedArray<float>(&desc.mRiseRates, PxVehicleControlInputs::eMAX_NUM_VEHICLE_ANALOG_INPUTS);
		d->FallRates = Util::AsManagedArray<float>(&desc.mFallRates, PxVehicleControlInputs::eMAX_NUM_VEHICLE_ANALOG_INPUTS);

	return d;
}
PxVehiclePadSmoothingData VehiclePadSmoothingData::ToUnmanaged(VehiclePadSmoothingData^ desc)
{
	PxVehiclePadSmoothingData d;
		Util::AsUnmanagedArray(desc->RiseRates, &d.mRiseRates, PxVehicleControlInputs::eMAX_NUM_VEHICLE_ANALOG_INPUTS);
		Util::AsUnmanagedArray(desc->FallRates, &d.mFallRates, PxVehicleControlInputs::eMAX_NUM_VEHICLE_ANALOG_INPUTS);

	return d;
}