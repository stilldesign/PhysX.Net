#include "StdAfx.h"
#include "BoxObstacle.h"

BoxObstacle::BoxObstacle(PxObstacle* obstacle)
	: Obstacle(obstacle)
{

}
BoxObstacle::BoxObstacle()
	: Obstacle(CreateBoxObstacle())
{

}
PxBoxObstacle* BoxObstacle::CreateBoxObstacle()
{
	return new PxBoxObstacle();
}

Vector3 BoxObstacle::HalfExtents::get()
{
	return MV(this->UnmanagedPointer->mHalfExtents);
}
void BoxObstacle::HalfExtents::set(Vector3 value)
{
	this->UnmanagedPointer->mHalfExtents = UV(value);
}

Vector3 BoxObstacle::Extents::get()
{
	return this->HalfExtents * 2;
}
void BoxObstacle::Extents::set(Vector3 value)
{
	this->HalfExtents = value * 0.5f;
}

PxBoxObstacle* BoxObstacle::UnmanagedPointer::get()
{
	return (PxBoxObstacle*)Obstacle::UnmanagedPointer;
}