#include "StdAfx.h"
#include "SerializationRegistry.h"

SerializationRegistry::SerializationRegistry(PxSerializationRegistry* serializationRegistry)
{
	if (serializationRegistry == NULL)
		throw gcnew ArgumentNullException("serializationRegistry");

	_serializationRegistry = serializationRegistry;
}

PxSerializationRegistry* SerializationRegistry::UnmanagedPointer::get()
{
	return _serializationRegistry;
}