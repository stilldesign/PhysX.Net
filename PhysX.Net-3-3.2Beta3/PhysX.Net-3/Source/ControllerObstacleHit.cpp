#include "StdAfx.h"
#include "ControllerObstacleHit.h"

ControllerObstacleHit^ ControllerObstacleHit::ToManaged(PxControllerObstacleHit hit)
{
	auto h = gcnew ControllerObstacleHit();
	
	CctHit::PopulateManaged(&hit, h);

	return h;
}