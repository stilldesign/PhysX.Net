#include "StdAfx.h"
#include "SceneQueryHitObject.h"
#include "Actor.h"
#include "Shape.h"

PxSqHitObject SceneQueryHitObject::ToUnmanaged(SceneQueryHitObject^ obj)
{
	ThrowIfNull(obj, "obj");

	PxSqHitObject o;
		o.actor = GetPointerOrNull(obj->Actor);
		o.shape = GetPointerOrNull(obj->Shape);

	return o;
}
SceneQueryHitObject^ SceneQueryHitObject::ToManaged(PxSqHitObject obj)
{
	SceneQueryHitObject^ o = gcnew SceneQueryHitObject();
		o->Actor = ObjectTable::GetObject<PhysX::Actor^>((intptr_t)obj.actor);
		o->Shape = ObjectTable::GetObject<PhysX::Shape^>((intptr_t)obj.shape);

	return o;
}