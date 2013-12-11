#include "StdAfx.h"
#include "ClothMotionConstraintConfig.h"

PxClothMotionConstraintConfig ClothMotionConstraintConfig::ToUnmanaged(ClothMotionConstraintConfig managed)
{
	PxClothMotionConstraintConfig unmanaged;
		unmanaged.scale = managed.Scale;
		unmanaged.bias = managed.Bias;
		unmanaged.stiffness = managed.Stiffness;

	return unmanaged;
}
ClothMotionConstraintConfig ClothMotionConstraintConfig::ToManaged(PxClothMotionConstraintConfig unmanaged)
{
	ClothMotionConstraintConfig managed;
		managed.Scale = unmanaged.scale;
		managed.Bias = unmanaged.bias;
		managed.Stiffness = unmanaged.stiffness;

	return managed;
}