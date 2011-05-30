#include "StdAfx.h"
#include "ActorDesc.h"

ActorDesc::ActorDesc(ActorType type)
{
	_type = type;
}

ActorType ActorDesc::Type::get()
{
	return _type;
}

void ActorDesc::PopulateManaged(PxActorDesc& desc)
{
	_type = ToManagedEnum(ActorType, desc.getType());
	this->DominanceGroup = desc.dominanceGroup;
	this->Flags = ToManagedEnum(ActorFlag, desc.actorFlags);
	this->OwnerClient = desc.ownerClient;
	this->ClientBehaviorBits = ToManagedEnum(ClientBehaviorBit, desc.clientBehaviorBits);
	this->Name = Util::ToManagedString(desc.name);
}
void ActorDesc::PopulateUnmanaged(PxActorDesc& desc)
{
	//_type = ToUnmanagedEnum(PxActorType, desc.getType());
	desc.dominanceGroup = this->DominanceGroup;
	desc.actorFlags = ToUnmanagedEnum(PxActorFlag, this->Flags);
	desc.ownerClient = this->OwnerClient;
	desc.clientBehaviorBits = ToUnmanagedEnum(PxClientBehaviorBit, this->ClientBehaviorBits);
	desc.name = Util::ToUnmanagedString(this->Name);
}