#include "StdAfx.h"
#include "BoxController.h"
#include "ControllerManager.h"

BoxController::BoxController(PxBoxController* boxController, PhysX::ControllerManager^ controllerManager) 
	: Controller(boxController, controllerManager)
{

}

Vector3 BoxController::Extents::get()
{
	float x = this->UnmanagedPointer->getHalfSideExtent();
	float y = this->UnmanagedPointer->getHalfHeight();
	float z = this->UnmanagedPointer->getHalfForwardExtent();

	return Vector3(x, y, z);
}
void BoxController::Extents::set(Vector3 value)
{
	this->UnmanagedPointer->setHalfSideExtent(value.X);
	this->UnmanagedPointer->setHalfHeight(value.Y);
	this->UnmanagedPointer->setHalfForwardExtent(value.Z);
}

Vector3 BoxController::Size::get()
{
	return Extents * 2;
}
void BoxController::Size::set(Vector3 value)
{
	Extents = value * 0.5f;
}

float BoxController::HalfHeight::get()
{
	return this->UnmanagedPointer->getHalfHeight();
}
void BoxController::HalfHeight::set(float value)
{
	this->UnmanagedPointer->setHalfHeight(value);
}

float BoxController::HalfSideExtent::get()
{
	return this->UnmanagedPointer->getHalfSideExtent();
}
void BoxController::HalfSideExtent::set(float value)
{
	this->UnmanagedPointer->setHalfSideExtent(value);
}

float BoxController::HalfForwardExtent::get()
{
	return this->UnmanagedPointer->getHalfForwardExtent();
}
void BoxController::HalfForwardExtent::set(float value)
{
	this->UnmanagedPointer->setHalfForwardExtent(value);
}

PxBoxController* BoxController::UnmanagedPointer::get()
{
	return (PxBoxController*)Controller::UnmanagedPointer;
}