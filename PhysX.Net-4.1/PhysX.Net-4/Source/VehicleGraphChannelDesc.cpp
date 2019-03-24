#include "StdAfx.h"
#include "VehicleGraphChannelDesc.h"

VehicleGraphChannelDesc^ VehicleGraphChannelDesc::FromUnmanaged(PxVehicleGraphChannelDesc desc)
{
	VehicleGraphChannelDesc^ d = gcnew VehicleGraphChannelDesc();
		d->MinY = desc.mMinY;
		d->MaxY = desc.mMaxY;
		d->MidY = desc.mMidY;
		d->ColorLow = MathUtil::PxVec3ToVector3(desc.mColorLow);
		d->ColorHigh = MathUtil::PxVec3ToVector3(desc.mColorHigh);
		d->Title = Util::ToManagedString(desc.mTitle);

	return d;
}
PxVehicleGraphChannelDesc VehicleGraphChannelDesc::ToUnmanaged(VehicleGraphChannelDesc^ desc)
{
	PxVehicleGraphChannelDesc d;
		d.mMinY = desc->MinY;
		d.mMaxY = desc->MaxY;
		d.mMidY = desc->MidY;
		d.mColorLow = MathUtil::Vector3ToPxVec3(desc->ColorLow);
		d.mColorHigh = MathUtil::Vector3ToPxVec3(desc->ColorHigh);
		d.mTitle = Util::ToUnmanagedString(desc->Title);

	return d;
}