#include "StdAfx.h"

#include "Contact Pair.h"
#include "Constant Contact Stream.h"

using namespace StillDesign::PhysX;

ContactPair::ContactPair()
{
	
}
//ContactPair::ContactPair( Actor^ actorA, Actor^ actorB, Vector3 normalForce, Vector3 frictionForce, bool actorADeleted, bool actorBDeleted )
//{
//	_actorA = actorA;
//	_actorB = actorB;
//	
//	_normalForce = normalForce;
//	_frictionForce = frictionForce;
//	
//	_actorADeleted = actorADeleted;
//	_actorBDeleted = actorBDeleted;
//	
//	_contactStream = gcnew ConstantContactStream(  );
//}
ContactPair::~ContactPair()
{
	this->!ContactPair();
}
ContactPair::!ContactPair()
{
	_contactStream = nullptr;
}

ContactPair^ ContactPair::FromUnmanagedPointer( NxContactPair* contactPair )
{
	ContactPair^ pair = gcnew ContactPair();
		
		if( contactPair->isDeletedActor[ 0 ] == false )
			pair->_actorA = ObjectTable::GetObject<Actor^>( (intptr_t)contactPair->actors[ 0 ] );
		if( contactPair->isDeletedActor[ 1 ] == false )
			pair->_actorB = ObjectTable::GetObject<Actor^>( (intptr_t)contactPair->actors[ 1 ] );
		
		pair->_normalForce = Math::NxVec3ToVector3( contactPair->sumNormalForce );
		pair->_frictionForce = Math::NxVec3ToVector3( contactPair->sumFrictionForce );
		
		pair->_actorADeleted = contactPair->isDeletedActor[ 0 ];
		pair->_actorBDeleted = contactPair->isDeletedActor[ 1 ];
		
		pair->_contactStream = gcnew ConstantContactStream( &contactPair->stream );
		
	return pair;
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

ConstantContactStream^ ContactPair::ContactStream::get()
{
	return _contactStream;
}