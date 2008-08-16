#include "StdAfx.h"

#include "Box Controller.h"
#include "Box Controller Description.h"

#include "Controller Manager.h"
#include "Controller.h"
#include "Controller Description.h"
#include "Enums.h"
#include "Scene.h"
#include "Actor.h"
#include "Base Shape.h"
#include "Actor.h"

#include <NxShape.h> 

using namespace StillDesign::PhysX;

BoxController::BoxController( NxBoxController* boxController, StillDesign::PhysX::ControllerManager^ manager ) : Controller( boxController, manager )
{
	
}

Vector3 BoxController::Extents::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getExtents() );
}
void BoxController::Extents::set( Vector3 value )
{
	this->UnmanagedPointer->setExtents( Math::Vector3ToNxVec3( value ) );
}

Vector3 BoxController::Size::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getExtents() * 2.0f );
}
void BoxController::Size::set( Vector3 value )
{
	this->UnmanagedPointer->setExtents( Math::Vector3ToNxVec3( value* 0.5f ) );
}

void BoxController::StepOffset::set( float value )
{
	this->UnmanagedPointer->setStepOffset( value );
}

NxBoxController* BoxController::UnmanagedPointer::get()
{
	return (NxBoxController*)Controller::UnmanagedPointer;
}