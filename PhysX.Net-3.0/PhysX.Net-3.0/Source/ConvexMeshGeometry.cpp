#include "StdAfx.h"
#include "ConvexMeshGeometry.h"
#include "ConvexMesh.h"
#include <PxConvexMeshGeometry.h> 

ConvexMeshGeometry::ConvexMeshGeometry()
	: Geometry(GeometryType::ConvexMesh)
{
	
}
ConvexMeshGeometry::ConvexMeshGeometry(PhysX::ConvexMesh^ convexMesh, [Optional] Nullable<MeshScale> scale)
	: Geometry(GeometryType::ConvexMesh)
{
	this->Scale = scale.GetValueOrDefault(MeshScale::Identity);
	this->ConvexMesh = convexMesh;
}

PxGeometry* ConvexMeshGeometry::ToUnmanaged()
{
	PxConvexMeshGeometry* convexMesh = new PxConvexMeshGeometry();

	convexMesh->scale = MeshScale::ToUnmanaged(this->Scale);
	convexMesh->convexMesh = GetPointerOrNull(this->ConvexMesh);

	return convexMesh;
}