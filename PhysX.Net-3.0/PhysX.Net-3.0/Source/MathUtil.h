#pragma once

#include <PxExtended.h>

namespace PhysX
{
	private ref class MathUtil
	{
		internal:
			static MathPrimitives::Matrix PxTransformToMatrix(physx::pubfnd3::PxTransform* transform);
			static physx::pubfnd3::PxTransform MatrixToPxTransform(MathPrimitives::Matrix transform);
				
			static MathPrimitives::Matrix PxMat33ToMatrix(physx::pubfnd3::PxMat33* matrix);
			static physx::pubfnd3::PxMat33 MatrixToPxMat33(MathPrimitives::Matrix matrix);

			static MathPrimitives::Vector3 PxVec3ToVector3(physx::pubfnd3::PxVec3 vector);
			static physx::pubfnd3::PxVec3 Vector3ToPxVec3(MathPrimitives::Vector3 vector);

			static MathPrimitives::Vector3 PxExtendedVec3ToVector3(PxExtendedVec3 vector);
			static PxExtendedVec3 Vector3ToPxExtendedVec3(MathPrimitives::Vector3 vector);
				
			static MathPrimitives::Quaternion PxQuatToQuaternion(physx::pubfnd3::PxQuat quat);
			static physx::pubfnd3::PxQuat QuaternionPxQuat(MathPrimitives::Quaternion quat);

			static bool IsMultipleOf(int num, int divisor);
	};
};