#include "StdAfx.h"
#include "QueryCache.h"
#include "Shape.h"
#include "RigidActor.h"

QueryCache^ QueryCache::ToManaged(PxQueryCache unmanaged)
{
	auto managed = gcnew QueryCache();
		managed->Shape = ObjectTable::Instance->GetObject<PhysX::Shape^>((intptr_t)unmanaged.shape);
		managed->Actor = ObjectTable::Instance->GetObject<PhysX::RigidActor^>((intptr_t)unmanaged.actor);
		managed->FaceIndex = unmanaged.faceIndex;

	return managed;
}
PxQueryCache QueryCache::ToUnmanaged(QueryCache^ managed)
{
	ThrowIfNull(managed, "managed");

	PxQueryCache unmanaged;
		unmanaged.shape = (managed->Shape == nullptr ? NULL : managed->Shape->UnmanagedPointer);
		unmanaged.actor = (managed->Actor == nullptr ? NULL : managed->Actor->UnmanagedPointer);
		unmanaged.faceIndex = managed->FaceIndex;

	return unmanaged;
}