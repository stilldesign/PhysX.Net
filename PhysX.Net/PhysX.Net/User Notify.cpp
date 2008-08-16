#include "StdAfx.h"

#include "User Notify.h"
#include "Scene.h"
#include "Joint.h"
#include "Actor.h"

using namespace StillDesign::PhysX;

UserNotify::UserNotify()
{
	_userNotify = new InternalUserNotify( this );
}
UserNotify::~UserNotify()
{
	this->!UserNotify();
}
UserNotify::!UserNotify()
{
	SAFE_DELETE( _userNotify );
}

InternalUserNotify* UserNotify::UnmanagedPointer::get()
{
	return _userNotify;
}

//

InternalUserNotify::InternalUserNotify( gcroot<UserNotify^> userNotify )
{
	_userNotify = userNotify;
}

bool InternalUserNotify::onJointBreak( NxReal breakingForce, NxJoint &brokenJoint )
{
	Joint^ joint = ObjectCache::GetObject<Joint^>( (intptr_t)(&brokenJoint) );
	
	return _userNotify->OnJointBreak( breakingForce, joint );
}
void InternalUserNotify::onWake( NxActor** actors, NxU32 count )
{
	array<Actor^>^ a = gcnew array<Actor^>( count );
	
	for( unsigned int x = 0; x < count; x++ )
	{
		a[ x ] = ObjectCache::GetObject<Actor^>( (intptr_t)actors[ x ] );
	}
	
	_userNotify->OnWake( a );
}
void InternalUserNotify::onSleep( NxActor** actors, NxU32 count )
{
	array<Actor^>^ a = gcnew array<Actor^>( count );
	
	for( unsigned int x = 0; x < count; x++ )
	{
		a[ x ] = ObjectCache::GetObject<Actor^>( (intptr_t)actors[ x ] );
	}
	
	_userNotify->OnSleep( a );
}