#include "StdAfx.h"
#include "VehicleAckermannGeometryData.h"

VehicleAckermannGeometryData^ VehicleAckermannGeometryData::ToManaged(PxVehicleAckermannGeometryData data)
{
	auto d = gcnew VehicleAckermannGeometryData();
		d->Accuracy = data.mAccuracy;
		d->FrontWidth = data.mFrontWidth;
		d->RearWidth = data.mRearWidth;
		d->AxleSeparation = data.mAxleSeparation;
	
	return d;
}
PxVehicleAckermannGeometryData VehicleAckermannGeometryData::ToUnmanaged(VehicleAckermannGeometryData^ data)
{
	ThrowIfNull(data, "data");

	PxVehicleAckermannGeometryData d;
		d.mAccuracy = data->Accuracy;
		d.mFrontWidth = data->FrontWidth;
		d.mRearWidth = data->RearWidth;
		d.mAxleSeparation = data->AxleSeparation;
	
	return d;
}