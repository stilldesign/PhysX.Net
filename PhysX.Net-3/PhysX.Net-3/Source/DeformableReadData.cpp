#include "StdAfx.h"
#include <PxDeformableReadData.h> 
#include "DeformableReadData.h"

DeformableReadData::DeformableReadData(PxDeformableReadData* deformableReadData)
	: LockedData(deformableReadData)
{
	
}

int DeformableReadData::NumberOfVertices::get()
{
	return this->UnmanagedPointer->numVertices;
}
void DeformableReadData::NumberOfVertices::set(int value)
{
	this->UnmanagedPointer->numVertices = value;
}

int DeformableReadData::DirtyBufferFlags::get()
{
	return this->UnmanagedPointer->dirtyBufferFlags;
}
void DeformableReadData::DirtyBufferFlags::set(int value)
{
	this->UnmanagedPointer->dirtyBufferFlags = value;
}

int DeformableReadData::NumberOfPrimitiveSplitPairs::get()
{
	return this->UnmanagedPointer->numPrimitiveSplitPairs;
}
void DeformableReadData::NumberOfPrimitiveSplitPairs::set(int value)
{
	this->UnmanagedPointer->numPrimitiveSplitPairs = value;
}

array<Vector3>^ DeformableReadData::PositionBuffer::get()
{
	int n = this->UnmanagedPointer->numVertices;

	return Util::AsManagedArray<Vector3>((void*)this->UnmanagedPointer->positionBuffer.ptr(), n);
}
void DeformableReadData::PositionBuffer::set(array<Vector3>^ value)
{
	ThrowIfNull(value, "value");

	const PxVec3* r = new const PxVec3[value->Length];
	Util::AsUnmanagedArray(value, (void*)r, value->Length);

	PxStrideIterator<const PxVec3> p = PxStrideIterator<const PxVec3>(r);
	this->UnmanagedPointer->positionBuffer = p;
}

array<Vector3>^ DeformableReadData::VelocityBuffer::get()
{
	int n = this->UnmanagedPointer->numVertices;

	return Util::AsManagedArray<Vector3>((void*)this->UnmanagedPointer->velocityBuffer.ptr(), n);
}
void DeformableReadData::VelocityBuffer::set(array<Vector3>^ value)
{
	const PxVec3* r = new const PxVec3[value->Length];
	Util::AsUnmanagedArray(value, (void*)r, value->Length);

	PxStrideIterator<const PxVec3> p = PxStrideIterator<const PxVec3>(r);
	this->UnmanagedPointer->velocityBuffer = p;
}

array<float>^ DeformableReadData::InverseMassBuffer::get()
{
	int n = this->UnmanagedPointer->numVertices;

	return Util::AsManagedArray<float>((void*)this->UnmanagedPointer->inverseMassBuffer.ptr(), n);
}
void DeformableReadData::InverseMassBuffer::set(array<float>^ value)
{
	const float* r = new const float[value->Length];
	Util::AsUnmanagedArray(value, (void*)r, value->Length);

	PxStrideIterator<const float> p = PxStrideIterator<const float>(r);
	this->UnmanagedPointer->inverseMassBuffer = p;
}

array<Vector3>^ DeformableReadData::NormalBuffer::get()
{
	int n = this->UnmanagedPointer->numVertices;

	return Util::AsManagedArray<Vector3>((void*)this->UnmanagedPointer->normalBuffer.ptr(), n);
}
void DeformableReadData::NormalBuffer::set(array<Vector3>^ value)
{
	const PxVec3* r = new const PxVec3[value->Length];
	Util::AsUnmanagedArray(value, (void*)r, value->Length);

	PxStrideIterator<const PxVec3> n = PxStrideIterator<const PxVec3>(r);
	this->UnmanagedPointer->normalBuffer = n;
}

array<int>^ DeformableReadData::ParentIndexBuffer::get()
{
	int n = this->UnmanagedPointer->numVertices;

	return Util::AsManagedArray<int>((void*)this->UnmanagedPointer->parentIndexBuffer.ptr(), n);
}
void DeformableReadData::ParentIndexBuffer::set(array<int>^ value)
{
	const PxU32* r = new const PxU32[value->Length];
	Util::AsUnmanagedArray(value, (void*)r, value->Length);

	PxStrideIterator<const PxU32> n = PxStrideIterator<const PxU32>(r);
	this->UnmanagedPointer->parentIndexBuffer = n;
}

array<int>^ DeformableReadData::IndexBuffer::get()
{
	int n = this->UnmanagedPointer->numVertices;

	return Util::AsManagedArray<int>((void*)this->UnmanagedPointer->indexBuffer, n);
}
void DeformableReadData::IndexBuffer::set(array<int>^ value)
{
	int n = this->UnmanagedPointer->numVertices;
	const PxU32* r = new const PxU32[value->Length];
	Util::AsUnmanagedArray(value, (void*)r, n);

	this->UnmanagedPointer->indexBuffer = r;
}

array<DeformablePrimitiveSplitPair>^ DeformableReadData::PrimitiveSplitPairBuffer::get()
{
	int n = this->UnmanagedPointer->numVertices;

	return Util::AsManagedArray<DeformablePrimitiveSplitPair>((void*)this->UnmanagedPointer->primitiveSplitPairBuffer.ptr(), n);
}
void DeformableReadData::PrimitiveSplitPairBuffer::set(array<DeformablePrimitiveSplitPair>^ value)
{
	const PxDeformablePrimitiveSplitPair* r = new const PxDeformablePrimitiveSplitPair[value->Length];
	Util::AsUnmanagedArray(value, (void*)r, value->Length);

	PxStrideIterator<const PxDeformablePrimitiveSplitPair> n = PxStrideIterator<const PxDeformablePrimitiveSplitPair>(r);
	this->UnmanagedPointer->primitiveSplitPairBuffer = n;
}

PxDeformableReadData* DeformableReadData::UnmanagedPointer::get()
{
	return (PxDeformableReadData*)LockedData::UnmanagedPointer;
}