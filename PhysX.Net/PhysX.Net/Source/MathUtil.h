#pragma once

namespace PhysX
{
	public ref class MathUtil
	{
	internal:
		static Matrix4x4 PxTransformToMatrix(PxTransform* transform);
		static PxTransform MatrixToPxTransform(Matrix4x4 transform);

		static Matrix4x4 PxMat33ToMatrix(PxMat33* matrix);
		static PxMat33 MatrixToPxMat33(Matrix4x4 matrix);

		static Matrix4x4 PxMat44ToMatrix(PxMat44* mat44);
		static PxMat44 MatrixToPxMat44(Matrix4x4 matrix);

		static Vector3 PxVec3ToVector3(PxVec3 vector);
		static PxVec3 Vector3ToPxVec3(Vector3 vector);

		static Vector3 PxExtendedVec3ToVector3(PxExtendedVec3 vector);
		static PxExtendedVec3 Vector3ToPxExtendedVec3(Vector3 vector);

		static Vector2 PxVec2ToVector2(PxVec2 vector);
		static PxVec2 Vector2ToPxVec2(Vector2 vector);

		static Quaternion PxQuatToQuaternion(PxQuat quat);
		static PxQuat QuaternionToPxQuat(Quaternion quat);

	public:
		static bool IsMultipleOf(int num, int divisor);

		const static float Pi = 3.1415926535897932384626433832795f;
		const static float PiOver2 = Pi / 2.0f;

		static int Vector3SizeInBytes = 12;
	};
};