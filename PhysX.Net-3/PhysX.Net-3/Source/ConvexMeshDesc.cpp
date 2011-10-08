#include "StdAfx.h"
#include "ConvexMeshDesc.h"

ConvexMeshDesc::ConvexMeshDesc()
{
	_is16BitTriangles = false;
}

ConvexMeshDesc^ ConvexMeshDesc::ToManaged(PxConvexMeshDesc desc)
{
	auto d = gcnew ConvexMeshDesc();

	if (desc.triangles.stride == sizeof(short))
		d->_triangles = Util::AsManagedArray<short>((void*)desc.triangles.data, desc.triangles.count);
	else if (desc.triangles.stride == sizeof(int))
		d->_triangles = Util::AsManagedArray<int>((void*)desc.triangles.data, desc.triangles.count);

	d->_positions = Util::AsManagedArray<Vector3>((void*)desc.points.data, desc.points.count);
	d->Flags = ToManagedEnum(ConvexFlag, desc.flags);

	return d;
}
PxConvexMeshDesc ConvexMeshDesc::ToUnmanaged(ConvexMeshDesc^ desc)
{
	ThrowIfNull(desc, "desc");

	PxConvexMeshDesc d;
	
	PxBoundedData p;
	p.data = new PxVec3[desc->_positions->Length];
	Util::AsUnmanagedArray(desc->_positions, (void*)p.data, desc->_positions->Length);

	PxBoundedData t;
	if (desc->Is16BitTriangles)
	{
		t.data = new short[desc->_triangles->Length];
		Util::AsUnmanagedArray<short>((array<short>^)desc->_triangles, (void*)t.data, desc->_triangles->Length);
	}
	else
	{
		t.data = new int[desc->_triangles->Length];
		Util::AsUnmanagedArray<int>((array<int>^)desc->_triangles, (void*)t.data, desc->_triangles->Length);
	}

	d.points = p;
	d.triangles = t;
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
		throw gcnew InvalidOperationException("Triangles indices must be either short or int (signed or unsigned)");
	
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