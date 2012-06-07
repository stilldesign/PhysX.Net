#include "StdAfx.h"
#include "ClothMeshDesc.h"

ClothMeshDesc::ClothMeshDesc()
{

}

PxClothMeshDesc ClothMeshDesc::ToUnmanaged(ClothMeshDesc^ desc)
{
	ThrowIfNull(desc, "desc");

	PxClothMeshEdgeFlags* ef;
	if (desc->EdgeFlags == nullptr)
	{
		ef = NULL;
	}
	else
	{
		ef = new PxClothMeshEdgeFlags[desc->EdgeFlags->Length];
		Util::AsUnmanagedArray(desc->EdgeFlags, ef);
	}

	PxClothMeshVertFlags* vf;
	if (desc->VertexFlags == nullptr)
	{
		vf = NULL;
	}
	else
	{
		vf = new PxClothMeshVertFlags[desc->VertexFlags->Length];
		Util::AsUnmanagedArray(desc->VertexFlags, vf);
	}

	PxClothMeshDesc d;
		d.edgeFlags = ef;
		d.vertFlags = vf;

	desc->PopulateUnmanaged(d);

	return d;
}

void ClothMeshDesc::SetToDefault()
{
	SimpleTriangleMesh::SetToDefault();
}
bool ClothMeshDesc::IsValid()
{
	return SimpleTriangleMesh::IsValid();
}