#include "StdAfx.h"

#include <Nxp.h> 

#include "Actor Group Pair.h"

using namespace StillDesign::PhysX;

ActorGroupPair::operator ActorGroupPair( NxActorGroupPair actorGroupPair )
{
	ActorGroupPair p;
		p.Group0 = actorGroupPair.group0;
		p.Group1 = actorGroupPair.group1;
		p.Flags = actorGroupPair.flags;
		
	return p;
}
ActorGroupPair::operator NxActorGroupPair( ActorGroupPair actorGroupPair )
{
	NxActorGroupPair p;
		p.group0 = actorGroupPair.Group0;
		p.group1 = actorGroupPair.Group1;
		p.flags = actorGroupPair.Flags;
	
	return p;
}

short ActorGroupPair::Group0::get()
{
	return _group0;
}
void ActorGroupPair::Group0::set( short value )
{
	_group0 = value;
}

short ActorGroupPair::Group1::get()
{
	return _group1;
}
void ActorGroupPair::Group1::set( short value )
{
	_group1 = value;
}
int ActorGroupPair::Flags::get()
{
	return _flags;
}
void ActorGroupPair::Flags::set( int value )
{
	_flags = value;
}