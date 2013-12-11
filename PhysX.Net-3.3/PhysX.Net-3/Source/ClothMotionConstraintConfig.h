#pragma once

//#include <PxCloth.h>

namespace PhysX
{
	public value class ClothMotionConstraintConfig
	{
	internal:
		static PxClothMotionConstraintConfig ToUnmanaged(ClothMotionConstraintConfig managed);
		static ClothMotionConstraintConfig ToManaged(PxClothMotionConstraintConfig unmanaged);

	public:
		property float Scale;
		property float Bias;
		property float Stiffness;
	};
};