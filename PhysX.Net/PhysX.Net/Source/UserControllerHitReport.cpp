#include "StdAfx.h"
#include "UserControllerHitReport.h"
#include "ControllerShapeHit.h"
#include "ControllersHit.h"
#include "ControllerObstacleHit.h"

InternalUserControllerHitReport::InternalUserControllerHitReport(UserControllerHitReport^ hitReport)
	: PxUserControllerHitReport()
{
	ThrowIfNull(hitReport, "hitReport");

	_hitReport = hitReport;
}
void InternalUserControllerHitReport::onShapeHit(const PxControllerShapeHit &hit)
{
	ControllerShapeHit^ shapeHit = ControllerShapeHit::ToManaged(hit);

	_hitReport->OnShapeHit(shapeHit);
}
void InternalUserControllerHitReport::onControllerHit(const PxControllersHit &hit)
{
	ControllersHit^ controllerHit = ControllersHit::ToManaged(hit);

	_hitReport->OnControllerHit(controllerHit);
}
void InternalUserControllerHitReport::onObstacleHit (const PxControllerObstacleHit &hit)
{
	auto obstacleHit = ControllerObstacleHit::ToManaged(hit);

	_hitReport->OnObstacleHit(obstacleHit);
}

//

UserControllerHitReport::UserControllerHitReport()
{
	_hitReport = new InternalUserControllerHitReport(this);
}
UserControllerHitReport::~UserControllerHitReport()
{
	this->!UserControllerHitReport();
}
UserControllerHitReport::!UserControllerHitReport()
{
	SAFE_DELETE(_hitReport);
}

InternalUserControllerHitReport* UserControllerHitReport::UnmanagedPointer::get()
{
	return _hitReport;
}