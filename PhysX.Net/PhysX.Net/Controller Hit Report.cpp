#include "StdAfx.h"

#include "Controller Hit Report.h"
#include "Controller Hit.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

UserControllerHitReport::UserControllerHitReport( Scene^ scene, ControllerHitReport^ hitReport ) : NxUserControllerHitReport()
{
	if( hitReport == nullptr )
		throw gcnew ArgumentNullException( "hitReport" );
	if( scene == nullptr )
		throw gcnew ArgumentNullException( "scene" );
	
	_scene = scene;
	
	_hitReport = hitReport;
}
NxControllerAction UserControllerHitReport::onShapeHit( const NxControllerShapeHit &hit )
{
	ControllerShapeHit^ shapeHit = gcnew ControllerShapeHit( hit );
	
	return (NxControllerAction)_hitReport->OnShapeHit( shapeHit );
}
NxControllerAction UserControllerHitReport::onControllerHit( const NxControllersHit &hit )
{
	ControllersHit^ controllerHit = gcnew ControllersHit( hit );
	
	return (NxControllerAction)_hitReport->OnControllerHit( controllerHit );
}

//

ControllerHitReport::ControllerHitReport( Scene^ scene )
{
	_hitReport = new UserControllerHitReport( scene, this );
}
ControllerHitReport::~ControllerHitReport()
{
	this->!ControllerHitReport();
}
ControllerHitReport::!ControllerHitReport()
{
	SAFE_DELETE( _hitReport );
}

UserControllerHitReport* ControllerHitReport::UnmanagedPointer::get()
{
	return _hitReport;
}