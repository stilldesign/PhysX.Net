#pragma once

#include "ClothEnum.h"
#include "SimpleTriangleMesh.h"
#include <PxClothMeshDesc.h> 

namespace PhysX
{
	public ref class ClothMeshDesc : SimpleTriangleMesh
	{
	public:
		ClothMeshDesc();

	internal:
		static PxClothMeshDesc ToUnmanaged(ClothMeshDesc^ desc);

	public:
		void SetToDefault();
		bool IsValid();
		
		/// <summary>
		/// Edge flags for cooking.
		/// </summary>
		property array<ClothMeshEdgeFlag>^ EdgeFlags;
		
		/// <summary>
		/// Vertex flags for cooking.
		/// </summary>
		property array<ClothMeshVertexFlag>^ VertexFlags;
	};
};