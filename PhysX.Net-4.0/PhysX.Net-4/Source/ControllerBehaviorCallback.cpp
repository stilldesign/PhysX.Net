#include "StdAfx.h"
#include "RigidActor.h"
#include "ControllerBehaviorCallback.h"
#include "Obstacle.h"

ControllerBehaviorCallback::ControllerBehaviorCallback()
{
	_internalCallback = new InternalControllerBehaviorCallback(this);

	ObjectTable::Instance->Add((intptr_t)_internalCallback, this, nullptr);
}
ControllerBehaviorCallback::~ControllerBehaviorCallback()
{
	this->!ControllerBehaviorCallback();
}
ControllerBehaviorCallback::!ControllerBehaviorCallback()
{
	SAFE_DELETE(_internalCallback);
}

bool ControllerBehaviorCallback::Disposed::get()
{
	return _internalCallback == nullptr;
}

InternalControllerBehaviorCallback* ControllerBehaviorCallback::UnmanagedPointer::get()
{
	return _internalCallback;
}

//

InternalControllerBehaviorCallback::InternalControllerBehaviorCallback(gcroot<ControllerBehaviorCallback^> managed)
{
	_managed = managed;
}

PxControllerBehaviorFlags InternalControllerBehaviorCallback::getBehaviorFlags(const PxShape &shape, const PxActor &actor)
{
	auto s = ObjectTable::Instance->TryGetObject<Shape^>((intptr_t)&shape);
	auto a = ObjectTable::Instance->TryGetObject<Actor^>((intptr_t)&actor);

	auto cbf = _managed->GetBehaviorFlags(s, a);

	return ToUnmanagedEnum(PxControllerBehaviorFlag, cbf);
}
PxControllerBehaviorFlags InternalControllerBehaviorCallback::getBehaviorFlags(const PxController &controller)
{
	auto c = ObjectTable::Instance->TryGetObject<Controller^>((intptr_t)&controller);

	auto cbf = _managed->GetBehaviorFlags(c);

	return ToUnmanagedEnum(PxControllerBehaviorFlag, cbf);
}
PxControllerBehaviorFlags InternalControllerBehaviorCallback::getBehaviorFlags(const PxObstacle &obstacle)
{
	auto o = ObjectTable::Instance->TryGetObject<Obstacle^>((intptr_t)&obstacle);

	auto cbf = _managed->GetBehaviorFlags(o);

	return ToUnmanagedEnum(PxControllerBehaviorFlag, cbf);
}