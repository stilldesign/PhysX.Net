#pragma once


namespace PhysX
{
	public ref class SimpleContact
	{
	protected:
		static void PopulateUnmanaged(SimpleContact^ managed, PxSimpleContact& unmanaged);

	public:
		property Vector3 Contact;
		property float Separation;
	};
};