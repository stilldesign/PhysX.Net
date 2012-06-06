#include "StdAfx.h"
#include "ControllerShapeHit.h"

ControllerShapeHit^ ControllerShapeHit::ToManaged(PxControllerShapeHit hit)
{
	ControllerShapeHit^ h = gcnew ControllerShapeHit();
		h->Shape = ObjectTable::GetObject<PhysX::Shape^>((intptr_t)hit.shape);
		h->TriangleIndex = hit.triangleIndex;

	CctHit::PopulateManaged(&hit, h);

	return h;
}