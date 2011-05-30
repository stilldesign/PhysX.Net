#pragma once

#include "GeometryUtilEnum.h"
#include <PxSimpleTriangleMesh.h> 

namespace PhysX
{
	/// <summary>
	/// A structure describing a triangle mesh.
	/// </summary>
	public ref class SimpleTriangleMesh
	{
		private:
			Array^ _triangles;
			bool _is16BitTriangles;

			array<Vector3>^ _positions;

		public:
			SimpleTriangleMesh();

		internal:
			static SimpleTriangleMesh^ ToManaged(PxSimpleTriangleMesh desc);
			static PxSimpleTriangleMesh ToUnmanaged(SimpleTriangleMesh^ desc);

		public:
			generic<typename T> where T : value class
			array<T>^ GetTriangles();
			generic<typename T> where T : value class
			void SetTriangles(array<T>^ triangles);

			array<Vector3>^ GetPositions();
			void SetPositions(array<Vector3>^ positions);

			property MeshFlag Flags;

			/// <summary>
			/// Gets whether the triangles are stored as short or int values.
			/// </summary>
			property bool Is16BitTriangles
			{
				bool get();
			}
	};
};