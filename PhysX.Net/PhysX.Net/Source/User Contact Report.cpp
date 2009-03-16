#include "StdAfx.h"

#include "User Contact Report.h"
#include "Scene.h"

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

ContactPair::ContactPair( Actor^ actorA, Actor^ actorB, Vector3 normalForce, Vector3 frictionForce, bool actorADeleted, bool actorBDeleted )
{
	_actorA = actorA;
	_actorB = actorB;
	
	_normalForce = normalForce;
	_frictionForce = frictionForce;
}
ContactPair::ContactPair( NxContactPair* contactPair )
{
	_actorA = ObjectTable::GetObject<Actor^>( (intptr_t)contactPair->actors[ 0 ] );
	_actorB = ObjectTable::GetObject<Actor^>( (intptr_t)contactPair->actors[ 1 ] );
	
	_normalForce = Math::NxVec3ToVector3( contactPair->sumNormalForce );
	_frictionForce = Math::NxVec3ToVector3( contactPair->sumFrictionForce );
	
	_actorADeleted = contactPair->isDeletedActor[ 0 ];
	_actorBDeleted = contactPair->isDeletedActor[ 1 ];
}

Actor^ ContactPair::ActorA::get()
{
	return _actorA;
}
Actor^ ContactPair::ActorB::get()
{
	return _actorB;
}

Vector3 ContactPair::NormalForce::get()
{
	return _normalForce;
}
Vector3 ContactPair::FrictionForce::get()
{
	return _frictionForce;
}

bool ContactPair::IsActorADeleted::get()
{
	return _actorADeleted;
}
bool ContactPair::IsActorBDeleted::get()
{
	return _actorBDeleted;
}

//

InternalUserContactReport::InternalUserContactReport( UserContactReport^ userContactReport )
{
	_userContactReport = userContactReport;
}
void InternalUserContactReport::onContactNotify( NxContactPair &pair, NxU32 events )
{
	_userContactReport->OnContactNotify( gcnew ContactPair( &pair ), (ContactPairFlag)events );
}