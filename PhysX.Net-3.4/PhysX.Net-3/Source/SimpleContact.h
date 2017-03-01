#pragma once


namespace PhysX
{
	public ref class SimpleContact
	{
	protected:
		static void PopulateManaged(SimpleContact^ managed, PxContact* unmanaged);
		static void PopulateUnmanaged(SimpleContact^ managed, PxContact* unmanaged);

	public:
		property Vector3 Contact;
		property float Separation;
	};
};