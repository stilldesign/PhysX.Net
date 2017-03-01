#include "StdAfx.h"
#include "ActiveTransform.h"

 ActiveTransform^ ActiveTransform::ToManaged(PxActiveTransform transform)
{
	ActiveTransform^ t = gcnew ActiveTransform();
		t->Actor = ObjectTable::GetObject<PhysX::Actor^>((intptr_t)transform.actor);
		t->ActorToWorldTransform = MathUtil::PxTransformToMatrix(&transform.actor2World);
	
	return t;
}