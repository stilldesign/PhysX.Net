#include "StdAfx.h"
#include "Obstacle.h"

Obstacle::Obstacle(PxObstacle* obstacle)
{
	if (obstacle == NULL)
		throw gcnew ArgumentNullException("obstacle");

	_obstacle = obstacle;
}
Obstacle::~Obstacle()
{
	this->!Obstacle();
}
Obstacle::!Obstacle()
{
	_obstacle = NULL;
}

GeometryType Obstacle::Type::get()
{
	return ToManagedEnum(GeometryType, _obstacle->getType());
}

Vector3 Obstacle::Position::get()
{
	return MathUtil::PxExtendedVec3ToVector3(_obstacle->mPos);
}
void Obstacle::Position::set(Vector3 value)
{
	_obstacle->mPos = MathUtil::Vector3ToPxExtendedVec3(value);
}

Quaternion Obstacle::Rotation::get()
{
	return MathUtil::PxQuatToQuaternion(_obstacle->mRot);
}
void Obstacle::Rotation::set(Quaternion value)
{
	_obstacle->mRot = MathUtil::QuaternionToPxQuat(value);
}

PxObstacle* Obstacle::UnmanagedPointer::get()
{
	return _obstacle;
}