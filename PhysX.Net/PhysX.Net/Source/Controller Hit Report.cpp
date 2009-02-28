#include "StdAfx.h"

#include "Controller Hit Report.h"
#include "Controller Shape Hit.h"
#include "Scene.h"
#include "Controllers Hit.h"

using namespace StillDesign::PhysX;

UserControllerHitReport::UserControllerHitReport( ControllerHitReport^ hitReport ) : NxUserControllerHitReport()
{
	ThrowIfNull( hitReport, "hitReport" );
	
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

ControllerHitReport::ControllerHitReport()
{
	_hitReport = new UserControllerHitReport( this );
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