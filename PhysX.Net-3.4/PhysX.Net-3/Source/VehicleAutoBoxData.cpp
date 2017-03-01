#include "StdAfx.h"
#include "VehicleAutoBoxData.h"

VehicleAutoBoxData^ VehicleAutoBoxData::ToManaged(PxVehicleAutoBoxData data)
{
	VehicleAutoBoxData^ d = gcnew VehicleAutoBoxData();
		d->UpRatios = Util::AsManagedArray<float>(data.mUpRatios, PxVehicleGearsData::eGEARSRATIO_COUNT);
		d->DownRatios = Util::AsManagedArray<float>(data.mDownRatios, PxVehicleGearsData::eGEARSRATIO_COUNT);

	return d;
}
PxVehicleAutoBoxData VehicleAutoBoxData::ToUnmanaged(VehicleAutoBoxData^ data)
{
	ThrowIfNull(data, "data");

	PxVehicleAutoBoxData d;
		Util::AsUnmanagedArray(data->UpRatios, &d.mUpRatios, PxVehicleGearsData::eGEARSRATIO_COUNT);
		Util::AsUnmanagedArray(data->DownRatios, &d.mDownRatios, PxVehicleGearsData::eGEARSRATIO_COUNT);

	return d;
}