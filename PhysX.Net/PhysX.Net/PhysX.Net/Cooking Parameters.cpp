#include "StdAfx.h"

#include "Cooking Parameters.h"

using namespace System;
using namespace StillDesign::PhysX;

CookingParameters::operator NxCookingParams( CookingParameters parameters )
{
	NxCookingParams p;
		p.hintCollisionSpeed = (parameters.ResourceType == CookingResourceType::Performance ? true : false);
		p.skinWidth = parameters.SkinWidth;
		p.targetPlatform = (NxPlatform)parameters.Platform;
	
	return p;
}
CookingParameters::operator CookingParameters( NxCookingParams parameters )
{
	CookingParameters p;
		p.ResourceType = (parameters.hintCollisionSpeed ? CookingResourceType::Performance : CookingResourceType::LessMemory);
		p.SkinWidth = parameters.skinWidth;
		p.Platform = (StillDesign::PhysX::Platform)parameters.targetPlatform;
	
	return p;
}

StillDesign::PhysX::Platform CookingParameters::Platform::get()
{
	return _platform;
}
void CookingParameters::Platform::set( StillDesign::PhysX::Platform value )
{
	_platform = value;
}

float CookingParameters::SkinWidth::get()
{
	return _skinWidth;
}
void CookingParameters::SkinWidth::set( float value )
{
	_skinWidth = value;
}

CookingResourceType CookingParameters::ResourceType::get()
{
	return _resourceType;
}
void CookingParameters::ResourceType::set( CookingResourceType value )
{
	_resourceType = value;
}