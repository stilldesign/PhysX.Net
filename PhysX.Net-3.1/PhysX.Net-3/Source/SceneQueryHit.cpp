#include "StdAfx.h"
#include "SceneQueryHit.h"
#include "Shape.h"
#include "ObjectTable.h"
#include "Scene.h"
#include "Actor.h"

void SceneQueryHit::PopulateUnmanaged(PxSceneQueryHit& hit)
{
	hit.shape = (this->Shape == nullptr ? NULL : this->Shape->UnmanagedPointer);
	hit.faceIndex = this->FaceIndex;
	hit.flags = ToUnmanagedEnum(PxSceneQueryFlag, this->Flags);
}
void SceneQueryHit::PopulateManaged(PxSceneQueryHit& hit)
{
	this->Shape = (hit.shape == NULL ? nullptr : ObjectTable::GetObject<PhysX::Shape^>((intptr_t)hit.shape));
	this->FaceIndex = hit.faceIndex;
	this->Flags = ToManagedEnum(SceneQueryFlags, hit.flags);
}

SceneQueryHit^ SceneQueryHit::ToManaged(PxSceneQueryHit* hit)
{
	if (hit == NULL)
		throw gcnew ArgumentNullException("hit");

	SceneQueryHit^ h = gcnew SceneQueryHit();
	
	h->PopulateManaged(*hit);

	return h;
}