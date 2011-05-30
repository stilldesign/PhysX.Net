#include "StdAfx.h"
#include "TriangleMeshDesc.h"

TriangleMeshDesc::TriangleMeshDesc()
{
	
}

TriangleMeshDesc^ TriangleMeshDesc::ToManaged(PxTriangleMeshDesc desc)
{
	auto d = gcnew TriangleMeshDesc();

	d->MaterialIndices = Util::AsManagedArray<short>(desc.materialIndices.data, desc.triangles.count);
	d->ConvexEdgeThreshold = desc.convexEdgeThreshold;

	return d;
}
PxTriangleMeshDesc TriangleMeshDesc::ToUnmanaged(TriangleMeshDesc^ desc)
{
	PxTriangleMeshDesc d;

	auto i = PxTypedStridedData<PxMaterialTableIndex>();
	i.data = new PxMaterialTableIndex[desc->MaterialIndices->Length];

	d.materialIndices = i;
	Util::AsUnmanagedArray<short>(desc->MaterialIndices, (void*)i.data, desc->MaterialIndices->Length);

	d.convexEdgeThreshold = desc->ConvexEdgeThreshold;

	return d;
}