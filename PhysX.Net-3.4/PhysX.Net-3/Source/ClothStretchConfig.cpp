#include "StdAfx.h"
#include "ClothStretchConfig.h"

ClothStretchConfig^ ClothStretchConfig::ToManaged(PxClothStretchConfig config)
{
	auto c = gcnew ClothStretchConfig();
		c->Stiffness = config.stiffness;
		c->StiffnessMultiplier = config.stiffnessMultiplier;
		c->CompressionLimit = config.compressionLimit;
		c->StretchLimit = config.stretchLimit;

	return c;
}
PxClothStretchConfig ClothStretchConfig::ToUnmanaged(ClothStretchConfig^ config)
{
	ThrowIfNull(config, "config");

	PxClothStretchConfig c;

	c.stiffness = config->Stiffness;
	c.stiffnessMultiplier = config->StiffnessMultiplier;
	c.compressionLimit = config->CompressionLimit;
	c.stretchLimit = config->StretchLimit;

	return c;
}