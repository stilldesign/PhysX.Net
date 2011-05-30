#include "StdAfx.h"
#include "DeformableMesh.h"
#include "Physics.h"
#include <PxDeformableMesh.h> 

DeformableMesh::DeformableMesh(PxDeformableMesh* deformableMesh, PhysX::Physics^ owner)
{
	if (deformableMesh == NULL)
		throw gcnew ArgumentNullException("deformableMesh");
	ThrowIfNullOrDisposed(owner, "owner");

	_deformableMesh = deformableMesh;
	_physics = owner;

	ObjectTable::Add((intptr_t)deformableMesh, this, owner);
}
DeformableMesh::~DeformableMesh()
{
	this->!DeformableMesh();
}
DeformableMesh::!DeformableMesh()
{
	
}

bool DeformableMesh::Disposed::get()
{
	return _deformableMesh == NULL;
}

int DeformableMesh::ReferenceCount::get()
{
	return _deformableMesh->getReferenceCount();
}

DeformablePrimitiveType DeformableMesh::PrimitiveType::get()
{
	return ToManagedEnum(DeformablePrimitiveType, _deformableMesh->getPrimitiveType());
}

PxDeformableMesh* DeformableMesh::UnmanagedPointer::get()
{
	return _deformableMesh;
}