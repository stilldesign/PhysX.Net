#include "StdAfx.h"
#include "SceneQueryImpactHit.h"

void SceneQueryImpactHit::PopulateUnmanaged(PxSceneQueryImpactHit& hit)
{
	SceneQueryHit::PopulateUnmanaged(hit);

	hit.impact = MathUtil::Vector3ToPxVec3(this->Impact);
	hit.normal = MathUtil::Vector3ToPxVec3(this->Normal);
	hit.distance = this->Distance;
}
void SceneQueryImpactHit::PopulateManaged(PxSceneQueryImpactHit& hit)
{
	SceneQueryHit::PopulateManaged(hit);

	this->Impact = MathUtil::PxVec3ToVector3(hit.impact);
	this->Normal = MathUtil::PxVec3ToVector3(hit.normal);
	this->Distance = hit.distance;
}