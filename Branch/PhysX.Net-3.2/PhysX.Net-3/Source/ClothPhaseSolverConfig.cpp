#include "StdAfx.h"
#include "ClothPhaseSolverConfig.h"

ClothPhaseSolverConfig^ ClothPhaseSolverConfig::ToManaged(PxClothPhaseSolverConfig config)
{
	auto c = gcnew ClothPhaseSolverConfig();
		c->SolverType = ToManagedEnum(ClothPhaseSolverType, config.solverType);
		c->Stiffness = config.stiffness;
		c->StretchStiffness = config.stretchStiffness;
		c->StretchLimit = config.stretchLimit;

	return c;
}
PxClothPhaseSolverConfig ClothPhaseSolverConfig::ToUnmanaged(ClothPhaseSolverConfig^ config)
{
	ThrowIfNull(config, "config");

	PxClothPhaseSolverConfig c;

	c.solverType = (PxClothPhaseSolverConfig::SolverType)config->SolverType;
	c.stiffness = config->Stiffness;
	c.stretchStiffness = config->StretchStiffness;
	c.stretchLimit = config->StretchLimit;

	return c;
}