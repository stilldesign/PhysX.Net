#include "StdAfx.h"
#include "ControllerState.h"

ControllerState^ ControllerState::ToManaged(PxControllerState unmanaged)
{
	auto managed = gcnew ControllerState();
	
	managed->DeltaPosition = MV(unmanaged.deltaXP);
	managed->TouchedShape = ObjectTable::Instance->GetObject<Shape^>((intptr_t)unmanaged.touchedShape);
	managed->TouchedActor = ObjectTable::Instance->GetObject<RigidActor^>((intptr_t)unmanaged.touchedActor);
	managed->CollisionFlags = ToManagedEnum(ControllerCollisionFlag, unmanaged.collisionFlags);
	managed->StandingOnAnotherCct = unmanaged.standOnAnotherCCT;
	managed->StandingOnObstacle = unmanaged.standOnObstacle;
	managed->MovingUp = unmanaged.isMovingUp;

	return managed;
}