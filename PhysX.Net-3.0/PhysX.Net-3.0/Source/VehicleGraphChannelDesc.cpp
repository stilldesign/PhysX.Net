#include "StdAfx.h"
#include "VehicleGraphChannelDesc.h"

VehicleGraphChannelDesc^ VehicleGraphChannelDesc::FromUnmanaged(PxVehicleGraphChannelDesc desc)
{
	VehicleGraphChannelDesc^ d = gcnew VehicleGraphChannelDesc();
		d->MinY = desc.mMinY;
		d->MaxY = desc.mMaxY;
		d->MidY = desc.mMidY;
		d->ColourLow = MathUtil::PxVec3ToVector3(desc.mColourLow);
		d->ColourHigh = MathUtil::PxVec3ToVector3(desc.mColourHigh);
		d->Title = Util::ToManagedString(desc.mTitle);

	return d;
}
PxVehicleGraphChannelDesc VehicleGraphChannelDesc::ToUnmanaged(VehicleGraphChannelDesc^ desc)
{
	PxVehicleGraphChannelDesc d;
		d.mMinY = desc->MinY;
		d.mMaxY = desc->MaxY;
		d.mMidY = desc->MidY;
		d.mColourLow = MathUtil::Vector3ToPxVec3(desc->ColourLow);
		d.mColourHigh = MathUtil::Vector3ToPxVec3(desc->ColourHigh);
		d.mTitle = Util::ToUnmanagedString(desc->Title);

	return d;
}