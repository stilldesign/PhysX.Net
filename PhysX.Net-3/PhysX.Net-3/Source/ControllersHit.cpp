#include "StdAfx.h"
#include "ControllersHit.h"
#include "Controller.h"

PxControllersHit ControllersHit::ToUnmanaged(ControllersHit^ hit)
{
	ThrowIfNull(hit, "hit");

	PxControllersHit h;
		h.controller = (hit->Controller == nullptr ? NULL : hit->Controller->UnmanagedPointer);
		h.other = (hit->Other == nullptr ? NULL : hit->Other->UnmanagedPointer);

	return h;
}
ControllersHit^ ControllersHit::ToManaged(PxControllersHit hit)
{
	ControllersHit^ h = gcnew ControllersHit();
		h->Controller = ObjectTable::GetObject<PhysX::Controller^>((intptr_t)hit.controller);
		h->Other = ObjectTable::GetObject<PhysX::Controller^>((intptr_t)hit.other);

	return h;
}