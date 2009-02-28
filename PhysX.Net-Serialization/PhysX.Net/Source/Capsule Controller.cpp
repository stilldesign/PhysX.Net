#include "StdAfx.h"

#include "Capsule Controller.h"
#include "Capsule Controller Description.h"
#include "Controller Manager.h"
#include "Controller.h"
#include "Controller Description.h"
#include "Enums.h"
#include "Scene.h"
#include "Actor.h"

#include <NxCapsuleController.h> 

using namespace StillDesign::PhysX;

CapsuleController::CapsuleController( NxCapsuleController* capsuleController, StillDesign::PhysX::ControllerManager^ manager ) : Controller( capsuleController, manager )
{
	
}

void CapsuleController::SetStepOffset( float stepOffset )
{
	this->UnmanagedPointer->setStepOffset( stepOffset );
}

float CapsuleController::Radius::get()
{
	return this->UnmanagedPointer->getRadius();
}
void CapsuleController::Radius::set( float value )
{
	this->UnmanagedPointer->setRadius( value );
}

float CapsuleController::Height::get()
{
	return this->UnmanagedPointer->getHeight();
}
void CapsuleController::Height::set( float value )
{
	this->UnmanagedPointer->setHeight( value );
}

CapsuleClimbingMode CapsuleController::ClimbingMode::get()
{
	return (CapsuleClimbingMode)this->UnmanagedPointer->getClimbingMode();
}
void CapsuleController::ClimbingMode::set( CapsuleClimbingMode value )
{
	this->UnmanagedPointer->setClimbingMode( (NxCapsuleClimbingMode)value );
}

NxCapsuleController* CapsuleController::UnmanagedPointer::get()
{
	return (NxCapsuleController*)Controller::UnmanagedPointer;
}