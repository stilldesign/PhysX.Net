#include "StdAfx.h"

#include "Cooking Parameters.h"

using namespace System;
using namespace StillDesign::PhysX;

NxCookingParams CookingParameters::ToUnmanaged( CookingParameters parameters )
{
	NxCookingParams p;
		p.hintCollisionSpeed = (parameters.ResourceType == CookingResourceType::Performance ? true : false);
		p.skinWidth = parameters.SkinWidth;
		p.targetPlatform = (NxPlatform)parameters.Platform;
	
	return p;
}
CookingParameters CookingParameters::ToManaged( NxCookingParams parameters )
{
	CookingParameters p;
		p.ResourceType = (parameters.hintCollisionSpeed ? CookingResourceType::Performance : CookingResourceType::LessMemory);
		p.SkinWidth = parameters.skinWidth;
		p.Platform = (StillDesign::PhysX::Platform)parameters.targetPlatform;
	
	return p;
}