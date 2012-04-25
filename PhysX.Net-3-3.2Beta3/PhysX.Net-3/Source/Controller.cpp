#include "StdAfx.h"
#include "Controller.h"
#include "ControllerManager.h"

Controller::Controller(PxController* controller, PhysX::ControllerManager^ owner)
{
	if (controller == NULL)
		throw gcnew ArgumentNullException("controller");
	ThrowIfNull(owner, "owner");

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
	return _controller == NULL;
}

void Controller::Move(Vector3 displacement)
{
	Move(displacement, 0xFFFFFFFF, 0.001f, ControllerFlag::Down | ControllerFlag::Sides | ControllerFlag::Up, 1.0f);
}
void Controller::Move(Vector3 displacement, int activeGroups, float minimumDistance, ControllerFlag collisionFlags, float sharpness)
{
	PxU32 cf;
	_controller->move(MathUtil::Vector3ToPxVec3(displacement), activeGroups, minimumDistance, cf, sharpness);
}

void Controller::ReportSceneChanged()
{
	_controller->reportSceneChanged();
}

PhysX::ControllerManager^ Controller::ControllerManager::get()
{
	return _controllerManager;
}

Vector3 Controller::Position::get()
{
	PxExtendedVec3 p = _controller->getPosition();

	return Vector3((float)p.x, (float)p.y, (float)p.z);
}
void Controller::Position::set(Vector3 value)
{
	PxExtendedVec3 p(value.X, value.Y, value.Z);

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

CCTUpAxis Controller::UpDirection::get()
{
	return ToManagedEnum(CCTUpAxis, _controller->getUpDirection());
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