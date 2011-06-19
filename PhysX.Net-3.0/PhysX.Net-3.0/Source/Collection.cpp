#include "StdAfx.h"
#include "Collection.h"
#include "Physics.h"
#include "InternalSerialStream.h"
#include "Scene.h"
#include <PxExtensionsAPI.h>
#include <PxSerialFramework.h> 

Collection::Collection(PxCollection* collection, PhysX::Physics^ owner)
{
	if (collection == NULL)
		throw gcnew ArgumentNullException("collection");
	ThrowIfNullOrDisposed(owner, "owner");

	_collection = collection;
	_physics = owner;

	ObjectTable::Add((intptr_t)collection, this, owner);
}
Collection::~Collection()
{
	this->!Collection();
}
Collection::!Collection()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	this->Physics->UnmanagedPointer->releaseCollection(_collection);
	_collection = NULL;

	_physics = nullptr;

	OnDisposed(this, nullptr);
}

bool Collection::Disposed::get()
{
	return _collection == NULL;
}

void Collection::Serialize(System::IO::Stream^ stream)
{
	ThrowIfNull(stream, "stream");
	if (!stream->CanWrite)
		throw gcnew ArgumentException("Cannot write to stream", "stream");

	InternalSerialStream s;
	InternalMemoryStream* m = s.GetMemoryStream();

	_collection->serialize(s);

	int n = m->getMemorySize();

	if (n <= 0)
		return;

	m->ResetSeek();

	const PxU8* data = m->GetMemory();

	array<Byte>^ buffer = gcnew array<Byte>(n);
	pin_ptr<Byte> b = &buffer[0];
	memcpy_s(b, n, (void*)data, n);

	stream->Write(buffer, 0, n);
}
bool Collection::Deserialize(System::IO::Stream^ stream)
{
	ThrowIfNull(stream, "stream");
	if (!stream->CanRead)
		throw gcnew ArgumentException("Cannot read from stream", "stream");

	int n = (int)stream->Length;

	if (n <= 0)
		return false;

	// Read the entire contents of the stream to a managed byte array
	array<Byte>^ data = gcnew array<Byte>(n);
	stream->Read(data, 0, n);
	// Pin the first element
	pin_ptr<Byte> d = &data[0];

	// Allocate a (16 byte) aligned block of memory and copy in the stream data
	void* j = _aligned_malloc(n, 128);
	memcpy_s(j, n, d, n);
	
	// Deserialize
	bool result = _collection->deserialize(j, NULL, NULL);

	// Free up the unmanaged memory
	_aligned_free(j);

	return result;
}

int Collection::GetNumberOfObjects()
{
	return _collection->getNbObjects();
}

//

void Collection::CollectPhysicsForExport(PhysX::Physics^ physics)
{
	ThrowIfNullOrDisposed(physics, "physics");

	PxCollectForExportSDK(*physics->UnmanagedPointer, *_collection);
}
void Collection::CollectSceneForExport(Scene^ scene)
{
	ThrowIfNullOrDisposed(scene, "scene");

	PxCollectForExportScene(*scene->UnmanagedPointer, *_collection);
}

//

PhysX::Physics^ Collection::Physics::get()
{
	return _physics;
}

PxCollection* Collection::UnmanagedPointer::get()
{
	return _collection;
}