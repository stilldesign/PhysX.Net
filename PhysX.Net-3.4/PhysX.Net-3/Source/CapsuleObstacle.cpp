#include "StdAfx.h"
#include "CapsuleObstacle.h"

CapsuleObstacle::CapsuleObstacle(PxObstacle* obstacle)
	: Obstacle(obstacle)
{

}
CapsuleObstacle::CapsuleObstacle()
	: Obstacle(CreateCapsuleObstacle())
{

}
PxCapsuleObstacle* CapsuleObstacle::CreateCapsuleObstacle()
{
	return new PxCapsuleObstacle();
}

float CapsuleObstacle::HalfHeight::get()
{
	return this->UnmanagedPointer->mHalfHeight;
}
void CapsuleObstacle::HalfHeight::set(float value)
{
	this->UnmanagedPointer->mHalfHeight = value;
}
float CapsuleObstacle::Height::get()
{
	return this->HalfHeight * 2;
}
void CapsuleObstacle::Height::set(float value)
{
	this->HalfHeight = value * 0.5f;
}

float CapsuleObstacle::Radius::get()
{
	return this->UnmanagedPointer->mRadius;
}
void CapsuleObstacle::Radius::set(float value)
{
	this->UnmanagedPointer->mRadius = value;
}

PxCapsuleObstacle* CapsuleObstacle::UnmanagedPointer::get()
{
	return (PxCapsuleObstacle*)Obstacle::UnmanagedPointer;
}