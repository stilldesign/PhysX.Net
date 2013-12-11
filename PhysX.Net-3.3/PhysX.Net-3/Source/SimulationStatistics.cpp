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
		s->NumberOfActiveConstraints = stats->nbActiveConstraints;
		s->NumberOfActiveDynamicBodies = stats->nbActiveDynamicBodies;
		s->NumberOfActiveKinematicBodies = stats->nbActiveKinematicBodies;
		s->NumberOfStaticBodies = stats->nbStaticBodies;
		s->NumberOfDynamicBodies = stats->nbDynamicBodies;

		s->NumberOfShapes = gcnew Dictionary<GeometryType, int>();
		for (int i = 0; i < PxGeometryType::eGEOMETRY_COUNT; i++)
		{
			s->NumberOfShapes[(GeometryType)i] = stats->nbShapes[i];
		}

		s->NumberOfBroadPhaseAdds = gcnew Dictionary<VolumeType, int>();
		for (int i = 0; i < PxSimulationStatistics::eVOLUME_COUNT; i++)
		{
			s->NumberOfBroadPhaseAdds[(VolumeType)i] = stats->nbBroadPhaseAdds[i];
		}

		s->NumberOfBroadPhaseRemoves = gcnew Dictionary<VolumeType, int>();
		for (int i = 0; i < PxSimulationStatistics::eVOLUME_COUNT; i++)
		{
			s->NumberOfBroadPhaseRemoves[(VolumeType)i] = stats->nbBroadPhaseRemoves[i];
		}

	return s;
}