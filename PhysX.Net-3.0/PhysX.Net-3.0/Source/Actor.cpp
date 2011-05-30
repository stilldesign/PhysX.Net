#include "StdAfx.h"
#include "Actor.h"
#include "Physics.h"

using namespace PhysX;

Actor::Actor(PxActor* actor, PhysX::Physics^ owner)
{
	if (actor == NULL)
		throw gcnew ArgumentNullException("actor");
	ThrowIfNullOrDisposed(owner, "owner");

	_actor = actor;
	_physics = owner;

	ObjectTable::Add((intptr_t)actor, this, owner);
}
Actor::~Actor()
{
	this->!Actor();
}
Actor::!Actor()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_actor->release();
	_actor = NULL;

	OnDisposed(this, nullptr);
}

bool Actor::Disposed::get()
{
	return _actor == NULL;
}

//

PhysX::Physics^ Actor::Physics::get()
{
	return _physics;
}

ActorType Actor::Type::get()
{
	return ToManagedEnum(ActorType, _actor->getType());
}

Bounds3 Actor::WorldBounds::get()
{
	return Bounds3::FromUnmanaged(_actor->getWorldBounds());
}

ActorFlag Actor::Flags::get()
{
	return ToManagedEnum(ActorFlag, _actor->getActorFlags());
}
void Actor::Flags::set(ActorFlag value)
{
	_actor->setActorFlags((PxActorFlags)(PxU32)value);
}

PxActor* Actor::UnmanagedPointer::get()
{
	return _actor;
}