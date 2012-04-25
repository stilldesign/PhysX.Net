#include "StdAfx.h"
#include "BoxController.h"
#include "ControllerManager.h"

BoxController::BoxController(PxBoxController* boxController, PhysX::ControllerManager^ controllerManager) 
	: Controller(boxController, controllerManager)
{

}

Vector3 BoxController::Extents::get()
{
	return MathUtil::PxVec3ToVector3(this->UnmanagedPointer->getExtents());
}
void BoxController::Extents::set(Vector3 value)
{
	this->UnmanagedPointer->setExtents(MathUtil::Vector3ToPxVec3(value));
}

Vector3 BoxController::Size::get()
{
	return MathUtil::PxVec3ToVector3(this->UnmanagedPointer->getExtents() * 2.0f);
}
void BoxController::Size::set(Vector3 value)
{
	this->UnmanagedPointer->setExtents(MathUtil::Vector3ToPxVec3(value * 0.5f));
}

PxBoxController* BoxController::UnmanagedPointer::get()
{
	return (PxBoxController*)Controller::UnmanagedPointer;
}