#include "StdAfx.h"
#include "ControllerShapeHit.h"

ControllerShapeHit^ ControllerShapeHit::ToManaged(PxControllerShapeHit hit)
{
	ControllerShapeHit^ h = gcnew ControllerShapeHit();
		h->Shape = ObjectTable::Instance->TryGetObject<PhysX::Shape^>((intptr_t)hit.shape);
		h->TriangleIndex = hit.triangleIndex;

	ControllerHit::PopulateManaged(&hit, h);

	return h;
}