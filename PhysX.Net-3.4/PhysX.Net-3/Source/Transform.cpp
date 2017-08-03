#include "StdAfx.h"
#include "Transform.h"

Transform::Transform(Quaternion q, Vector3 p)
{
	this->Quat = q;
	this->Position = p;
}
Transform::Transform(Vector3 p)
{
	this->Quat = Quaternion::Identity;
	this->Position = p;
}

Matrix4x4 Transform::ToMatrix()
{
	Matrix4x4 m = Matrix::CreateFromQuaternion(Quaternion(Quat.X, Quat.Y, Quat.Z, Quat.W));
	m.M41 = Position.X;
	m.M42 = Position.Y;
	m.M43 = Position.Z;
	m.M44 = 1;
	return m;
}

Transform::operator Matrix4x4(Transform t)
{
	return t.ToMatrix();
}

bool Transform::operator == (Transform left, Transform right)
{
	return
		left.Quat == right.Quat &&
		left.Position == right.Position;
}
bool Transform::operator != (Transform left, Transform right)
{
	return !(left == right);
}

String^ Transform::ToString()
{
	return String::Format("Quat: {0} Position: {1}", Quat, Position);
}

int Transform::GetHashCode()
{
	int hash = 17;
	hash = hash * 23 + Quat.GetHashCode();
	hash = hash * 23 + Position.GetHashCode();
	return hash;
}

bool Transform::Equals(Object^ obj)
{
	if (obj == nullptr || obj->GetType() != GetType())
		return false;

	return Equals(safe_cast<Transform>(obj));
}

bool Transform::Equals(Transform other)
{
	return (Quat == other.Quat) && (Position == other.Position);
}

Transform Transform::ToManaged(PxTransform t)
{
	Transform m;
	memcpy(&m, &t, sizeof(PxTransform));
	return m;
}
PxTransform Transform::ToUnmanaged(Transform m)
{
	PxTransform u;
	memcpy(&u, &m, sizeof(PxTransform));
	return u;
}