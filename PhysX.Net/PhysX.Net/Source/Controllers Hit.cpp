#include "StdAfx.h"

#include "Controllers Hit.h"
#include "Controller.h"

using namespace StillDesign::PhysX;

ControllersHit::ControllersHit()
{
	_controllersHit = new NxControllersHit();
}
ControllersHit::ControllersHit( const NxControllersHit controllersHit )
{
	_controllersHit = new NxControllersHit( controllersHit );
	
	if( controllersHit.controller != NULL )
		_controller = ObjectTable::GetObject<StillDesign::PhysX::Controller^>( (intptr_t)controllersHit.controller );
	
	if( controllersHit.other != NULL )
		_other = ObjectTable::GetObject<StillDesign::PhysX::Controller^>( (intptr_t)controllersHit.other );
}
ControllersHit::~ControllersHit()
{
	this->!ControllersHit();
}
ControllersHit::!ControllersHit()
{
	SAFE_DELETE( _controllersHit );
	
	_controller = nullptr;
	_other = nullptr;
}

StillDesign::PhysX::Controller^ ControllersHit::Controller::get()
{
	return _controller;
}
StillDesign::PhysX::Controller^ ControllersHit::Other::get()
{
	return _other;
}

NxControllersHit* ControllersHit::UnmanagedPointer::get()
{
	return _controllersHit;
}