#include "StdAfx.h"
#include "MathUtil.h"

using namespace PhysX;
using namespace PhysX::MathPrimitives;
using namespace physx::pubfnd3;

Matrix MathUtil::PxTransformToMatrix(PxTransform* transform)
{
	Quaternion q = Quaternion(transform->q.x, transform->q.y, transform->q.z, transform->q.w);
	Matrix m = 
		Matrix::RotationQuaternion(q) *
		Matrix::Translation(Vector3(transform->p.x, transform->p.y, transform->p.z));
	
	return m;
}
PxTransform MathUtil::MatrixToPxTransform(Matrix matrix)
{
	Quaternion q = Quaternion::RotationMatrix(matrix);

	PxTransform t;
		t.p = PxVec3(matrix.M41, matrix.M42, matrix.M43);
		t.q = PxQuat(q.X, q.Y, q.Z, q.W);

	return t;
}

Vector3 MathUtil::PxVec3ToVector3(PxVec3 vector)
{
	return Vector3(vector.x, vector.y, vector.z);
}
PxVec3 MathUtil::Vector3ToPxVec3(Vector3 vector)
{
	return PxVec3(vector.X, vector.Y, vector.Z);
}

Quaternion MathUtil::PxQuatToQuaternion(PxQuat quat)
{
	return Quaternion(quat.x, quat.y, quat.z, quat.w);
}
PxQuat MathUtil::QuaternionPxQuat(Quaternion quat)
{
	return PxQuat(quat.X, quat.Y, quat.Z, quat.W);
}

bool MathUtil::IsMultipleOf(int num, int divisor)
{
	return (num % divisor) == 0;
}