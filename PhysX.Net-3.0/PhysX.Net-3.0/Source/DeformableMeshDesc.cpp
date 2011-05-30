#include "StdAfx.h"
#include "DeformableMeshDesc.h"

DeformableMeshDesc::DeformableMeshDesc()
{
	_is16BitPrimitives = false;
}

PxDeformableMeshDesc DeformableMeshDesc::ToUnmanaged(DeformableMeshDesc^ desc)
{
	ThrowIfNull(desc, "desc");

	PxDeformableMeshDesc d;
	
	void* primitives;	
	if (desc->Is16BitPrimitives)
	{
		primitives = new short[desc->_primitives->Length];
		Util::AsUnmanagedArray<short>((array<short>^)desc->_primitives, (void*)primitives, desc->_primitives->Length);
	}
	else
	{
		primitives = new int[desc->_primitives->Length];
		Util::AsUnmanagedArray<int>((array<int>^)desc->_primitives, (void*)primitives, desc->_primitives->Length);
	}

	PxVec3* vertices;
	if (desc->Vertices == nullptr)
	{
		vertices = NULL;
	}
	else
	{
		vertices = new PxVec3[desc->Vertices->Length];
		Util::AsUnmanagedArray(desc->Vertices, (void*)vertices, desc->Vertices->Length);
	}

	float* m;
	if (desc->VertexMasses == nullptr)
	{
		m = NULL;
	}
	else
	{
		m = new float[desc->VertexMasses->Length];
		Util::AsUnmanagedArray(desc->VertexMasses, (void*)m, desc->VertexMasses->Length);
	}

	DeformableVertexFlag* f;
	if (desc->VertexFlags == nullptr)
	{
		f = NULL;
	}
	else
	{
		f = new DeformableVertexFlag[desc->VertexFlags->Length];
		Util::AsUnmanagedArray(desc->VertexFlags, (void*)f, desc->VertexFlags->Length);
	}

	//

	d.primitiveType = ToUnmanagedEnum(PxDeformablePrimitiveType, desc->PrimitiveType);
	d.numVertices = desc->NumberOfVertices;
	d.numPrimitives = desc->NumberOfPrimitives;
	d.vertexStrideBytes = sizeof(PxVec3);
	d.primitiveStrideBytes = (desc->Is16BitPrimitives ? sizeof(short) : sizeof(int)) * 3;
	d.vertices = vertices;
	d.primitives = primitives;
	d.vertexMassStrideBytes = sizeof(float);
	d.vertexFlagStrideBytes = sizeof(int);
	d.vertexMasses = m;
	d.vertexFlags = f;
	d.weldingDistance = desc->WeldingDistance;
	d.maxHierarchyLevels = desc->MaximumHierarchyLevels;
	d.flags = ToUnmanagedEnum(PxDeformableVertexFlag, desc->Flags);

	return d;
}
DeformableMeshDesc^ DeformableMeshDesc::ToManaged(PxDeformableMeshDesc desc)
{
	DeformableMeshDesc^ d = gcnew DeformableMeshDesc();

	if (desc.primitiveStrideBytes == sizeof(short))
	{
		d->_is16BitPrimitives = true;
		d->_primitives = Util::AsManagedArray<short>(desc.primitives, desc.numPrimitives);
	}
	else if (desc.primitiveStrideBytes == sizeof(int))
	{
		d->_is16BitPrimitives = false;
		d->_primitives = Util::AsManagedArray<int>(desc.primitives, desc.numPrimitives);
	}
	else
	{
		throw gcnew InvalidOperationException("Primitives must be declared as 16 or 32 bit values");
	}

	d->NumberOfVertices = desc.numVertices;
	d->NumberOfPrimitives = desc.numPrimitives;
	d->Vertices = Util::AsManagedArray<Vector3>(desc.vertices, desc.numVertices);
	d->VertexMasses = Util::AsManagedArray<float>(desc.vertexMasses, desc.numVertices);
	d->VertexFlags = Util::AsManagedArray<DeformableVertexFlag>(desc.vertexFlags, desc.numVertices);
	d->WeldingDistance = desc.weldingDistance;
	d->MaximumHierarchyLevels = desc.maxHierarchyLevels;
	d->Flags = ToManagedEnum(DeformableVertexFlag, desc.flags);

	return d;
}

generic<typename T> where T : value class
array<T>^ DeformableMeshDesc::GetPrimitives()
{
	return (array<T>^)_primitives;
}
generic<typename T> where T : value class
void DeformableMeshDesc::SetPrimitives(array<T>^ primitives)
{
	auto t = Util::Is16Or32Bit<T>();

	if (t == PrimitiveTypeSize::Bit16)
		_is16BitPrimitives = true;
	else if (t == PrimitiveTypeSize::Bit32)
		_is16BitPrimitives = false;
	else
		throw gcnew InvalidOperationException("Primitives indices must be either short or int (signed or unsigned)");

	_primitives = primitives;
}

bool DeformableMeshDesc::Is16BitPrimitives::get()
{
	return _is16BitPrimitives;
}