#include "StdAfx.h"
#include "RigidActor.h"
#include "ControllerBehaviorCallback.h"

ControllerBehaviorCallback::ControllerBehaviorCallback()
{

}
ControllerBehaviorCallback::~ControllerBehaviorCallback()
{
	this->!ControllerBehaviorCallback();
}
ControllerBehaviorCallback::!ControllerBehaviorCallback()
{
	_callback = NULL;
}

ControllerBehaviorFlag ControllerBehaviorCallback::GetBehaviorFlags(Shape^ shape)
{
	ThrowIfNullOrDisposed(shape, "shape");

	PxU32 bf = _callback->getBehaviorFlags(*shape->UnmanagedPointer, *shape->Actor->UnmanagedPointer);

	return (ControllerBehaviorFlag)bf;
}
ControllerBehaviorFlag ControllerBehaviorCallback::GetBehaviorFlags(Controller^ controller)
{
	ThrowIfNullOrDisposed(controller, "controller");

	PxU32 bf = _callback->getBehaviorFlags(*controller->UnmanagedPointer);

	return (ControllerBehaviorFlag)bf;
}
//ControllerBehaviorFlag ControllerBehaviorCallback::GetBehaviorFlags(Obstacle^ obstacle)
//{
//
//}

PxControllerBehaviorCallback* ControllerBehaviorCallback::UnmanagedPointer::get()
{
	return _callback;
}