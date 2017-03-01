#include "StdAfx.h"

//
//#include "GeometryHolder.h"
//#include "Geometry.h"
//#include "SphereGeometry.h"
//#include "PlaneGeometry.h"
//#include "CapsuleGeometry.h"
//#include "BoxGeometry.h"
//#include "ConvexMeshGeometry.h"
//#include "TriangleMeshGeometry.h"
//#include "HeightFieldGeometry.h"
//
//Geometry^ GeometryHolder::GetGeometryFromUnmanaged(PxGeometryHolder* gh)
//{
//	return nullptr;
//	switch (gh->getType())
//	{
//	case PxGeometryType::eSPHERE:
//		return SphereGeometry::ToManaged(gh->sphere());
//
//	case PxGeometryType::ePLANE:
//		return PlaneGeometry::ToManaged(gh->plane());
//
//	case PxGeometryType::eCAPSULE:
//		return CapsuleGeometry::ToManaged(gh->capsule());
//
//	case PxGeometryType::eBOX:
//		return BoxGeometry::ToManaged(gh->box());
//
//	case PxGeometryType::eCONVEXMESH:
//		return ConvexMeshGeometry::ToManaged(gh->convexMesh());
//
//	case PxGeometryType::eTRIANGLEMESH:
//		return TriangleMeshGeometry::ToManaged(gh->triangleMesh());
//
//	case PxGeometryType::eHEIGHTFIELD:
//		return HeightFieldGeometry::ToManaged(gh->heightField());
//
//	default:
//		throw gcnew InvalidOperationException("Unsupported geometry type");
//	} 
//}