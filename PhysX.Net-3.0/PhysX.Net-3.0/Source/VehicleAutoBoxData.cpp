#include "StdAfx.h"
#include "VehicleAutoBoxData.h"

VehicleAutoBoxData^ VehicleAutoBoxData::FromUnmanaged(PxVehicleAutoBoxData data)
{
	VehicleAutoBoxData^ d = gcnew VehicleAutoBoxData();
		d->UpRatios = Util::AsManagedArray<float>(data.mUpRatios, PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);
		d->DownRatios = Util::AsManagedArray<float>(data.mDownRatios, PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);

	return d;
}
PxVehicleAutoBoxData VehicleAutoBoxData::ToUnmanaged(VehicleAutoBoxData^ data)
{
	ThrowIfNull(data, "data");

	PxVehicleAutoBoxData d;
		Util::AsUnmanagedArray(data->UpRatios, &d.mUpRatios, PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);
		Util::AsUnmanagedArray(data->DownRatios, &d.mDownRatios, PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);

	return d;
}