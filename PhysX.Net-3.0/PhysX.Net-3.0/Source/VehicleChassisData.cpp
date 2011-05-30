#include "StdAfx.h"

#include "VehicleChassisData.h"

PxVehicleChassisData VehicleChassisData::ToUnmanaged(VehicleChassisData^ data)
{
	PxVehicleChassisData d;
		d.mMOI = MathUtil::Vector3ToPxVec3(data->MOI);
		d.mMass = data->Mass;
		d.mCMOffset = MathUtil::Vector3ToPxVec3(data->CMOffset);

	return d;
}