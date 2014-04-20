#include "StdAfx.h"

#include "Pair Flag.h"
#include "Scene.h"

#include <NxScene.h> 

using namespace StillDesign::PhysX;

PairFlag::PairFlag()
{
	
}
PairFlag::PairFlag( Object^ objectA, Object^ objectB, unsigned int flags )
{
	_objectA = objectA;
	_objectB = objectB;
	_flags = flags;
}
PairFlag::PairFlag( NxPairFlag pairFlag )
{
	if( (pairFlag.flags & 0xF0000000 ) == 0 )
	{
		_objectA = ObjectTable::GetObject<Shape^>( (intptr_t)pairFlag.objects[ 0 ] );
		_objectB = ObjectTable::GetObject<Shape^>( (intptr_t)pairFlag.objects[ 1 ] );
	}else{
		_objectA = ObjectTable::GetObject<Actor^>( (intptr_t)pairFlag.objects[ 0 ] );
		_objectB = ObjectTable::GetObject<Actor^>( (intptr_t)pairFlag.objects[ 1 ] );
	}
	
	_flags = pairFlag.flags;
}

Object^ PairFlag::ObjectA::get()
{
	return _objectA;
}

Object^ PairFlag::ObjectB::get()
{
	return _objectB;
}

unsigned int PairFlag::Flags::get()
{
	return _flags;
}