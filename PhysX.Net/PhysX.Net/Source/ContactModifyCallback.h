#pragma once

namespace PhysX
{
	ref class ContactModifyCallback;
	ref class ContactModifyPair;

	class InternalContactModifyCallback : public PxContactModifyCallback
	{
	private:
		gcroot<PhysX::ContactModifyCallback^> _callback;

	public:
		InternalContactModifyCallback(gcroot<PhysX::ContactModifyCallback^> callback);

		virtual void onContactModify(PxContactModifyPair* const pairs, PxU32 count);
	};

	//

	public ref class ContactModifyCallback abstract
	{
	private:
		InternalContactModifyCallback* _unmanaged;

	public:
		ContactModifyCallback();
	protected:
		~ContactModifyCallback();
	public:
		!ContactModifyCallback();

		virtual void OnContactModify(array<ContactModifyPair^>^ pairs) abstract;

	internal:
		property InternalContactModifyCallback* UnmanagedPointer
		{
			InternalContactModifyCallback* get();
		}
	};
};