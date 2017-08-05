#include "StdAfx.h"
#include "ClothTetherConfig.h"

ClothTetherConfig::ClothTetherConfig()
{
	Stiffness = 1;
	StretchLimit = 1;
}
ClothTetherConfig::ClothTetherConfig(float stiffness, float stretchLimit)
{
	Stiffness = stiffness;
	StretchLimit = stretchLimit;
}

PxClothTetherConfig ClothTetherConfig::ToUnmanaged(ClothTetherConfig^ m)
{
	return PxClothTetherConfig(m->Stiffness, m->StretchLimit);
}
ClothTetherConfig^ ClothTetherConfig::ToManaged(PxClothTetherConfig u)
{
	return gcnew ClothTetherConfig(u.stiffness, u.stretchLimit);
}