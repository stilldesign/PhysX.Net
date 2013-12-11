#include "StdAfx.h"
//#include <PxHeightField.h> 
#include "HeightField.h"
#include "Physics.h"
#include "Serializable.h"

HeightField::HeightField(PxHeightField* heightField, PhysX::Physics^ owner)
{
	if (heightField == NULL)
		throw gcnew ArgumentNullException("heightField");
	ThrowIfNullOrDisposed(owner, "owner");

	_heightField = heightField;
	_physics = owner;

	ObjectTable::Add((intptr_t)heightField, this, owner);
}
HeightField::~HeightField()
{
	this->!HeightField();
}
HeightField::!HeightField()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_heightField->release();
	_heightField = NULL;

	OnDisposed(this, nullptr);
}

bool HeightField::Disposed::get()
{
	return (_heightField == NULL);
}

Serializable^ HeightField::AsSerializable()
{
	return gcnew Serializable(_heightField);
}

//

PhysX::Physics^ HeightField::Physics::get()
{
	return _physics;
}

float HeightField::GetHeight(float x, float z)
{
	return _heightField->getHeight(x, z);
}

short HeightField::GetTriangleMaterialIndex(int triangleIndex)
{
	return _heightField->getTriangleMaterialIndex(triangleIndex);
}

//

int HeightField::NumberOfRows::get()
{
	return _heightField->getNbRows();
}

int HeightField::NumberOfColumns::get()
{
	return _heightField->getNbColumns();
}

HeightFieldFormat HeightField::Format::get()
{
	return ToManagedEnum(HeightFieldFormat, _heightField->getFormat());
}

int HeightField::SampleStride::get()
{
	return _heightField->getSampleStride();
}

float HeightField::Thickness::get()
{
	return _heightField->getThickness();
}

float HeightField::ConvexEdgeThreshold::get()
{
	return _heightField->getConvexEdgeThreshold();
}

HeightFieldFlag HeightField::Flags::get()
{
	return ToManagedEnum(HeightFieldFlag, _heightField->getFlags());
}

int HeightField::ReferenceCount::get()
{
	return _heightField->getReferenceCount();
}

PxHeightField* HeightField::UnmanagedPointer::get()
{
	return _heightField;
}