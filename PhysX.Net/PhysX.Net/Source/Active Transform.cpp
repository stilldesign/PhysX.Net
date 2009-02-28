#include "StdAfx.h"

#include "Active Transform.h"
#include "Scene.h"
#include "Actor.h"
#include "Math.h"

#include <NxScene.h> 

using namespace StillDesign::PhysX;

ActiveTransform::ActiveTransform( NxActiveTransform activeTransform )
{
	_actorToWorld = Math::Mat34ToMatrix( &activeTransform.actor2World );
	_actor = ObjectCache::GetObject<StillDesign::PhysX::Actor^>( (intptr_t)activeTransform.actor );
}

StillDesign::PhysX::Actor^ ActiveTransform::Actor::get()
{
	return _actor;
}
Matrix ActiveTransform::ActorToWorld::get()
{
	return _actorToWorld;
}