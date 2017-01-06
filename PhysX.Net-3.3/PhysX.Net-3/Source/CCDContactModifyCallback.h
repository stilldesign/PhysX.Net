#pragma once

#include <PxContactModifyCallback.h>

namespace PhysX
{
	ref class CCDContactModifyCallback;
	ref class ContactModifyPair;
};

class InternalCCDContactModifyCallback : public PxCCDContactModifyCallback
{
private:
	gcroot<PhysX::CCDContactModifyCallback^> _managed;

public:
	InternalCCDContactModifyCallback(gcroot<PhysX::CCDContactModifyCallback^> managed);

	virtual void onCCDContactModify(PxContactModifyPair* const pairs, PxU32 count);
};

namespace PhysX
{
	public ref class CCDContactModifyCallback
	{
	private:
		InternalCCDContactModifyCallback* _unmanaged;

	public:
		CCDContactModifyCallback();
		~CCDContactModifyCallback();
	protected:
		!CCDContactModifyCallback();

	public:
		virtual void OnCCDContactModify(array<ContactModifyPair^>^ pairs) abstract;

	internal:
		property InternalCCDContactModifyCallback* UnmanagedPointer
		{
			InternalCCDContactModifyCallback* get();
		}
	};
};