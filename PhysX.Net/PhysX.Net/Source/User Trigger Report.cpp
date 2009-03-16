#include "StdAfx.h"

#include "User Trigger Report.h"
#include "Scene.h"
#include "Shape.h"

#include <NxUserContactReport.h> 

using namespace StillDesign::PhysX;

UserTriggerReport::UserTriggerReport()
{
	_internalUserTriggerReport = new InternalUserTriggerReport( this );
}
UserTriggerReport::~UserTriggerReport()
{
	this->!UserTriggerReport();
}
UserTriggerReport::!UserTriggerReport()
{
	SAFE_DELETE( _internalUserTriggerReport );
}

InternalUserTriggerReport* UserTriggerReport::UnmanagedPointer::get()
{
	return _internalUserTriggerReport;
}

//

InternalUserTriggerReport::InternalUserTriggerReport( gcroot<UserTriggerReport^> userTriggerReport )
{
	_userTriggerReport = userTriggerReport;
}

void InternalUserTriggerReport::onTrigger( NxShape &triggerShape, NxShape &otherShape, NxTriggerFlag status )
{
	Shape^ t = ObjectTable::GetObject<Shape^>( (intptr_t)(&triggerShape) );
	Shape^ o = ObjectTable::GetObject<Shape^>( (intptr_t)(&otherShape) );
	
	_userTriggerReport->OnTrigger( t, o, (TriggerFlag)status );
}