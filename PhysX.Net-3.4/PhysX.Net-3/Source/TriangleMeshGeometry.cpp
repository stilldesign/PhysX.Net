#include "StdAfx.h"
#include "TriangleMeshGeometry.h"
#include "TriangleMesh.h"

TriangleMeshGeometry::TriangleMeshGeometry()
	: Geometry(GeometryType::TriangleMesh)
{
	this->Scale = MeshScale::Identity;
}
TriangleMeshGeometry::TriangleMeshGeometry(PhysX::TriangleMesh^ triangleMesh, [Optional] Nullable<MeshScale> scaling, [Optional] Nullable<MeshGeometryFlag> flags)
	: TriangleMeshGeometry()
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

	// TODO: paddingFromFlags

	return g;
}
TriangleMeshGeometry^ TriangleMeshGeometry::ToManaged(PxTriangleMeshGeometry triangleMesh)
{
	TriangleMeshGeometry^ g = gcnew TriangleMeshGeometry();
		g->Scale = MeshScale::ToManaged(triangleMesh.scale);
		g->MeshFlags = ToManagedEnum(MeshGeometryFlag, triangleMesh.meshFlags);
		g->TriangleMesh = triangleMesh.triangleMesh == NULL ?
			nullptr : 
			ObjectTable::Instance->GetObject<PhysX::TriangleMesh^>((intptr_t)triangleMesh.triangleMesh);

	// TODO: paddingFromFlags

	return g;
}