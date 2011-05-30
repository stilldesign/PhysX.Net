#include "StdAfx.h"
#include "VehicleGraphDesc.h"

PxVehicleGraphDesc VehicleGraphDesc::ToUnmanaged(VehicleGraphDesc desc)
{
	PxVehicleGraphDesc d;
		d.mPosX = desc.PositionX;
		d.mPosY = desc.PositionY;
		d.mSizeX = desc.SizeX;
		d.mSizeY = desc.SizeY;
		d.mBackgroundColour = MathUtil::Vector3ToPxVec3(desc.BackgroundColour);
		d.mAlpha = desc.Alpha;

	return d;
}