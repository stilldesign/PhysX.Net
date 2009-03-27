#include "StdAfx.h"

#include "User Controller Hit Report.h"
#include "Controller Shape Hit.h"
#include "Scene.h"
#include "Controllers Hit.h"

using namespace StillDesign::PhysX;

InternalUserControllerHitReport::InternalUserControllerHitReport( UserControllerHitReport^ hitReport ) : NxUserControllerHitReport()
{
	ThrowIfNull( hitReport, "hitReport" );
	
	_hitReport = hitReport;
}
NxControllerAction InternalUserControllerHitReport::onShapeHit( const NxControllerShapeHit &hit )
{
	ControllerShapeHit^ shapeHit = gcnew ControllerShapeHit( hit );
	
	return (NxControllerAction)_hitReport->OnShapeHit( shapeHit );
}
NxControllerAction InternalUserControllerHitReport::onControllerHit( const NxControllersHit &hit )
{
	ControllersHit^ controllerHit = gcnew ControllersHit( hit );
	
	return (NxControllerAction)_hitReport->OnControllerHit( controllerHit );
}

//

UserControllerHitReport::UserControllerHitReport()
{
	_hitReport = new InternalUserControllerHitReport( this );
}
UserControllerHitReport::~UserControllerHitReport()
{
	this->!UserControllerHitReport();
}
UserControllerHitReport::!UserControllerHitReport()
{
	SAFE_DELETE( _hitReport );
}

InternalUserControllerHitReport* UserControllerHitReport::UnmanagedPointer::get()
{
	return _hitReport;
}