#include "StdAfx.h"

#include "Raycast Reporting.h"

using namespace StillDesign::PhysX;

UserRaycastReport::UserRaycastReport()
{
	_rayCastReport = new InternalUserRaycastReport( this );
}
UserRaycastReport::~UserRaycastReport()
{
	this->!UserRaycastReport();
}
UserRaycastReport::!UserRaycastReport()
{
	SAFE_DELETE( _rayCastReport );
}

InternalUserRaycastReport* UserRaycastReport::UnmanagedPointer::get()
{
	return _rayCastReport;
}

//

InternalUserRaycastReport::InternalUserRaycastReport( UserRaycastReport^ rayCastReport )
{
	_rayCastReport = rayCastReport;
}

bool InternalUserRaycastReport::onHit( const NxRaycastHit &hits )
{
	return _rayCastReport->OnHit( (RaycastHit^)((NxRaycastHit)hits) );
}