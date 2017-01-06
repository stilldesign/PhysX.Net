#include "StdAfx.h"
#include "CCDContactModifyCallback.h"
#include "ContactModifyPair.h"

InternalCCDContactModifyCallback::InternalCCDContactModifyCallback(gcroot<PhysX::CCDContactModifyCallback^> managed)
{
	_managed = managed;
}
void InternalCCDContactModifyCallback::onCCDContactModify(PxContactModifyPair* const pairs, PxU32 count)
{
	// Copy the pairs to managed objects
	auto m = gcnew array<ContactModifyPair^>(count);

	for (size_t i = 0; i < count; i++)
	{
		m[i] = ContactModifyPair::ToManaged(&pairs[i]);
	}

	// Allow the user to modify the array
	_managed->OnCCDContactModify(m);

	// Copy them back to the original unmanaged objects
	for (size_t i = 0; i < count; i++)
	{
		ContactModifyPair::ToUnmanaged(m[i], pairs[i]);
	}
}

//

CCDContactModifyCallback::CCDContactModifyCallback()
{
	_unmanaged = new InternalCCDContactModifyCallback(this);
}
CCDContactModifyCallback::~CCDContactModifyCallback()
{
	this->!CCDContactModifyCallback();
}
CCDContactModifyCallback::!CCDContactModifyCallback()
{
	SAFE_DELETE(_unmanaged);
}

InternalCCDContactModifyCallback* CCDContactModifyCallback::UnmanagedPointer::get()
{
	return _unmanaged;
}