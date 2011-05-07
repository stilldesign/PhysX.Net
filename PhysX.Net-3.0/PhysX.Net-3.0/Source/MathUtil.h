#pragma once

namespace PhysX
{
	private ref class MathUtil
	{
		internal:
			static MathPrimitives::Matrix PxTransformToMatrix(physx::pubfnd3::PxTransform* transform);
			static physx::pubfnd3::PxTransform MatrixToPxTransform(MathPrimitives::Matrix transform);
				
			static MathPrimitives::Vector3 PxVec3ToVector3(physx::pubfnd3::PxVec3 vector);
			static physx::pubfnd3::PxVec3 Vector3ToPxVec3(MathPrimitives::Vector3 vector);
				
			static MathPrimitives::Quaternion PxQuatToQuaternion(physx::pubfnd3::PxQuat quat);
			static physx::pubfnd3::PxQuat QuaternionPxQuat(MathPrimitives::Quaternion quat);

			static bool IsMultipleOf(int num, int divisor);
	};
};