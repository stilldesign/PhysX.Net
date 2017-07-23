#include "StdAfx.h"
#include "ActorShape.h"
#include "ObjectTable.h"
#include "Shape.h"
#include "RigidActor.h"

using namespace PhysX;

void ActorShape::PopulateManaged(PxActorShape unmanaged)
{
	this->Actor = (unmanaged.actor == NULL ? nullptr : ObjectTable::Instance->GetObject<RigidActor^>((intptr_t)unmanaged.actor));
	this->Shape = (unmanaged.shape == NULL ? nullptr : ObjectTable::Instance->GetObject<PhysX::Shape^>((intptr_t)unmanaged.shape));
}
void ActorShape::PopulateUnmanaged(PxActorShape& unmanaged)
{
	unmanaged.actor = GetPointerOrNull(this->Actor);
	unmanaged.shape = GetPointerOrNull(this->Shape);
}

ActorShape::ActorShape()
{

}
ActorShape::ActorShape(RigidActor^ actor, PhysX::Shape^ shape)
{
	this->Actor = actor;
	this->Shape = shape;
}