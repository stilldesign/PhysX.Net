#include "StdAfx.h"
#include "BroadPhaseCallback.h"
#include "Shape.h"
#include "Actor.h"
#include "Aggregate.h"

using namespace PhysX;

InternalBroadPhaseCallback::InternalBroadPhaseCallback(gcroot<PhysX::BroadPhaseCallback^> managed)
{
	_managed = managed;
}
void InternalBroadPhaseCallback::onObjectOutOfBounds(PxShape &shape, PxActor &actor)
{
	auto s = ObjectTable::Instance->TryGetObject<Shape^>((intptr_t)&shape);
	auto a = ObjectTable::Instance->TryGetObject<Actor^>((intptr_t)&actor);

	_managed->OnObjectOutOfBounds(s, a);
}
void InternalBroadPhaseCallback::onObjectOutOfBounds(PxAggregate &aggregate)
{
	auto a = ObjectTable::Instance->TryGetObject<Aggregate^>((intptr_t)&aggregate);

	_managed->OnObjectOutOfBounds(a);
}

//

BroadPhaseCallback::BroadPhaseCallback()
{
	_internal = new InternalBroadPhaseCallback(this);
}
BroadPhaseCallback::~BroadPhaseCallback()
{
	this->!BroadPhaseCallback();
}
BroadPhaseCallback::!BroadPhaseCallback()
{
	SAFE_DELETE(_internal);
}

PxBroadPhaseCallback* BroadPhaseCallback::UnmanagedPointer::get()
{
	return _internal;
}