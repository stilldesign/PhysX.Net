#include "StdAfx.h"

#include "Math.h"
#include "Box.h"

using namespace StillDesign::PhysX;

Box::Box( Vector3 center, Vector3 size )
{
	this->Center = center;
	this->Size = size;
}
Box::Box( Vector3 center, Vector3 size, Quaternion rotation )
{
	this->Center = center;
	this->Size = size;
	this->Rotation = rotation;
}

Box::operator Box( NxBox box )
{
	NxQuat q;
	box.rot.toQuat( q );
	
	Box newBox;
		newBox.Center = Math::NxVec3ToVector3( box.center );
		newBox.Size = Math::NxVec3ToVector3( box.extents * 2.0f );
		newBox.Rotation = Math::NxQuatToQuaternion( q );
	
	return newBox;
}
Box::operator NxBox( Box box )
{
	NxBox newBox;
		newBox.center = Math::Vector3ToNxVec3( box.Center );
		newBox.extents = Math::Vector3ToNxVec3( box.Extents );
		
		NxQuat q = Math::QuaternionNxQuat( box.Rotation );
		NxMat33 rot;
		rot.fromQuat( q );
		newBox.rot = rot;
		
	return newBox;
}

bool Box::IsValid()
{
	return
		this->Size.X > 0 &&
		this->Size.Y > 0 &&
		this->Size.Z > 0;
}

Box Box::Empty::get()
{
	return Box();
}

Vector3 Box::Extents::get()
{
	return this->Size * 0.5f;
}
void Box::Extents::set( Vector3 value )
{
	this->Size = value * 2.0f;
}