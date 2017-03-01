#include "StdAfx.h"
#include "TriangleMeshDesc.h"

TriangleMeshDesc::TriangleMeshDesc()
{
	
}

TriangleMeshDesc^ TriangleMeshDesc::ToManaged(PxTriangleMeshDesc desc)
{
	auto d = gcnew TriangleMeshDesc();

	d->MaterialIndices = Util::AsManagedArray<short>(desc.materialIndices.data, desc.triangles.count);

	return d;
}
PxTriangleMeshDesc TriangleMeshDesc::ToUnmanaged(TriangleMeshDesc^ desc)
{
	PxTriangleMeshDesc d;

	desc->PopulateUnmanaged(d);

	if (desc->MaterialIndices != nullptr)
	{
		auto i = PxTypedStridedData<PxMaterialTableIndex>();
		i.data = new PxMaterialTableIndex[desc->MaterialIndices->Length];
		
		d.materialIndices = i;
		Util::AsUnmanagedArray<short>(desc->MaterialIndices, (void*)i.data, desc->MaterialIndices->Length);
	}
	
	return d;
}

void TriangleMeshDesc::SetToDefault()
{
	SimpleTriangleMesh::SetToDefault();
}
bool TriangleMeshDesc::IsValid()
{
	if(Points->Length < 3) 	//at least 1 trig's worth of points
		return false;
	if ((!Triangles) && (Points->Length%3))		// Non-indexed mesh => we must ensure the geometry defines an implicit number of triangles // i.e. numVertices can't be divided by 3
		return false;
	//add more validity checks here
	//if (MaterialIndices.data && MaterialIndices.stride < sizeof(PxMaterialTableIndex))
	//	return false;

	return SimpleTriangleMesh::IsValid();
}