#include "StdAfx.h"
#include "Attachment.h"
#include "Physics.h"
#include "Scene.h"
#include "Deformable.h"
#include "Shape.h"
#include <PxAttachment.h> 

Attachment::Attachment(PxAttachment* attachment, PhysX::Physics^ owner)
{
	if (attachment == NULL)
		throw gcnew ArgumentNullException("attachment");
	ThrowIfNullOrDisposed(owner, "owner");

	_attachment = attachment;

	ObjectTable::Add((intptr_t)_attachment, this, owner);
}
Attachment::~Attachment()
{
	this->!Attachment();
}
Attachment::!Attachment()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_attachment->release();
	_attachment = NULL;

	OnDisposed(this, nullptr);
}

bool Attachment::Disposed::get()
{
	return _attachment == NULL;
}

array<Vector3>^ Attachment::GetPositions()
{
	int n = _attachment->getNbVertices();

	if (n == 0)
		return gcnew array<Vector3>(0);

	auto p = gcnew array<Vector3>(n);
	pin_ptr<Vector3> b = &p[0];

	int k = _attachment->getPositions((PxVec3*)b, n);

	if (k != n)
		return nullptr;

	return p;
}
void Attachment::SetPositions(array<Vector3>^ positions)
{
	ThrowIfNull(positions, "positions");

	if (positions->Length == 0)
		return;

	pin_ptr<Vector3> p = &positions[0];
	_attachment->setPositions((PxVec3*)p, positions->Length);
}

array<int>^ Attachment::GetVertexIndices()
{
	int n = _attachment->getNbVertices();

	if (n == 0)
		return gcnew array<int>(0);

	auto i = gcnew array<int>(n);
	pin_ptr<int> b = &i[0];

	int k = _attachment->getVertexIndices((PxU32*)b, n);

	if (k != n)
		return nullptr;

	return i;
}

array<int>^ Attachment::GetFlags()
{
	int n = _attachment->getNbVertices();

	if (n == 0)
		return gcnew array<int>(0);

	auto i = gcnew array<int>(n);
	pin_ptr<int> b = &i[0];

	int k = _attachment->getFlags((PxU32*)b, n);

	if (k != n)
		return nullptr;

	return i;
}

PhysX::Scene^ Attachment::Scene::get()
{
	return ObjectTable::GetObject<PhysX::Scene^>((intptr_t)_attachment->getScene());
}

PhysX::Deformable^ Attachment::Deformable::get()
{
	return ObjectTable::GetObject<PhysX::Deformable^>((intptr_t)_attachment->getDeformable());
}

PhysX::Shape^ Attachment::Shape::get()
{
	return ObjectTable::GetObject<PhysX::Shape^>((intptr_t)_attachment->getShape());
}

int Attachment::NumberOfVertices::get()
{
	return _attachment->getNbVertices();
}

PxAttachment* Attachment::UnmanagedPointer::get()
{
	return _attachment;
}