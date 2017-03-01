#include "StdAfx.h"
#include "ConvexMeshDesc.h"

ConvexMeshDesc::ConvexMeshDesc()
{
	_is16BitTriangles = false;
}

bool ConvexMeshDesc::IsValid()
{
	return true;
}

ConvexMeshDesc^ ConvexMeshDesc::ToManaged(PxConvexMeshDesc desc)
{
	auto d = gcnew ConvexMeshDesc();

	if (desc.polygons.stride == sizeof(short))
		d->_triangles = Util::AsManagedArray<short>((void*)desc.polygons.data, desc.polygons.count);
	else if (desc.polygons.stride == sizeof(int))
		d->_triangles = Util::AsManagedArray<int>((void*)desc.polygons.data, desc.polygons.count);

	d->_positions = Util::AsManagedArray<Vector3>((void*)desc.points.data, desc.points.count);
	d->Flags = ToManagedEnum(ConvexFlag, desc.flags);

	return d;
}
PxConvexMeshDesc ConvexMeshDesc::ToUnmanaged(ConvexMeshDesc^ desc)
{
	ThrowIfNull(desc, "desc");

	PxConvexMeshDesc d;
	
	PxBoundedData p;
	{
		p.data = new PxVec3[desc->_positions->Length];
		Util::AsUnmanagedArray(desc->_positions, (void*)p.data, desc->_positions->Length);
		p.count = desc->_positions->Length;
		p.stride = sizeof(Vector3);
	}

	PxBoundedData t;
	{
		int indexSize = desc->Is16BitTriangles ? sizeof(short) : sizeof(int);
		int indexCount = desc->_triangles->Length;

		t.data = malloc(indexCount * indexSize);
		if (desc->Is16BitTriangles)
			Util::AsUnmanagedArray((array<short>^)desc->_triangles, (void*)t.data, indexCount);
		else
			Util::AsUnmanagedArray((array<int>^)desc->_triangles, (void*)t.data, indexCount);
		t.count = desc->_triangles->Length / 3;
		t.stride = (indexSize * 3);
	}

	d.points = p;
	d.indices = t;
	d.flags = ToUnmanagedEnum(PxConvexFlag, desc->Flags);

	return d;
}

generic<typename T> where T : value class
array<T>^ ConvexMeshDesc::GetTriangles()
{
	//if (!IsInstanceOf<array<T>^>(_triangles))
	//	throw gcnew InvalidOperationException(String::Format("Triangles are not stored as {0}", array<T>::typeid->Name));

	return (array<T>^)_triangles;
}
generic<typename T> where T : value class
void ConvexMeshDesc::SetTriangles(array<T>^ triangles)
{
	auto t = Util::Is16Or32Bit<T>();

	if (t == PrimitiveTypeSize::Bit16)
		_is16BitTriangles = true;
	else if (t == PrimitiveTypeSize::Bit32)
		_is16BitTriangles = false;
	else
		throw gcnew InvalidOperationException("Triangle indices must be an array of either short or int (signed or unsigned) values");
	
	_triangles = triangles;
}

array<Vector3>^ ConvexMeshDesc::GetPositions()
{
	return _positions;
}
void ConvexMeshDesc::SetPositions(array<Vector3>^ positions)
{
	_positions = positions;
}

bool ConvexMeshDesc::Is16BitTriangles::get()
{
	return _is16BitTriangles;
}