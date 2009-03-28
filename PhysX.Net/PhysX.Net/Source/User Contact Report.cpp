#include "StdAfx.h"

#include "User Contact Report.h"
#include "Scene.h"
#include "Contact Pair.h"

using namespace StillDesign::PhysX;

UserContactReport::UserContactReport()
{
	_contactReport = new InternalUserContactReport( this );
}
UserContactReport::~UserContactReport()
{
	this->!UserContactReport();
}
UserContactReport::!UserContactReport()
{
	SAFE_DELETE( _contactReport );
}

InternalUserContactReport* UserContactReport::UnmanagedPointer::get()
{
	return _contactReport;
}

//

InternalUserContactReport::InternalUserContactReport( UserContactReport^ userContactReport )
{
	_userContactReport = userContactReport;
}
void InternalUserContactReport::onContactNotify( NxContactPair &pair, NxU32 events )
{
	_userContactReport->OnContactNotify( ContactPair::FromUnmanagedPointer( &pair ), (ContactPairFlag)events );
}