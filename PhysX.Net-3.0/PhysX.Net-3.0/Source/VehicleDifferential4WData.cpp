#include "StdAfx.h"
#include "VehicleDifferential4WData.h"

PxVehicleDifferential4WData VehicleDifferential4WData::ToUnmanaged(VehicleDifferential4WData data)
{
	PxVehicleDifferential4WData d;
		d.mFrontRearSplit = data.FrontRearSplit;
		d.mCentreBias = data.CentreBias;
		d.mFrontBias = data.FrontBias;
		d.mRearBias = data.RearBias;
		d.mType = (PxU32)data.Type;
	
	return d;
}