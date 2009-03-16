#include "StdAfx.h"

#include "Controller.h"
#include "Controller Manager.h"
#include "Controller Description.h"
#include "Actor.h"
#include "Controller Move Result.h"
#include "Scene.h"

#include <NxController.h> 

using namespace StillDesign::PhysX;

StillDesign::PhysX::Controller::Controller( NxController* controller, ControllerManager^ manager )
{
	Debug::Assert( controller != NULL );
	Debug::Assert( manager != nullptr );
	
	ObjectTable::Add( (intptr_t)controller, this );
	
	_controller = controller;
	
	_manager = manager;
	
	_actor = gcnew StillDesign::PhysX::Actor( controller->getActor() );
	//GC::SuppressFinalize( _actor );
}
StillDesign::PhysX::Controller::~Controller()
{
	this->!Controller();
}
StillDesign::PhysX::Controller::!Controller()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_manager->UnmanagedPointer->releaseController( *_controller );
	
	// Because the controller will be disposing of the actor (and thus its internal shape) they should not be released by the finalizer code (they already have been).
	// The managed classes should still pass through the normal garbage collection route.
	_actor->UnmanagedPointer = NULL;
	_actor->Shapes[ 0 ]->UnmanagedPointer = NULL;
	//GC::ReRegisterForFinalize( _actor );
	
	_controller = NULL;
	
	_manager = nullptr;
	_actor = nullptr;
	_userData = nullptr;
	
	OnDisposed( this, nullptr );
}
bool StillDesign::PhysX::Controller::IsDisposed::get()
{
	return ( _controller == NULL );
}

ControllerMoveResult^ StillDesign::PhysX::Controller::Move( float displacementX, float displacementY, float displacementZ )
{
	return Move( Vector3( displacementX, displacementY, displacementZ ) );
}
ControllerMoveResult^ StillDesign::PhysX::Controller::Move( Vector3 displacement )
{
	return Move( displacement, 0xFFFFFFFF, 0.0001f, 1.0f );
}
ControllerMoveResult^ StillDesign::PhysX::Controller::Move( Vector3 displacement, unsigned int activeGroups, float minimumDistance, float sharpness )
{
	unsigned int collisionFlag = 0;
	_controller->move( NxVec3( displacement.X, displacement.Y, displacement.Z ), activeGroups, minimumDistance, collisionFlag, sharpness );
	
	_manager->UnmanagedPointer->updateControllers();
	
	return gcnew ControllerMoveResult( (ControllerCollisionFlag)collisionFlag );
}

void StillDesign::PhysX::Controller::ReportSceneChanged()
{
	_controller->reportSceneChanged();
}

void StillDesign::PhysX::Controller::SetStepOffset( float offset )
{
	_controller->setStepOffset( offset );
}
void StillDesign::PhysX::Controller::SetCollisionEnabled( bool value )
{
	_controller->setCollision( value );
}

StillDesign::PhysX::ControllerManager^ StillDesign::PhysX::Controller::Manager::get()
{
	return _manager;
}

String^ StillDesign::PhysX::Controller::Name::get()
{
	return _name;
}
void StillDesign::PhysX::Controller::Name::set( String^ value )
{
	_name = value;
}

StillDesign::PhysX::Actor^ StillDesign::PhysX::Controller::Actor::get()
{
	return _actor;
}

CCTInteractionFlag StillDesign::PhysX::Controller::InteractionFlag::get()
{
	return (CCTInteractionFlag)_controller->getInteraction();
}
void StillDesign::PhysX::Controller::InteractionFlag::set( CCTInteractionFlag value )
{
	return _controller->setInteraction( (NxCCTInteractionFlag)value );
}

Vector3 StillDesign::PhysX::Controller::Position::get()
{
	NxExtendedVec3 pos = _controller->getPosition();
	
	return Vector3( (float)pos.x, (float)pos.y, (float)pos.z );
}
void StillDesign::PhysX::Controller::Position::set( Vector3 value )
{
	_controller->setPosition( NxExtendedVec3( (double)value.X, (double)value.Y, (double)value.Z ) );
}

Vector3 StillDesign::PhysX::Controller::FilteredPosition::get()
{
	NxExtendedVec3 pos = _controller->getFilteredPosition();
	
	return Vector3( (float)pos.x, (float)pos.y, (float)pos.z );
}

Vector3 StillDesign::PhysX::Controller::DebugPosition::get()
{
	NxExtendedVec3 pos = _controller->getDebugPosition();
	
	return Vector3( (float)pos.x, (float)pos.y, (float)pos.z );
}

ControllerType StillDesign::PhysX::Controller::Type::get()
{
	return (ControllerType)_controller->getType();
}

Object^ StillDesign::PhysX::Controller::UserData::get()
{
	return _userData;
}
void StillDesign::PhysX::Controller::UserData::set( Object^ value )
{
	_userData = value;
}

NxController* StillDesign::PhysX::Controller::UnmanagedPointer::get()
{
	return _controller;
}