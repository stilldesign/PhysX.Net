#include "StdAfx.h"
#include <PxDeformableDesc.h> 
#include "DeformableConstrainCoefficients.h"

DeformableConstrainCoefficients::DeformableConstrainCoefficients()
{
	
}

void DeformableConstrainCoefficients::SetToDefault()
{
	MaximumDistance = 0.0f;
	CollisionSphereRadius = 0.0f;
	CollisionSphereDistance = 0.0f;
}
bool DeformableConstrainCoefficients::IsValid()
{
	if (MaximumDistance < 0.0f) return false;
	if (CollisionSphereRadius < 0.0f) return false;
	return true;
}

DeformableConstrainCoefficients^ DeformableConstrainCoefficients::ToManaged(PxDeformableConstrainCoefficients coe)
{
	auto c = gcnew DeformableConstrainCoefficients();
		c->MaximumDistance = coe.maxDistance;
		c->CollisionSphereRadius = coe.collisionSphereRadius;
		c->CollisionSphereDistance = coe.collisionSphereDistance;

	return c;
}
PxDeformableConstrainCoefficients DeformableConstrainCoefficients::ToUnmanaged(DeformableConstrainCoefficients^ coe)
{
	PxDeformableConstrainCoefficients c;
		c.maxDistance = coe->MaximumDistance;
		c.collisionSphereRadius = coe->CollisionSphereRadius;
		c.collisionSphereDistance = coe->CollisionSphereDistance;

	return c;
}