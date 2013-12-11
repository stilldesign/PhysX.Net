#pragma once

//#include <PxSerialFramework.h>

namespace PhysX
{
	public ref class SerializationRegistry
	{
	private:
		PxSerializationRegistry* _serializationRegistry;

	internal:
		SerializationRegistry(PxSerializationRegistry* serializationRegistry);

	public:


	internal:
		property PxSerializationRegistry* UnmanagedPointer
		{
			PxSerializationRegistry* get();
		}
	};
}