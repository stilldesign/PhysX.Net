#include "StdAfx.h"
#include "TriangleMeshGeometry.h"
#include "TriangleMesh.h"

TriangleMeshGeometry::TriangleMeshGeometry(PhysX::TriangleMesh^ triangleMesh, [Optional] Nullable<MeshScale> scaling, [Optional] Nullable<MeshGeometryFlag> flags)
	: Geometry(GeometryType::TriangleMesh)
{
	ThrowIfNullOrDisposed(triangleMesh, "triangleMesh");

	this->Scale = scaling.GetValueOrDefault(MeshScale::Identity);
	this->MeshFlags = flags.GetValueOrDefault((MeshGeometryFlag)0);
	this->TriangleMesh = triangleMesh;
}

PxGeometry* TriangleMeshGeometry::ToUnmanaged()
{
	PxTriangleMeshGeometry* g = new PxTriangleMeshGeometry();
		g->scale = MeshScale::ToUnmanaged(this->Scale);
		g->meshFlags = ToUnmanagedEnum(PxMeshGeometryFlag, this->MeshFlags);
		g->triangleMesh = (this->TriangleMesh == nullptr ? NULL : this->TriangleMesh->UnmanagedPointer);

	return g;
}