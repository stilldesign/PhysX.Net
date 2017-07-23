#include "StdAfx.h"
#include "ControllerStats.h"

ControllerStats ControllerStats::ToManaged(PxControllerStats u)
{
	ControllerStats m;

	m.FullUpdates = u.nbFullUpdates;
	m.Iterations = u.nbIterations;
	m.PartialUpdates = u.nbPartialUpdates;
	m.Tessellation = u.nbTessellation;

	return m;
}