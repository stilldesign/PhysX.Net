#include "StdAfx.h"
#include "ControllerShapeHit.h"

ControllerShapeHit^ ControllerShapeHit::ToManaged(PxControllerShapeHit hit)
{
	ControllerShapeHit^ h = gcnew ControllerShapeHit();
		h->Controller = ObjectTable::GetObject<PhysX::Controller^>((intptr_t)hit.controller);
		h->Shape = ObjectTable::GetObject<PhysX::Shape^>((intptr_t)hit.shape);
		h->WorldPosition = MathUtil::PxExtendedVec3ToVector3(hit.worldPos);
		h->WorldNormal = MathUtil::PxVec3ToVector3(hit.worldNormal);
		h->Direction = MathUtil::PxVec3ToVector3(hit.dir);
		h->Length = hit.length;

	return h;
}