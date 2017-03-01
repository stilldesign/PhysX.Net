#pragma once

#include "Geometry.h"

namespace PhysX
{
	/// <summary>
	/// Class describing a plane geometry.
	/// The plane geometry has no properties.
	/// The plane equation is defined as normal=<1,0,0> and D = 0 relative to a reference frame.
	/// In the case of a PxShape, the shape local pose is the reference frame.
	/// </summary>
	public ref class PlaneGeometry : Geometry
	{
		public:
			PlaneGeometry();

		internal:
			virtual PxGeometry* ToUnmanaged() override;
			static PlaneGeometry^ ToManaged(PxPlaneGeometry plane);

		public:
			
	};
};