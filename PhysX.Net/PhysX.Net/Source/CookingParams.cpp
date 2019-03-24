#include "StdAfx.h"
#include "CookingParams.h"
#include "MidphaseDesc.h"

PxCookingParams CookingParams::ToUnmanaged(CookingParams^ params)
{
	PxTolerancesScale sc = TolerancesScale::ToUnmanaged(params->Scale);

	PxCookingParams p(sc);

	p.suppressTriangleMeshRemapTable = params->SuppressTriangleMeshRemapTable;
	p.buildTriangleAdjacencies = params->BuildTriangleAdjacencies;
	p.meshPreprocessParams = ToUnmanagedEnum(PxMeshPreprocessingFlag, params->MeshPreprocessParams);
	p.meshWeldTolerance = params->MeshWeldTolerance;
	p.areaTestEpsilon = params->AreaTestEpsilon;
	p.convexMeshCookingType = ToUnmanagedEnum(PxConvexMeshCookingType, params->ConvexMeshCookingType);
	p.buildGPUData = params->BuildGPUData;
	p.gaussMapLimit = params->GaussMapLimit;
	p.midphaseDesc = PhysX::MidphaseDesc::ToUnmanaged(params->MidphaseDesc);
	p.planeTolerance = params->PlaneTolerance;

	return p;
}
CookingParams^ CookingParams::ToManaged(PxCookingParams params)
{
	auto p = gcnew CookingParams();

	p->SuppressTriangleMeshRemapTable = params.suppressTriangleMeshRemapTable;
	p->Scale = TolerancesScale::ToManaged(params.scale);
	p->BuildTriangleAdjacencies = params.buildTriangleAdjacencies;
	p->MeshPreprocessParams = ToManagedEnum(MeshPreprocessingFlag, params.meshPreprocessParams);
	p->MeshWeldTolerance = params.meshWeldTolerance;
	p->AreaTestEpsilon = params.areaTestEpsilon;
	p->ConvexMeshCookingType = ToManagedEnum(PhysX::ConvexMeshCookingType, params.convexMeshCookingType);
	p->BuildGPUData = params.buildGPUData;
	p->GaussMapLimit = params.gaussMapLimit;
	p->MidphaseDesc = PhysX::MidphaseDesc::ToManaged(params.midphaseDesc);
	p->PlaneTolerance = params.planeTolerance;

	return p;
}