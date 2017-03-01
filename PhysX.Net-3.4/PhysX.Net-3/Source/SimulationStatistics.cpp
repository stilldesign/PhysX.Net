#include "StdAfx.h"
#include "SimulationStatistics.h"

SimulationStatistics::SimulationStatistics()
{
	
}

SimulationStatistics^ SimulationStatistics::ToManaged(PxSimulationStatistics* stats)
{
	if (stats == NULL)
		throw gcnew ArgumentException("stats");

	auto s = gcnew SimulationStatistics();
		s->ActiveConstraints = stats->nbActiveConstraints;
		s->ActiveDynamicBodies = stats->nbActiveDynamicBodies;
		s->ActiveKinematicBodies = stats->nbActiveKinematicBodies;
		s->StaticBodies = stats->nbStaticBodies;
		s->DynamicBodies = stats->nbDynamicBodies;
		s->Articulations = stats->nbArticulations;
		s->DiscreteContactPairsTotal = stats->nbDiscreteContactPairsTotal;
		s->DiscreteContactPairsWithCacheHits = stats->nbDiscreteContactPairsWithCacheHits;
		s->DiscreteContactPairsWithContacts = stats->nbDiscreteContactPairsWithContacts;

		s->Shapes = gcnew Dictionary<GeometryType, int>();
		for (int i = 0; i < PxGeometryType::eGEOMETRY_COUNT; i++)
		{
			s->Shapes[(GeometryType)i] = stats->nbShapes[i];
		}

		s->BroadPhaseAdds = gcnew Dictionary<VolumeType, int>();
		for (int i = 0; i < PxSimulationStatistics::eVOLUME_COUNT; i++)
		{
			s->BroadPhaseAdds[(VolumeType)i] = stats->nbBroadPhaseAdds[i];
		}

		s->BroadPhaseRemoves = gcnew Dictionary<VolumeType, int>();
		for (int i = 0; i < PxSimulationStatistics::eVOLUME_COUNT; i++)
		{
			s->BroadPhaseRemoves[(VolumeType)i] = stats->nbBroadPhaseRemoves[i];
		}

	return s;
}