#include "StdAfx.h"
#include "VehicleChassisData.h"

PxVehicleChassisData VehicleChassisData::ToUnmanaged(VehicleChassisData^ data)
{
	ThrowIfNull(data, "data");

	PxVehicleChassisData d;
		d.mMOI = MathUtil::Vector3ToPxVec3(data->MomentOfInertia);
		d.mMass = data->Mass;
		d.mCMOffset = MathUtil::Vector3ToPxVec3(data->CenterOfMassOffset);

	return d;
}
VehicleChassisData^ VehicleChassisData::ToManaged(PxVehicleChassisData data)
{
	auto d = gcnew VehicleChassisData();
		d->MomentOfInertia = MathUtil::PxVec3ToVector3(data.mMOI);
		d->Mass = data.mMass;
		d->CenterOfMassOffset = MathUtil::PxVec3ToVector3(data.mCMOffset);

	return d;
}