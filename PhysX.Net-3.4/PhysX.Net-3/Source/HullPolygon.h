#pragma once

namespace PhysX
{
	public ref class HullPolygon
	{
		internal:
			static PxHullPolygon ToUnmanaged(HullPolygon^ hullPolygon);
			static HullPolygon^ ToManaged(PxHullPolygon hullPolygon);

		public:
			property Plane Plane;
			property int NumberOfVertices;
			property int IndexBase;
	};
};