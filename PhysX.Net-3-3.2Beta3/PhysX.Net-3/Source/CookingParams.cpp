#include "StdAfx.h"
#include "CookingParams.h"

PxCookingParams CookingParams::ToUnmanaged(CookingParams^ params)
{
	PxCookingParams p;

	p.skinWidth = params->SkinWidth;
	p.suppressTriangleMeshRemapTable = params->SuppressTriangleMeshRemapTable;
	p.targetPlatform = ToUnmanagedEnum(PxPlatform, params->TargetPlatform);

	return p;
}
CookingParams^ CookingParams::ToManaged(PxCookingParams params)
{
	CookingParams^ p = gcnew CookingParams();

	p->SkinWidth = params.skinWidth;
	p->SuppressTriangleMeshRemapTable = params.suppressTriangleMeshRemapTable;
	p->TargetPlatform = ToManagedEnum(Platform, params.targetPlatform);

	return p;
}