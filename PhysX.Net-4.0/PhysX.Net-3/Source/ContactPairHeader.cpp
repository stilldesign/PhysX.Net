#include "StdAfx.h"
#include "ContactPairHeader.h"

ContactPairHeader^ ContactPairHeader::ToManaged(PxContactPairHeader unmanaged)
{
	auto managed = gcnew ContactPairHeader();

	managed->Actor0 = ObjectTable::Instance->TryGetObject<RigidActor^>((intptr_t)unmanaged.actors[0]);
	managed->Actor1 = ObjectTable::Instance->TryGetObject<RigidActor^>((intptr_t)unmanaged.actors[1]);

	managed->ExtraData = (unmanaged.extraDataStream == NULL) ?
		nullptr :
		Util::AsManagedArray<Byte>(unmanaged.extraDataStream, unmanaged.extraDataStreamSize);

	managed->Flags = ToManagedEnum(ContactPairHeaderFlag, unmanaged.flags);

	return managed;
}