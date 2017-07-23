#include "StdAfx.h"
#include "ConvexMeshGeometry.h"
#include "ConvexMesh.h"

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
ConvexMeshGeometry^ ConvexMeshGeometry::ToManaged(PxConvexMeshGeometry convexMesh)
{
	ConvexMeshGeometry^ cm = gcnew ConvexMeshGeometry();

	cm->Scale = MeshScale::ToManaged(convexMesh.scale);
	cm->ConvexMesh = convexMesh.convexMesh == NULL ? 
		nullptr : 
		ObjectTable::Instance->GetObject<PhysX::ConvexMesh^>((intptr_t)convexMesh.convexMesh);

	return cm;
}

int ConvexMeshGeometry::FindFaceIndex(Matrix4x4 geometryPose, Vector3 impactPosition, Vector3 unitDirection)
{
	auto unmanaged = (PxConvexMeshGeometry*)ToUnmanaged();

	PxU32 faceIndex = PxFindFaceIndex(
		*unmanaged,
		MathUtil::MatrixToPxTransform(geometryPose),
		MathUtil::Vector3ToPxVec3(impactPosition),
		MathUtil::Vector3ToPxVec3(unitDirection));

	delete unmanaged;

	return faceIndex;
}