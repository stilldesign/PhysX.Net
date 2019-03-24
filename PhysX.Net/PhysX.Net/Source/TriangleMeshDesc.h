#pragma once

#include "SimpleTriangleMesh.h"
#include "CookingEnum.h"

namespace PhysX
{
	/// <summary>
	/// Descriptor class for TriangleMeshDesc.
	/// </summary>
	public ref class TriangleMeshDesc : SimpleTriangleMesh
	{
		public:
			TriangleMeshDesc();

		internal:
			static TriangleMeshDesc^ ToManaged(PxTriangleMeshDesc desc);
			static PxTriangleMeshDesc ToUnmanaged(TriangleMeshDesc^ desc);

		public:
			void SetToDefault();
			bool IsValid();

			property array<short>^ MaterialIndices;
	};
};