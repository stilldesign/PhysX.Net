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
		s->NumberOfActiveConstraints = stats->numActiveConstraints;
		s->NumberOfActiveDynamicBodies = stats->numActiveDynamicBodies;
		s->NumberOfActiveKinematicBodies = stats->numActiveKinematicBodies;
		s->NumberOfStaticBodies = stats->numStaticBodies;
		s->NumberOfDynamicBodies = stats->numDynamicBodies;

		s->NumberOfShapes = gcnew Dictionary<GeometryType, int>();
		for (int i = 0; i < PxGeometryType::eGEOMETRY_COUNT; i++)
		{
			s->NumberOfShapes[(GeometryType)i] = stats->numShapes[i];
		}

		s->NumberOfBroadPhaseAdds = gcnew Dictionary<VolumeType, int>();
		for (int i = 0; i < PxSimulationStatistics::eVOLUME_COUNT; i++)
		{
			s->NumberOfBroadPhaseAdds[(VolumeType)i] = stats->numBroadPhaseAdds[i];
		}

		s->NumberOfBroadPhaseRemoves = gcnew Dictionary<VolumeType, int>();
		for (int i = 0; i < PxSimulationStatistics::eVOLUME_COUNT; i++)
		{
			s->NumberOfBroadPhaseRemoves[(VolumeType)i] = stats->numBroadPhaseRemoves[i];
		}

	return s;
}