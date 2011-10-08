#include "StdAfx.h"
#include "Foundation.h"
#include "Physics.h"

Foundation::Foundation(PxFoundation* foundation, PhysX::Physics^ owner)
{
	if (foundation == NULL)
		throw gcnew ArgumentNullException("foundation");
	ThrowIfNullOrDisposed(owner, "owner");

	_foundation = foundation;

	ObjectTable::Add((intptr_t)foundation, this, owner);
}
Foundation::~Foundation()
{
	this->!Foundation();
}
Foundation::!Foundation()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	// The native PxFoundation object is not created by us, it is a simple member variable
	// on the PxPhysics object, therefore do not delete/free it
	_foundation = NULL;

	OnDisposed(this, nullptr);
}

bool Foundation::Disposed::get()
{
	return _foundation == NULL;
}

PxFoundation* Foundation::UnmanagedPointer::get()
{
	return _foundation;
}