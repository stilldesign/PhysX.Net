#include "StdAfx.h"
#include "ClothStretchConfig.h"

ClothPhaseSolverConfig^ ClothPhaseSolverConfig::ToManaged(PxClothStretchConfig config)
{
	auto c = gcnew ClothPhaseSolverConfig();
		c->Stiffness = config.stiffness;
		c->StiffnessMultiplier = config.stiffnessMultiplier;
		c->CompressionLimit = config.compressionLimit;
		c->StretchLimit = config.stretchLimit;

	return c;
}
PxClothStretchConfig ClothPhaseSolverConfig::ToUnmanaged(ClothPhaseSolverConfig^ config)
{
	ThrowIfNull(config, "config");

	PxClothStretchConfig c;

	c.stiffness = config->Stiffness;
	c.stiffnessMultiplier = config->StiffnessMultiplier;
	c.compressionLimit = config->CompressionLimit;
	c.stretchLimit = config->StretchLimit;

	return c;
}