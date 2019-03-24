#include "StdAfx.h"
#include "SceneLimits.h"

PxSceneLimits SceneLimits::ToUnmanaged(SceneLimits^ managed)
{
	PxSceneLimits unmanaged;
		unmanaged.maxNbActors = managed->MaxActors;		
		unmanaged.maxNbBodies = managed->MaxBodies;
		unmanaged.maxNbStaticShapes = managed->MaxStaticShapes;
		unmanaged.maxNbDynamicShapes = managed->MaxDynamicShapes;
		unmanaged.maxNbAggregates = managed->MaxAggregates;
		unmanaged.maxNbConstraints = managed->MaxConstraints;
		unmanaged.maxNbRegions = managed->MaxRegions;
		unmanaged.maxNbBroadPhaseOverlaps = managed->MaxBroadPhaseOverlaps;

	return unmanaged;
}
SceneLimits^ SceneLimits::ToManaged(PxSceneLimits unmanaged)
{
	auto managed = gcnew SceneLimits();
		managed->MaxActors = unmanaged.maxNbActors;
		managed->MaxBodies = unmanaged.maxNbBodies;
		managed->MaxStaticShapes = unmanaged.maxNbStaticShapes;
		managed->MaxDynamicShapes = unmanaged.maxNbDynamicShapes;
		managed->MaxAggregates = unmanaged.maxNbAggregates;
		managed->MaxConstraints = unmanaged.maxNbConstraints;
		managed->MaxRegions = unmanaged.maxNbRegions;
		managed->MaxBroadPhaseOverlaps = unmanaged.maxNbBroadPhaseOverlaps;

	return managed;
}

void SceneLimits::SetToDefault()
{
	MaxActors = 0;
	MaxBodies = 0;
	MaxStaticShapes = 0;
	MaxDynamicShapes = 0;
	MaxAggregates = 0;
	MaxConstraints = 0;
	MaxRegions = 0;
	MaxBroadPhaseOverlaps = 0;
}
bool SceneLimits::IsValid()
{
	return ToUnmanaged(this).isValid();
}