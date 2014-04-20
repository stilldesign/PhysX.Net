#include "StdAfx.h"

#include "Scene Statistics.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

SceneStatistics::SceneStatistics( Scene^ scene )
{
	ThrowIfNullOrDisposed( scene, "scene" );
	
	_stats = new NxSceneStats();
	
	scene->UnmanagedPointer->getStats( *_stats );
}
SceneStatistics::~SceneStatistics()
{
	this->!SceneStatistics();
}
SceneStatistics::!SceneStatistics()
{
	SAFE_DELETE( _stats );
}

int SceneStatistics::Contacts::get()
{
	return _stats->numContacts;
}
int SceneStatistics::MaximumContacts::get()
{
	return _stats->maxContacts;
}
int SceneStatistics::Pairs::get()
{
	return _stats->numPairs;
}
int SceneStatistics::MaximumPairs::get()
{
	return _stats->maxPairs;
}
int SceneStatistics::DynamicActorsInAwakeGroups::get()
{
	return _stats->numDynamicActorsInAwakeGroups;
}
int SceneStatistics::MaximumDynamicActorsInAwakeGroups::get()
{
	return _stats->maxDynamicActorsInAwakeGroups;
}
int SceneStatistics::AxisConstraints::get()
{
	return _stats->numAxisConstraints;
}
int SceneStatistics::MaximumAxisConstraints::get()
{
	return _stats->maxAxisConstraints;
}
int SceneStatistics::SolverBodies::get()
{
	return _stats->numSolverBodies;
}
int SceneStatistics::MaximumSolverBodies::get()
{
	return _stats->maxSolverBodies;
}
int SceneStatistics::Actors::get()
{
	return _stats->numActors;
}
int SceneStatistics::DynamicActors::get()
{
	return _stats->maxDynamicActors;
}
int SceneStatistics::MaximumDynamicActors::get()
{
	return _stats->maxDynamicActors;
}
int SceneStatistics::StaticShapes::get()
{
	return _stats->numStaticShapes;
}
int SceneStatistics::MaximumStaticShapes::get()
{
	return _stats->maxStaticShapes;
}
int SceneStatistics::DynamicShapes::get()
{
	return _stats->numDynamicShapes;
}
int SceneStatistics::MaximumDynamicShapes::get()
{
	return _stats->maxDynamicShapes;
}
int SceneStatistics::Joints::get()
{
	return _stats->numJoints;
}
int SceneStatistics::MaximumJoints::get()
{
	return _stats->maxJoints;
}

NxSceneStats* SceneStatistics::UnmanagedPointer::get()
{
	return _stats;
}