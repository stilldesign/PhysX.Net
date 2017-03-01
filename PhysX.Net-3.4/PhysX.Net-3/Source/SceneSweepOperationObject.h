#pragma once

#include "FilterData.h"

namespace PhysX
{
	ref class Geometry;

	// TODO: Nicer name
	public ref class SceneSweepOperationObject
	{
		public:
			SceneSweepOperationObject(PhysX::Geometry^ geometry, Matrix pose, [Optional] Nullable<PhysX::FilterData> filterData);

			property PhysX::Geometry^ Geometry;
			property Matrix Pose;
			property Nullable<PhysX::FilterData> FilterData;
	};
};