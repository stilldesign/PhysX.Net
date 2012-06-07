#include "StdAfx.h"
#include "SceneSweepOperationObject.h"

SceneSweepOperationObject::SceneSweepOperationObject(PhysX::Geometry^ geometry, Matrix pose, [Optional] Nullable<PhysX::FilterData> filterData)
{
	this->Geometry = Geometry;
	this->Pose = pose;
	this->FilterData = filterData;
}