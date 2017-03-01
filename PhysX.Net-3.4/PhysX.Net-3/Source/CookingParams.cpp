#include "StdAfx.h"
#include "CookingParams.h"
#include "MidphaseDesc.h"

PxCookingParams CookingParams::ToUnmanaged(CookingParams^ params)
{
	PxTolerancesScale sc = TolerancesScale::ToUnmanaged(params->Scale);

	PxCookingParams p(sc);

	p.skinWidth = params->SkinWidth;
	p.suppressTriangleMeshRemapTable = params->SuppressTriangleMeshRemapTable;
	p.targetPlatform = ToUnmanagedEnum(PxPlatform, params->TargetPlatform);
	p.buildTriangleAdjacencies = params->BuildTriangleAdjacencies;
	p.meshPreprocessParams = ToUnmanagedEnum(PxMeshPreprocessingFlag, params->MeshPreprocessParams);
	p.meshCookingHint = ToUnmanagedEnum(PxMeshCookingHint, params->MeshCookingHint);
	p.meshWeldTolerance = params->MeshWeldTolerance;
	p.meshSizePerformanceTradeOff = params->MeshSizePerformanceTradeOff;
	p.areaTestEpsilon = params->AreaTestEpsilon;
	p.convexMeshCookingType = ToUnmanagedEnum(PxConvexMeshCookingType, params->ConvexMeshCookingType);
	p.buildGPUData = params->BuildGPUData;
	p.gaussMapLimit = params->GaussMapLimit;
	p.midphaseDesc = PhysX::MidphaseDesc::ToUnmanaged(params->MidphaseDesc);

	return p;
}
CookingParams^ CookingParams::ToManaged(PxCookingParams params)
{
	auto p = gcnew CookingParams();

	p->SkinWidth = params.skinWidth;
	p->SuppressTriangleMeshRemapTable = params.suppressTriangleMeshRemapTable;
	p->TargetPlatform = ToManagedEnum(Platform, params.targetPlatform);
	p->Scale = TolerancesScale::ToManaged(params.scale);
	p->BuildTriangleAdjacencies = params.buildTriangleAdjacencies;
	p->MeshPreprocessParams = ToManagedEnum(MeshPreprocessingFlag, params.meshPreprocessParams);
	p->MeshCookingHint = ToManagedEnum(PhysX::MeshCookingHint, params.meshCookingHint);
	p->MeshWeldTolerance = params.meshWeldTolerance;
	p->MeshSizePerformanceTradeOff = params.meshSizePerformanceTradeOff;
	p->AreaTestEpsilon = params.areaTestEpsilon;
	p->ConvexMeshCookingType = ToManagedEnum(PhysX::ConvexMeshCookingType, params.convexMeshCookingType);
	p->BuildGPUData = params.buildGPUData;
	p->GaussMapLimit = params.gaussMapLimit;
	p->MidphaseDesc = PhysX::MidphaseDesc::ToManaged(params.midphaseDesc);

	return p;
}