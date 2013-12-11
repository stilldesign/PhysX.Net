#pragma once

#include "Plane.h"
//#include <PxConvexMesh.h> 

namespace PhysX
{
	public ref class HullPolygon
	{
		internal:
			static PxHullPolygon ToUnmanaged(HullPolygon^ hullPolygon);
			static HullPolygon^ ToManaged(PxHullPolygon hullPolygon);

		public:
			property PhysX::Math::Plane Plane;
			property int NumberOfVertices;
			property int IndexBase;
	};
};