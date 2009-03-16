#include "StdAfx.h"

#include "User Actor Pair Filtering.h"
#include "Scene.h"
#include "Actor.h"

using namespace StillDesign::PhysX;

UsingFrameworkNamespace

UserActorPairFiltering::UserActorPairFiltering( )
{
	_internalUserActorPairFiltering = new InternalUserActorPairFiltering( this );
}
UserActorPairFiltering::~UserActorPairFiltering()
{
	this->!UserActorPairFiltering();
}
UserActorPairFiltering::!UserActorPairFiltering()
{
	SAFE_DELETE( _internalUserActorPairFiltering );
}

InternalUserActorPairFiltering* UserActorPairFiltering::UnmanagedPointer::get()
{
	return _internalUserActorPairFiltering;
}

//

InternalUserActorPairFiltering::InternalUserActorPairFiltering( gcroot<UserActorPairFiltering^> userActorPairFiltering )
{
	_userActorPairFiltering = userActorPairFiltering;
}

void InternalUserActorPairFiltering::onActorPairs( NxActorPairFilter *filterArray, NxU32 arraySize )
{
	array<ActorPairFiltering^>^ pairs = gcnew array<ActorPairFiltering^>( arraySize );
	for( unsigned int x = 0; x < arraySize; x++ )
	{
		Actor^ a = ObjectTable::GetObject<Actor^>( (intptr_t)filterArray[ x ].actor[ 0 ] );
		Actor^ b = ObjectTable::GetObject<Actor^>( (intptr_t)filterArray[ x ].actor[ 1 ] );
		
		pairs[ x ] = gcnew ActorPairFiltering( a, b, filterArray[ x ].filtered );
	}
	
	_userActorPairFiltering->OnActorPairs( pairs );
	
	for( unsigned int x = 0; x < arraySize; x++ )
	{
		filterArray[ x ].actor[ 0 ] = pairs[ x ]->ActorA->UnmanagedPointer;
		filterArray[ x ].actor[ 1 ] = pairs[ x ]->ActorB->UnmanagedPointer;
		filterArray[ x ].filtered = pairs[ x ]->Filtered;
	}
}

//

ActorPairFiltering::ActorPairFiltering( Actor^ actorA, Actor^ actorB, bool filtered )
{
	_actorA = actorA;
	_actorB = actorB;
	_filtered = filtered;
}

Actor^ ActorPairFiltering::ActorA::get()
{
	return _actorA;
}
Actor^ ActorPairFiltering::ActorB::get()
{
	return _actorB;
}
bool ActorPairFiltering::Filtered::get()
{
	return _filtered;
}
void ActorPairFiltering::Filtered::set( bool value )
{
	_filtered = value;
}