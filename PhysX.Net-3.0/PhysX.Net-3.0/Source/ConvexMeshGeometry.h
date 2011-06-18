#pragma once

#include "Geometry.h"
#include "MeshScale.h"

class PxConvexMeshGeometry;

namespace PhysX
{
	ref class ConvexMesh;

	/// <summary>
	/// Convex mesh geometry class.
	/// This class unifies a convex mesh object with a scaling transform, and lets the combined object be
	/// used anywhere a Geometry is needed.
	/// </summary>
	public ref class ConvexMeshGeometry : Geometry
	{
		public:
			ConvexMeshGeometry();
			ConvexMeshGeometry(PhysX::ConvexMesh^ convexMesh, [Optional] Nullable<MeshScale> scale);

		internal:
			virtual PxGeometry* ToUnmanaged() override;

		public:
			property MeshScale Scale;
			property PhysX::ConvexMesh^ ConvexMesh;
	};
};