#include "StdAfx.h"
#include "MeshScale.h"

MeshScale::MeshScale(Vector3 scale, Quaternion rotation)
{
	Scale = scale;
	Rotation = rotation;
}

PxMeshScale MeshScale::ToUnmanaged(MeshScale meshScale)
{
	PxMeshScale s;
		s.scale = MathUtil::Vector3ToPxVec3(meshScale.Scale);
		s.rotation = MathUtil::QuaternionToPxQuat(meshScale.Rotation);

	return s;
}
MeshScale MeshScale::ToManaged(PxMeshScale meshScale)
{
	MeshScale s;
		s.Scale = MathUtil::PxVec3ToVector3(meshScale.scale);
		s.Rotation = MathUtil::PxQuatToQuaternion(meshScale.rotation);

	return s;
}

MeshScale MeshScale::GetInverse()
{
	return ToManaged(MeshScale::ToUnmanaged(*this).getInverse());
}

Matrix MeshScale::ToMatrix()
{
	return
		Matrix::CreateScale(this->Scale) *
		Matrix::CreateFromQuaternion(this->Rotation);
}

MeshScale MeshScale::Identity::get()
{
	MeshScale scale;
		scale.Scale = Vector3(1, 1, 1);
		scale.Rotation = Quaternion::Identity;

	return scale;
}

/// <summary>
/// Returns true if the scaling is an identity transformation.
/// </summary>
bool MeshScale::IsIdentity::get()
{
	return
		this->Scale.X == 1 && this->Scale.Y == 1 && this->Scale.Z == 1 &&
		this->Rotation.X == 0 && this->Rotation.Y == 0 && this->Rotation.Z == 0 && this->Rotation.W == 1;
}