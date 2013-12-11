#include "StdAfx.h"
#include "CookingParams.h"

PxCookingParams CookingParams::ToUnmanaged(CookingParams^ params)
{
	PxTolerancesScale sc = TolerancesScale::ToUnmanaged(params->Scale);

	PxCookingParams p(sc);

	p.skinWidth = params->SkinWidth;
	p.suppressTriangleMeshRemapTable = params->SuppressTriangleMeshRemapTable;
	p.targetPlatform = ToUnmanagedEnum(PxPlatform, params->TargetPlatform);
	p.buildTriangleAdjacencies = params->BuildTriangleAdjacencies;

	return p;
}
CookingParams^ CookingParams::ToManaged(PxCookingParams params)
{
	CookingParams^ p = gcnew CookingParams();

	p->SkinWidth = params.skinWidth;
	p->SuppressTriangleMeshRemapTable = params.suppressTriangleMeshRemapTable;
	p->TargetPlatform = ToManagedEnum(Platform, params.targetPlatform);
	p->Scale = TolerancesScale::ToManaged(params.scale);
	p->BuildTriangleAdjacencies = params.buildTriangleAdjacencies;

	return p;
}