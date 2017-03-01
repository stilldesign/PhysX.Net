#include "StdAfx.h"
#include "SimpleTriangleMesh.h"
#include "CookingEnum.h"

SimpleTriangleMesh::SimpleTriangleMesh()
{
	
}

void SimpleTriangleMesh::PopulateUnmanaged(PxSimpleTriangleMesh& mesh)
{
	PxBoundedData p;
	p.data = new PxVec3[this->Points->Length];
	p.count = this->Points->Length;
	p.stride = sizeof(PxVec3);
	Util::AsUnmanagedArray(this->Points, (void*)p.data, this->Points->Length);
	mesh.points = p;

	if (this->Triangles != nullptr)
	{
		Nullable<bool> is16BitTris = this->Is16BitTriangleIndices();
		if (!is16BitTris.HasValue)
			throw gcnew InvalidOperationException("Triangles must be a generic array of either 16 or 32 bit integers");

		PxBoundedData t;
		t.count = this->Triangles->Length / 3;
		if (is16BitTris.Value)
		{
			t.data = new short[this->Triangles->Length];
			t.stride = sizeof(short) * 3;
			Util::AsUnmanagedArray<short>((array<short>^)this->Triangles, (void*)t.data, this->Triangles->Length);
		}
		else
		{
			t.data = new int[this->Triangles->Length];
			t.stride = sizeof(int) * 3;
			Util::AsUnmanagedArray<int>((array<int>^)this->Triangles, (void*)t.data, this->Triangles->Length);
		}

		mesh.triangles = t;
	}
	else
	{
		mesh.triangles.data = NULL;
		mesh.triangles.count = 0;
		mesh.triangles.stride = 0;
	}

	mesh.flags = ToUnmanagedEnum(PxMeshFlag, this->Flags);
}

SimpleTriangleMesh^ SimpleTriangleMesh::ToManaged(PxSimpleTriangleMesh mesh)
{
	auto d = gcnew SimpleTriangleMesh();

	if (mesh.triangles.stride == sizeof(short))
		d->Triangles = Util::AsManagedArray<short>((void*)mesh.triangles.data, mesh.triangles.count);
	else if (mesh.triangles.stride == sizeof(int))
		d->Triangles = Util::AsManagedArray<int>((void*)mesh.triangles.data, mesh.triangles.count);

	d->Points = Util::AsManagedArray<Vector3>((void*)mesh.points.data, mesh.points.count);
	d->Flags = ToManagedEnum(MeshFlag, mesh.flags);

	return d;
}
PxSimpleTriangleMesh SimpleTriangleMesh::ToUnmanaged(SimpleTriangleMesh^ mesh)
{
	ThrowIfNull(mesh, "mesh");

	PxSimpleTriangleMesh d;

	mesh->PopulateUnmanaged(d);

	return d;
}

void SimpleTriangleMesh::SetToDefault()
{
	
}
bool SimpleTriangleMesh::IsValid()
{
	return true;
}

Nullable<bool> SimpleTriangleMesh::Is16BitTriangleIndices()
{
	return Util::Is16Or32Bit(this->Triangles);
}

generic<typename T>
array<T>^ SimpleTriangleMesh::GetTriangles()
{
	//if (!IsInstanceOf<array<T>^>(_triangles))
	//	throw gcnew InvalidOperationException(String::Format("Triangles are not stored as {0}", array<T>::typeid->Name));

	return (array<T>^)_triangles;
}
generic<typename T>
void SimpleTriangleMesh::SetTriangles(array<T>^ triangles)
{
	this->Triangles = triangles;
}

Array^ SimpleTriangleMesh::Triangles::get()
{
	return _triangles;
}
void SimpleTriangleMesh::Triangles::set(Array^ value)
{
	// If triangles are supplied, check that they are in the correct format (either [u]short or [u]int)
	if (value != nullptr)
	{
		Type^ type = value->GetType();

		if (!type->HasElementType || Util::Is16Or32Bit(type->GetElementType()) == (PrimitiveTypeSize)0)
			throw gcnew ArgumentException("Triangles must be a generic array of either 16 or 32 bit integers");
	}

	_triangles = value;
}