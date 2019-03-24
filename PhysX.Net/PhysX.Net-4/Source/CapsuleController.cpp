#include "StdAfx.h"
#include "CapsuleController.h"

CapsuleController::CapsuleController(PxCapsuleController* capsuleController, PhysX::ControllerManager^ controllerManager) 
	: Controller(capsuleController, controllerManager)
{

}

float CapsuleController::Radius::get()
{
	return this->UnmanagedPointer->getRadius();
}
void CapsuleController::Radius::set(float value)
{
	this->UnmanagedPointer->setRadius(value);
}

float CapsuleController::Height::get()
{
	return this->UnmanagedPointer->getHeight();
}
void CapsuleController::Height::set(float value)
{
	this->UnmanagedPointer->setHeight(value);
}

CapsuleClimbingMode CapsuleController::ClimbingMode::get()
{
	return ToManagedEnum(CapsuleClimbingMode, this->UnmanagedPointer->getClimbingMode());
}
void CapsuleController::ClimbingMode::set(CapsuleClimbingMode value)
{
	this->UnmanagedPointer->setClimbingMode(ToUnmanagedEnum(PxCapsuleClimbingMode, value));
}

PxCapsuleController* CapsuleController::UnmanagedPointer::get()
{
	return (PxCapsuleController*)Controller::UnmanagedPointer;
}