#pragma once

#include "GeometryUtilEnum.h"

namespace PhysX
{
	/// <summary>
	/// A structure describing a triangle mesh.
	/// </summary>
	public ref class SimpleTriangleMesh
	{
		private:
			Array^ _triangles;

		public:
			SimpleTriangleMesh();


		internal:
			void PopulateUnmanaged(PxSimpleTriangleMesh& mesh);

			static SimpleTriangleMesh^ ToManaged(PxSimpleTriangleMesh mesh);
			static PxSimpleTriangleMesh ToUnmanaged(SimpleTriangleMesh^ mesh);

		public:
			void SetToDefault();
			bool IsValid();

			/// <summary>
			/// Gets whether the triangles are stored as short or int values.
			/// </summary>
			Nullable<bool> Is16BitTriangleIndices();

			generic<typename T> where T : value class
			array<T>^ GetTriangles();
			generic<typename T> where T : value class
			void SetTriangles(array<T>^ triangles);

			property array<Vector3>^ Points;
			property Array^ Triangles
			{
				Array^ get();
				void set(Array^ value);
			}

			property MeshFlag Flags;
	};
};