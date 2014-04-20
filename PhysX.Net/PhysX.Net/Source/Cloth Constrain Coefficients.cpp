#include "StdAfx.h"
#include "Cloth Constrain Coefficients.h"

using namespace StillDesign::PhysX;

void ClothConstrainCoefficients::SetToDefault()
{
	MaximumDistance = 0.0f;
	MaximumDistanceBias = 0.0f;
	CollisionSphereRadius = 0.0f;
	CollisionSphereDistance = 0.0f;
}
bool ClothConstrainCoefficients::IsValid()
{
	if( MaximumDistance < 0.0f )
		return false;
	if( CollisionSphereRadius < 0.0f )
		return false;
	
	return true;
}

NxClothConstrainCoefficients ClothConstrainCoefficients::ToUnmanaged()
{
	NxClothConstrainCoefficients c;
		c.collisionSphereDistance = CollisionSphereDistance;
		c.collisionSphereRadius = CollisionSphereRadius;
		c.maxDistance = MaximumDistance;
		c.maxDistanceBias = MaximumDistanceBias;
	
	return c;
}
ClothConstrainCoefficients ClothConstrainCoefficients::FromUnmanaged( NxClothConstrainCoefficients constrainCoefficients )
{
	ClothConstrainCoefficients c;
		c.CollisionSphereDistance = constrainCoefficients.collisionSphereDistance;
		c.CollisionSphereRadius = constrainCoefficients.collisionSphereRadius;
		c.MaximumDistance = constrainCoefficients.maxDistance;
		c.MaximumDistanceBias = constrainCoefficients.maxDistanceBias;
	
	return c;
}