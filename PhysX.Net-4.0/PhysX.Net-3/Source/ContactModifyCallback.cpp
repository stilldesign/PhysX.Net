#include "StdAfx.h"
#include "ContactModifyPair.h"
#include "ContactModifyCallback.h"

InternalContactModifyCallback::InternalContactModifyCallback(gcroot<ContactModifyCallback^> callback)
{
	_callback = callback;
}

void InternalContactModifyCallback::onContactModify(PxContactModifyPair* const pairs, PxU32 count)
{
	// To managed
	auto managed = gcnew array<ContactModifyPair^>(count);

	for (unsigned int i = 0; i < count; i++)
	{
		managed[i] = ContactModifyPair::ToManaged(&pairs[i]);
	}

	_callback->OnContactModify(managed);

	// Back to unmanaged
	for (unsigned int i = 0; i < count; i++)
	{
		pairs[i] = ContactModifyPair::ToUnmanaged(managed[i]);
	}
}

//

ContactModifyCallback::ContactModifyCallback()
{
	_unmanaged = new InternalContactModifyCallback(this);
}
ContactModifyCallback::~ContactModifyCallback()
{
	this->!ContactModifyCallback();
}
ContactModifyCallback::!ContactModifyCallback()
{
	SAFE_DELETE(_unmanaged);
}

InternalContactModifyCallback* ContactModifyCallback::UnmanagedPointer::get()
{
	return _unmanaged;
}