#pragma once

#include "Geometry.h"
#include "MeshScale.h"

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
			static ConvexMeshGeometry^ ToManaged(PxConvexMeshGeometry convexMesh);

		public:
			int FindFaceIndex(Matrix4x4 geometryPose, Vector3 impactPosition, Vector3 unitDirection);

			property MeshScale Scale;
			property PhysX::ConvexMesh^ ConvexMesh;
	};
};