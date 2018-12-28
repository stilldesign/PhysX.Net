#pragma once

#include "CookingEnum.h"

namespace PhysX
{
	/// <summary>
	/// Descriptor class for ConvexMesh.
	/// </summary>
	public ref class ConvexMeshDesc
	{
		private:
			Array^ _triangles;
			bool _is16BitTriangles;

			array<Vector3>^ _positions;

		public:
			ConvexMeshDesc();

			bool IsValid();

		internal:
			static ConvexMeshDesc^ ToManaged(PxConvexMeshDesc desc);
			static PxConvexMeshDesc ToUnmanaged(ConvexMeshDesc^ desc);

		public:
			generic<typename T> where T : value class
			array<T>^ GetTriangles();
			generic<typename T> where T : value class
			void SetTriangles(array<T>^ triangles);

			array<Vector3>^ GetPositions();
			void SetPositions(array<Vector3>^ positions);

			property ConvexFlag Flags;

			/// <summary>
			/// Gets whether the triangles are stored as short or int values.
			/// </summary>
			property bool Is16BitTriangles
			{
				bool get();
			}
	};
};