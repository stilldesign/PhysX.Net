#include "StdAfx.h"
#include "Actor Group Pair.h"

#include <Nxp.h>

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