#include "StdAfx.h"
#include "Controller.h"
#include "ControllerManager.h"
#include "ControllerFilters.h"
#include "ObstacleContext.h"

Controller::Controller(PxController* controller, PhysX::ControllerManager^ owner)
{
	if (controller == NULL)
		throw gcnew ArgumentNullException("controller");
	ThrowIfNullOrDisposed(owner, "owner");

	_controller = controller;
	_controllerManager = owner;

	ObjectTable::Add((intptr_t)controller, this, owner);
}
Controller::~Controller()
{
	this->!Controller();
}
Controller::!Controller()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_controller->release();
	_controller = NULL;

	UserData = nullptr;

	OnDisposed(this, nullptr);
}
bool Controller::Disposed::get()
{
	return (_controller == NULL);
}

void Controller::Move(Vector3 displacement, TimeSpan elapsedTime)
{
	auto filter = gcnew ControllerFilters();
		filter->ActiveGroups = 0xFFFFFFFF;
		filter->FilterFlags = SceneQueryFilterFlag::Static | SceneQueryFilterFlag::Dynamic;

	Move(displacement, elapsedTime, 0.001f, filter, nullptr);
}
void Controller::Move(Vector3 displacement, TimeSpan elapsedTime, float minimumDistance, ControllerFilters^ filters, [Optional] ObstacleContext^ obstacles)
{
	auto disp = MathUtil::Vector3ToPxVec3(displacement);
	auto et = (float)elapsedTime.TotalSeconds;
	auto f = ControllerFilters::ToUnmanaged(filters);
	auto oc = (obstacles == nullptr ? NULL : obstacles->UnmanagedPointer);

	_controller->move(disp, minimumDistance, et, f, oc);

	// TODO: Not the cleanest way of cleaning up the memory that ControllerFilter allocates
	if (f.mFilterData != NULL)
	{
		delete f.mFilterData;
	}
}

void Controller::InvalidateCache()
{
	_controller->invalidateCache();
}

void Controller::Resize(float height)
{
	_controller->resize(height);
}

PhysX::ControllerManager^ Controller::ControllerManager::get()
{
	return _controllerManager;
}

Vector3 Controller::Position::get()
{
	PxExtendedVec3 p = _controller->getPosition();

	return MathUtil::PxExtendedVec3ToVector3(p);
}
void Controller::Position::set(Vector3 value)
{
	PxExtendedVec3 p = MathUtil::Vector3ToPxExtendedVec3(value);

	_controller->setPosition(p);
}

float Controller::StepOffset::get()
{
	return _controller->getStepOffset();
}
void Controller::StepOffset::set(float value)
{
	_controller->setStepOffset(value);
}

CCTInteractionMode Controller::Interaction::get()
{
	return ToManagedEnum(CCTInteractionMode, _controller->getInteraction());
}
void Controller::Interaction::set(CCTInteractionMode value)
{
	_controller->setInteraction(ToUnmanagedEnum(PxCCTInteractionMode, value));
}

float Controller::ContactOffset::get()
{
	return _controller->getContactOffset();
}

Vector3 Controller::UpDirection::get()
{
	return MathUtil::PxVec3ToVector3(_controller->getUpDirection());
}
void Controller::UpDirection::set(Vector3 value)
{
	_controller->setUpDirection(MathUtil::Vector3ToPxVec3(value));
}

float Controller::SlopeLimit::get()
{
	return _controller->getSlopeLimit();
}

ControllerShapeType Controller::Type::get()
{
	return ToManagedEnum(ControllerShapeType, _controller->getType());
}

PxController* Controller::UnmanagedPointer::get()
{
	return _controller;
}