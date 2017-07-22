#include "StdAfx.h"
#include "ClothMeshQuadifier.h"
#include "ClothMeshDesc.h"

ClothMeshDesc^ ClothMeshQuadifier::GetDescriptor(ClothMeshDesc^ clothMeshDesc)
{
	ThrowIfNull(clothMeshDesc, "clothMeshDesc");

	PxClothMeshDesc desc = ClothMeshDesc::ToUnmanaged(clothMeshDesc);

	PxClothMeshQuadifier quadifier(desc);

	PxClothMeshDesc descQuad = quadifier.getDescriptor();

	SAFE_DELETE(desc.invMasses.data);
	SAFE_DELETE(desc.points.data);
	SAFE_DELETE(desc.quads.data);
	SAFE_DELETE(desc.triangles.data);

	return ClothMeshDesc::ToManaged(descQuad);
}