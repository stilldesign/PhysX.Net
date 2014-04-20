#include "StdAfx.h"
#include "Soft Body Constrain Coefficients.h"

using namespace StillDesign::PhysX;

void SoftBodyConstrainCoefficients::SetToDefault()
{
	MaximumDistance = 0.0f;
	MaximumDistanceBias = 0.0f;
	CollisionSphereRadius = 0.0f;
	CollisionSphereDistance = 0.0f;
}
bool SoftBodyConstrainCoefficients::IsValid()
{
	if( MaximumDistance < 0.0f )
		return false;
	if( CollisionSphereRadius < 0.0f )
		return false;
	
	return true;
}

NxSoftBodyConstrainCoefficients SoftBodyConstrainCoefficients::ToUnmanaged()
{
	NxSoftBodyConstrainCoefficients c;
		c.collisionSphereDistance = CollisionSphereDistance;
		c.collisionSphereRadius = CollisionSphereRadius;
		c.maxDistance = MaximumDistance;
		c.maxDistanceBias = MaximumDistanceBias;
	
	return c;
}
SoftBodyConstrainCoefficients SoftBodyConstrainCoefficients::FromUnmanaged( NxSoftBodyConstrainCoefficients constrainCoefficients )
{
	SoftBodyConstrainCoefficients c;
		c.CollisionSphereDistance = constrainCoefficients.collisionSphereDistance;
		c.CollisionSphereRadius = constrainCoefficients.collisionSphereRadius;
		c.MaximumDistance = constrainCoefficients.maxDistance;
		c.MaximumDistanceBias = constrainCoefficients.maxDistanceBias;
	
	return c;
}