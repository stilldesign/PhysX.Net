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
VehicleChassisData^ VehicleChassisData::ToManaged(PxVehicleChassisData data)
{
	VehicleChassisData^ d = gcnew VehicleChassisData();
		d->CMOffset = MathUtil::PxVec3ToVector3(data.mCMOffset);
		d->Mass = data.mMass;
		d->MOI = MathUtil::PxVec3ToVector3(data.mMOI);

	return d;
}