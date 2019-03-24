#pragma once

#include "Geometry.h"
#include "MeshScale.h"

namespace PhysX
{
	ref class TriangleMesh;

	/// <summary>
	/// Triangle mesh geometry class.
	/// This class unifies a mesh object with a scaling transform, and lets the combined
	/// object be used anywhere a PxGeometry is needed.
	/// 
	/// The scaling is a transform along arbitrary axes contained in the scale object.
	/// The vertices of the mesh in geometry (or shape) space is the PxMeshScale::toMat33()
	/// transform, multiplied by the vertex space vertices in the ConvexMesh object.
	/// </summary>
	public ref class TriangleMeshGeometry : Geometry
	{
		public:
			TriangleMeshGeometry();
			TriangleMeshGeometry(PhysX::TriangleMesh^ triangleMesh, [Optional] Nullable<MeshScale> scaling, [Optional] Nullable<MeshGeometryFlag> flags);

		internal:
			virtual PxGeometry* ToUnmanaged() override;
			static TriangleMeshGeometry^ ToManaged(PxTriangleMeshGeometry triangleMesh);

		public:
			property MeshScale Scale;

			property MeshGeometryFlag MeshFlags;

			property PhysX::TriangleMesh^ TriangleMesh;
	};
};