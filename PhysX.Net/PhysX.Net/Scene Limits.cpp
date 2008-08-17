#include "StdAfx.h"

#include "Scene Limits.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

SceneLimits::SceneLimits()
{
	_sceneLimits = new NxSceneLimits();
}
SceneLimits::~SceneLimits()
{
	this->!SceneLimits();
}
SceneLimits::!SceneLimits()
{
	SAFE_DELETE( _sceneLimits );
}

SceneLimits^ SceneLimits::FromScene( Scene^ scene )
{
	SceneLimits^ sceneLimits = gcnew SceneLimits();
	
	scene->UnmanagedPointer->getLimits( *sceneLimits->_sceneLimits );
	
	return sceneLimits;
}

SceneLimits::operator NxSceneLimits( SceneLimits^ sceneLimits )
{
	NxSceneLimits limits;
		limits.maxNbActors = sceneLimits->MaximumActors;
		limits.maxNbBodies = sceneLimits->MaximumBodies;
		limits.maxNbDynamicShapes = sceneLimits->MaximumDynamicShapes;
		limits.maxNbJoints = sceneLimits->MaximumJoints;
		limits.maxNbStaticShapes = sceneLimits->MaximumStaticShapes;
	
	return limits;
}
SceneLimits::operator SceneLimits^( NxSceneLimits sceneLimits )
{
	SceneLimits^ limits = gcnew SceneLimits();
		limits->MaximumActors = sceneLimits.maxNbActors;
		limits->MaximumBodies = sceneLimits.maxNbBodies;
		limits->MaximumDynamicShapes = sceneLimits.maxNbDynamicShapes;
		limits->MaximumJoints = sceneLimits.maxNbJoints;
		limits->MaximumStaticShapes = sceneLimits.maxNbStaticShapes;
	
	return limits;
}

int SceneLimits::MaximumActors::get()
{
	return _sceneLimits->maxNbActors;
}
void SceneLimits::MaximumActors::set( int value )
{
	_sceneLimits->maxNbActors = value;
}

int SceneLimits::MaximumBodies::get()
{
	return _sceneLimits->maxNbBodies;
}
void SceneLimits::MaximumBodies::set( int value )
{
	_sceneLimits->maxNbBodies = value;
}

int SceneLimits::MaximumStaticShapes::get()
{
	return _sceneLimits->maxNbStaticShapes;
}
void SceneLimits::MaximumStaticShapes::set( int value )
{
	_sceneLimits->maxNbStaticShapes = value;
}

int SceneLimits::MaximumDynamicShapes::get()
{
	return _sceneLimits->maxNbDynamicShapes;
}
void SceneLimits::MaximumDynamicShapes::set( int value )
{
	_sceneLimits->maxNbDynamicShapes = value;
}

int SceneLimits::MaximumJoints::get()
{
	return _sceneLimits->maxNbJoints;
}
void SceneLimits::MaximumJoints::set( int value )
{
	_sceneLimits->maxNbJoints = value;
}

NxSceneLimits* SceneLimits::UnmanagedPointer::get()
{
	return _sceneLimits;
}