#include "StdAfx.h"
#include "ContactPointAux.h"

PxContactPointAux ContactPointAux::ToUnmanaged(ContactPointAux aux)
{
	PxContactPointAux a;
		a.targetVelocity = MathUtil::Vector3ToPxVec3(aux.TargetVelocity);
		a.maxImpulse = aux.MaxImpulse;

	return a;
}
ContactPointAux ContactPointAux::ToManaged(PxContactPointAux aux)
{
	ContactPointAux a;
		a.TargetVelocity = MathUtil::PxVec3ToVector3(aux.targetVelocity);
		a.MaxImpulse = aux.maxImpulse;

	return a;
}