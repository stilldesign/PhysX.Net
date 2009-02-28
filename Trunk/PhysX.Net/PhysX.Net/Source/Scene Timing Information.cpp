#include "StdAfx.h"

#include "Scene Timing Information.h"

using namespace StillDesign::PhysX;

float SceneTimingInformation::MaximumTimestep::get()
{
	return _maxTimestep;
}
void SceneTimingInformation::MaximumTimestep::set( float value )
{
	_maxTimestep = value;
}

int SceneTimingInformation::MaximumIterations::get()
{
	return _maxIterations;
}
void SceneTimingInformation::MaximumIterations::set( int value )
{
	_maxIterations = value;
}

StillDesign::PhysX::TimestepMethod SceneTimingInformation::TimestepMethod::get()
{
	return _timestepMethod;
}
void SceneTimingInformation::TimestepMethod::set( StillDesign::PhysX::TimestepMethod value )
{
	_timestepMethod = value;
}

int SceneTimingInformation::NumberOfSubSteps::get()
{
	return _subSteps;
}
void SceneTimingInformation::NumberOfSubSteps::set( int value )
{
	_subSteps = value;
}