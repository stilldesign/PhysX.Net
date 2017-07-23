#include "StdAfx.h"
#include "ControllersHit.h"
#include "Controller.h"

//PxControllersHit ControllersHit::ToUnmanaged(ControllersHit^ hit)
//{
//	ThrowIfNull(hit, "hit");
//
//	PxControllersHit h;
//		h.other = (hit->Other == nullptr ? NULL : hit->Other->UnmanagedPointer);
//	
//	return h;
//}
ControllersHit^ ControllersHit::ToManaged(PxControllersHit hit)
{
	ControllersHit^ h = gcnew ControllersHit();
		h->Other = (hit.other == NULL ? nullptr : ObjectTable::Instance->GetObject<PhysX::Controller^>((intptr_t)hit.other));

	ControllerHit::PopulateManaged(&hit, h);

	return h;
}