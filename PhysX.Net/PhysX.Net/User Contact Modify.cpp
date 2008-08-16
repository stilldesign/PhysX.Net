#include "StdAfx.h"

#include "User Contact Modify.h"
#include "Scene.h"
#include "Fluid.h"
#include "Fluid Emitter.h"

#include <NxUserContactReport.h> 

using namespace StillDesign::PhysX;

UserContactModify::UserContactModify()
{
	_internalUserContactModify = new InternalUserContactModify( this );
}
UserContactModify::~UserContactModify()
{
	this->!UserContactModify();
}
UserContactModify::!UserContactModify()
{
	SAFE_DELETE( _internalUserContactModify );
}

InternalUserContactModify* UserContactModify::UnmanagedPointer::get()
{
	return _internalUserContactModify;
}

//

UserContactModify::ContactCallbackData::ContactCallbackData()
{
	_contactCallbackData = new NxUserContactModify::NxContactCallbackData();
}
UserContactModify::ContactCallbackData::~ContactCallbackData()
{
	this->!ContactCallbackData();
}
UserContactModify::ContactCallbackData::!ContactCallbackData()
{
	SAFE_DELETE( _contactCallbackData );
}

UserContactModify::ContactCallbackData::operator ContactCallbackData^( NxUserContactModify::NxContactCallbackData &data )
{
	UserContactModify::ContactCallbackData^ d = gcnew UserContactModify::ContactCallbackData();
		memcpy( d->_contactCallbackData, &data, sizeof( NxUserContactModify::NxContactCallbackData ) );
	
	return d;
}
UserContactModify::ContactCallbackData::operator NxUserContactModify::NxContactCallbackData( UserContactModify::ContactCallbackData^ data )
{
	NxUserContactModify::NxContactCallbackData d;
		memcpy( &d, data->_contactCallbackData, sizeof( NxUserContactModify::NxContactCallbackData ) );
	
	return d;
}

float UserContactModify::ContactCallbackData::MinimumImpulse::get()
{
	return _contactCallbackData->minImpulse;
}
void UserContactModify::ContactCallbackData::MinimumImpulse::set( float value )
{
	_contactCallbackData->minImpulse = value;
}

float UserContactModify::ContactCallbackData::MaximumImpulse::get()
{
	return _contactCallbackData->maxImpulse;
}
void UserContactModify::ContactCallbackData::MaximumImpulse::set( float value )
{
	_contactCallbackData->maxImpulse = value;
}

Vector3 UserContactModify::ContactCallbackData::Error::get()
{
	return Math::NxVec3ToVector3( _contactCallbackData->error );
}
void UserContactModify::ContactCallbackData::Error::set( Vector3 value )
{
	_contactCallbackData->error = Math::Vector3ToNxVec3( value );
}

Vector3 UserContactModify::ContactCallbackData::Target::get()
{
	return Math::NxVec3ToVector3( _contactCallbackData->target );
}
void UserContactModify::ContactCallbackData::Target::set( Vector3 value )
{
	_contactCallbackData->target = Math::Vector3ToNxVec3( value );
}

Vector3 UserContactModify::ContactCallbackData::LocalPosition0::get()
{
	return Math::NxVec3ToVector3( _contactCallbackData->localpos0 );
}
void UserContactModify::ContactCallbackData::LocalPosition0::set( Vector3 value )
{
	_contactCallbackData->localpos0 = Math::Vector3ToNxVec3( value );
}

Vector3 UserContactModify::ContactCallbackData::LocalPosition1::get()
{
	return Math::NxVec3ToVector3( _contactCallbackData->localpos1 );
}
void UserContactModify::ContactCallbackData::LocalPosition1::set( Vector3 value )
{
	_contactCallbackData->localpos1 = Math::Vector3ToNxVec3( value );
}

Quaternion UserContactModify::ContactCallbackData::LocalOrientation0::get()
{
	return Math::NxQuatToQuaternion( _contactCallbackData->localorientation0 );
}
void UserContactModify::ContactCallbackData::LocalOrientation0::set( Quaternion value )
{
	_contactCallbackData->localorientation0 = Math::QuaternionNxQuat( value );
}

Quaternion UserContactModify::ContactCallbackData::LocalOrientation1::get()
{
	return Math::NxQuatToQuaternion( _contactCallbackData->localorientation1 );
}
void UserContactModify::ContactCallbackData::LocalOrientation1::set( Quaternion value )
{
	_contactCallbackData->localorientation1 = Math::QuaternionNxQuat( value );
}

float UserContactModify::ContactCallbackData::StaticFriction0::get()
{
	return _contactCallbackData->staticFriction0;
}
void UserContactModify::ContactCallbackData::StaticFriction0::set( float value )
{
	_contactCallbackData->staticFriction0 = value;
}

float UserContactModify::ContactCallbackData::StaticFriction1::get()
{
	return _contactCallbackData->staticFriction1;
}
void UserContactModify::ContactCallbackData::StaticFriction1::set( float value )
{
	_contactCallbackData->staticFriction1 = value;
}

float UserContactModify::ContactCallbackData::DynamicFriction0::get()
{
	return _contactCallbackData->dynamicFriction0;
}
void UserContactModify::ContactCallbackData::DynamicFriction0::set( float value )
{
	_contactCallbackData->dynamicFriction0 = value;
}

float UserContactModify::ContactCallbackData::DynamicFriction1::get()
{
	return _contactCallbackData->dynamicFriction1;
}
void UserContactModify::ContactCallbackData::DynamicFriction1::set( float value )
{
	_contactCallbackData->dynamicFriction1 = value;
}

float UserContactModify::ContactCallbackData::Restitution::get()
{
	return _contactCallbackData->restitution;
}
void UserContactModify::ContactCallbackData::Restitution::set( float value )
{
	_contactCallbackData->restitution = value;
}

//

InternalUserContactModify::InternalUserContactModify( gcroot<UserContactModify^> userContactModify )
{
	_userContactModify = userContactModify;
}

bool InternalUserContactModify::onContactConstraint( NxU32 &changeFlags, const NxShape *shape0, const NxShape *shape1, const NxU32 featureIndex0, const NxU32 featureIndex1, NxUserContactModify::NxContactCallbackData &data )
{
	UserContactModify::ContactCallbackData^ callback = (UserContactModify::ContactCallbackData^)data;
	
	Shape^ s0 = ObjectCache::GetObject<Shape^>( (intptr_t)shape0 );
	Shape^ s1 = ObjectCache::GetObject<Shape^>( (intptr_t)shape1 );
	
	bool result = _userContactModify->OnContactConstraint( changeFlags, s0, s1, featureIndex0, featureIndex1, callback );
	
	data = (NxContactCallbackData)callback;
	
	return result;
}