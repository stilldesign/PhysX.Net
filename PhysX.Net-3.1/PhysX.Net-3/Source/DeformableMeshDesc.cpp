#include "StdAfx.h"
#include "DeformableMeshDesc.h"

DeformableMeshDesc::DeformableMeshDesc()
{
	
}

PxDeformableMeshDesc DeformableMeshDesc::ToUnmanaged(DeformableMeshDesc^ desc)
{
	ThrowIfNull(desc, "desc");

	PxDeformableMeshDesc d;
	
	void* primitives;
	if (desc->Primitives != nullptr)
	{
		Nullable<bool> is16BitPrims = desc->Is16BitPrimitives();
		if (!is16BitPrims.HasValue)
			throw gcnew InvalidOperationException("Primitves must be a generic array of either 16 or 32 bit integers");

		if (is16BitPrims.Value)
		{
			primitives = new short[desc->_primitives->Length];
			Util::AsUnmanagedArray<short>((array<short>^)desc->_primitives, (void*)primitives, desc->_primitives->Length);

			if (desc->PrimitiveType == DeformablePrimitiveType::Triangle)
				d.primitiveStrideBytes = sizeof(short) * 3;
			else if(desc->PrimitiveType == DeformablePrimitiveType::Tetrahedron)
				d.primitiveStrideBytes = sizeof(short) * 4;
			else
				d.primitiveStrideBytes = 0;
		}
		else
		{
			primitives = new int[desc->_primitives->Length];
			Util::AsUnmanagedArray<int>((array<int>^)desc->_primitives, (void*)primitives, desc->_primitives->Length);

			if (desc->PrimitiveType == DeformablePrimitiveType::Triangle)
				d.primitiveStrideBytes = sizeof(int) * 3;
			else if(desc->PrimitiveType == DeformablePrimitiveType::Tetrahedron)
				d.primitiveStrideBytes = sizeof(int) * 4;
			else
				d.primitiveStrideBytes = 0;
		}
	}
	else
	{
		primitives = NULL;
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
		d->Primitives = Util::AsManagedArray<short>(desc.primitives, desc.numPrimitives);
	}
	else if (desc.primitiveStrideBytes == sizeof(int))
	{
		d->Primitives = Util::AsManagedArray<int>(desc.primitives, desc.numPrimitives);
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

void DeformableMeshDesc::SetToDefault()
{
	// TODO: Implement
}
bool DeformableMeshDesc::IsValid()
{
	// TODO: Implement
	return true;
}

generic<typename T> where T : value class
array<T>^ DeformableMeshDesc::GetPrimitives()
{
	return (array<T>^)_primitives;
}
generic<typename T> where T : value class
void DeformableMeshDesc::SetPrimitives(array<T>^ primitives)
{
	Primitives = primitives;
}

Nullable<bool> DeformableMeshDesc::Is16BitPrimitives()
{
	return Util::Is16Or32Bit(_primitives);
}

Array^ DeformableMeshDesc::Primitives::get()
{
	return _primitives;
}
void DeformableMeshDesc::Primitives::set(Array^ value)
{
	// If primitives are supplied, check that they are in the correct format (either [u]short or [u]int)
	if (value != nullptr)
	{
		if (!Util::Is16Or32Bit(value).HasValue)
			throw gcnew ArgumentException("Primitives must be a generic array of either 16 or 32 bit integers");
	}

	_primitives = value;
}