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
		s->KinematicBodies = stats->nbKinematicBodies;
		s->Aggregates = stats->nbAggregates;
		s->Articulations = stats->nbArticulations;
		s->AxisSolverConstraints = stats->nbAxisSolverConstraints;
		s->CompressedContactSize = stats->compressedContactSize;
		s->RequiredContactConstraintMemory = stats->requiredContactConstraintMemory;
		s->PeakConstraintMemory = stats->peakConstraintMemory;
		s->DiscreteContactPairsTotal = stats->nbDiscreteContactPairsTotal;
		s->DiscreteContactPairsWithCacheHits = stats->nbDiscreteContactPairsWithCacheHits;
		s->DiscreteContactPairsWithContacts = stats->nbDiscreteContactPairsWithContacts;
		s->NewPairs = stats->nbNewPairs;
		s->NewTouches = stats->nbNewTouches;
		s->LostTouches = stats->nbLostTouches;
		s->Partitions = stats->nbPartitions;

		s->Shapes = gcnew Dictionary<GeometryType, int>();
		for (int i = 0; i < PxGeometryType::eGEOMETRY_COUNT; i++)
		{
			s->Shapes[(GeometryType)i] = stats->nbShapes[i];
		}

		s->BroadPhaseAdds = stats->getNbBroadPhaseAdds();
		s->BroadPhaseRemoves = stats->getNbBroadPhaseRemoves();

		s->ModifiedContactPairs = gcnew array<int, 2>(PxGeometryType::eGEOMETRY_COUNT, PxGeometryType::eGEOMETRY_COUNT);
		for (size_t i = 0; i < PxGeometryType::eGEOMETRY_COUNT; i++)
		{
			for (size_t j = 0; j < PxGeometryType::eGEOMETRY_COUNT; j++)
			{
				s->ModifiedContactPairs[i, j] = stats->nbModifiedContactPairs[i][j];
			}
		}

		s->TriggerPairs = gcnew array<int, 2>(PxGeometryType::eGEOMETRY_COUNT, PxGeometryType::eGEOMETRY_COUNT);
		for (size_t i = 0; i < PxGeometryType::eGEOMETRY_COUNT; i++)
		{
			for (size_t j = 0; j < PxGeometryType::eGEOMETRY_COUNT; j++)
			{
				s->TriggerPairs[i, j] = stats->nbTriggerPairs[i][j];
			}
		}

	return s;
}