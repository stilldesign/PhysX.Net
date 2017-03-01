#include "StdAfx.h"
#include "SceneSweepOperationObject.h"

SceneSweepOperationObject::SceneSweepOperationObject(PhysX::Geometry^ geometry, Matrix pose, [Optional] Nullable<PhysX::FilterData> filterData)
{
	this->Geometry = geometry;
	this->Pose = pose;
	this->FilterData = filterData;
}