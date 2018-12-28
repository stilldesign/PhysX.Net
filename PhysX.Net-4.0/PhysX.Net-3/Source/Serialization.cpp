#include "StdAfx.h"
#include "Serialization.h"
#include "Physics.h"
#include "Scene.h"
#include "SerializationRegistry.h"
#include "Collection.h"
#include "Cooking.h"

bool Serialization::SerializeCollectionToXml(Stream^ outputStream, Collection^ collection, SerializationRegistry^ sr, [Optional] Cooking^ cooking, [Optional] Collection^ externalRefs, [Optional] Nullable<XmlParserOptions> parserOptions)
{
	ThrowIfNull(outputStream, "outputStream");
	if (!outputStream->CanWrite)
		throw gcnew ArgumentException("Cannot write to stream", "outputStream");

	PxDefaultMemoryOutputStream s;

	bool result = PxSerialization::serializeCollectionToXml
	(
		s,
		*collection->UnmanagedPointer,
		*sr->UnmanagedPointer,
		(cooking == nullptr ? NULL : cooking->UnmanagedPointer),
		(externalRefs == nullptr ? NULL : externalRefs->UnmanagedPointer),
		(parserOptions.HasValue ? &XmlParserOptions::ToUnmanaged(parserOptions.Value) : NULL)
	);

	if (!result)
		return false;

	PxU32 size = s.getSize();

	if (size <= 0)
		return false;

	PxU8* data = s.getData();

	array<Byte>^ buffer = gcnew array<Byte>(size);
	pin_ptr<Byte> b = &buffer[0];
	memcpy_s(b, size, (void*)data, size);

	outputStream->Write(buffer, 0, size);

	return true;
}
 
bool Serialization::SerializeCollectionToBinary (Stream^ outputStream, Collection^ collection, SerializationRegistry^ sr, [Optional] Collection^ externalRefs, [Optional] Nullable<bool> exportNames)
{
	ThrowIfNull(outputStream, "outputStream");
	if (!outputStream->CanWrite)
		throw gcnew ArgumentException("Cannot write to stream", "outputStream");

	PxDefaultMemoryOutputStream s;

	bool result = PxSerialization::serializeCollectionToBinary
	(
		s,
		*collection->UnmanagedPointer,
		*sr->UnmanagedPointer,
		(externalRefs == nullptr ? NULL : externalRefs->UnmanagedPointer),
		exportNames.GetValueOrDefault(false)
	);

	if (!result)
		return false;

	PxU32 size = s.getSize();

	if (size <= 0)
		return false;

	PxU8* data = s.getData();

	array<Byte>^ buffer = gcnew array<Byte>(size);
	pin_ptr<Byte> b = &buffer[0];
	memcpy_s(b, size, (void*)data, size);

	outputStream->Write(buffer, 0, size);

	return true;
}

SerializationRegistry^ Serialization::CreateSerializationRegistry(Physics^ physics)
{
	ThrowIfNullOrDisposed(physics, "physics");

	PxSerializationRegistry* sr = PxSerialization::createSerializationRegistry(*physics->UnmanagedPointer);

	return gcnew SerializationRegistry(sr);
}