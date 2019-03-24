#include "StdAfx.h"
#include "VehicleAntiRollBarData.h"
#include <vehicle\PxVehicleComponents.h> 

PxVehicleAntiRollBarData VehicleAntiRollBarData::ToUnmanaged(VehicleAntiRollBarData^ managed)
{
	PxVehicleAntiRollBarData u;
	u.mWheel0 = managed->Wheel0;
	u.mWheel1 = managed->Wheel1;
	u.mStiffness = managed->Stiffness;

	return u;
}
VehicleAntiRollBarData^ VehicleAntiRollBarData::ToManaged(PxVehicleAntiRollBarData unmanaged)
{
	auto m = gcnew VehicleAntiRollBarData();
	m->Wheel0 = unmanaged.mWheel0;
	m->Wheel1 = unmanaged.mWheel1;
	m->Stiffness = unmanaged.mStiffness;

	return m;
}