#include "StdAfx.h"
#include "VehicleWheelQueryResult.h"

VehicleWheelQueryResult^ VehicleWheelQueryResult::ToManaged(PxWheelQueryResult* unmanaged)
{
	auto managed = gcnew VehicleWheelQueryResult();

	managed->SuspensionLineStart = MV(unmanaged->suspLineStart);
	managed->SuspensionLineDirection = MV(unmanaged->suspLineDir);
	managed->SuspensionLineLength = unmanaged->suspLineLength;
	managed->IsInAir = unmanaged->isInAir;
	managed->TireContactActor = unmanaged->tireContactActor == NULL ? nullptr : ObjectTable::GetObject<Actor^>((intptr_t)unmanaged->tireContactActor);
	managed->TireContactShape = unmanaged->tireContactShape == NULL ? nullptr : ObjectTable::GetObject<Shape^>((intptr_t)unmanaged->tireContactShape);
	managed->TireSurfaceMaterial = unmanaged->tireSurfaceMaterial == NULL ? nullptr : ObjectTable::GetObject<Material^>((intptr_t)unmanaged->tireSurfaceMaterial);
	managed->TireSurfaceType = unmanaged->tireSurfaceType;
	managed->TireContactPoint = MV(unmanaged->tireContactPoint);
	managed->TireContactNormal = MV(unmanaged->tireContactNormal);
	managed->TireFriction = unmanaged->tireFriction;
	managed->SuspensionJounce = unmanaged->suspJounce;
	managed->SuspensionSpringForce = unmanaged->suspSpringForce;
	managed->TireLongitudinalDirection = MV(unmanaged->tireLongitudinalDir);
	managed->TireLateralDirection = MV(unmanaged->tireLateralDir);
	managed->LongitudinalSlip = unmanaged->longitudinalSlip;
	managed->LateralSlip = unmanaged->lateralSlip;
	managed->SteerAngle = unmanaged->steerAngle;
	managed->LocalPose = MM(&unmanaged->localPose);

	return managed;
}