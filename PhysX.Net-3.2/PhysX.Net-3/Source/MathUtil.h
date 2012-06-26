#pragma once

#include <PxExtended.h>

namespace PhysX
{
	private ref class MathUtil
	{
		internal:
			static Math::Matrix PxTransformToMatrix(PxTransform* transform);
			static PxTransform MatrixToPxTransform(Math::Matrix transform);
				
			static Math::Matrix PxMat33ToMatrix(PxMat33* matrix);
			static PxMat33 MatrixToPxMat33(Math::Matrix matrix);

			static Math::Vector3 PxVec3ToVector3(PxVec3 vector);
			static PxVec3 Vector3ToPxVec3(Math::Vector3 vector);

			static Math::Vector3 PxExtendedVec3ToVector3(PxExtendedVec3 vector);
			static PxExtendedVec3 Vector3ToPxExtendedVec3(Math::Vector3 vector);
				
			static Math::Quaternion PxQuatToQuaternion(PxQuat quat);
			static PxQuat QuaternionToPxQuat(Math::Quaternion quat);

			static bool IsMultipleOf(int num, int divisor);

			const static float Pi = 3.1415926535897932384626433832795f;
			const static float PiOver2 = Pi/2.0f;
	};
};