#pragma once

#include "ClothEnum.h"
#include "SimpleTriangleMesh.h"

namespace PhysX
{
	public ref class ClothMeshDesc
	{
	public:
		ClothMeshDesc();

	internal:
		static PxClothMeshDesc ToUnmanaged(ClothMeshDesc^ desc);

	public:
		void SetToDefault();
		bool IsValid();
		
		array<short>^ GetQuads16();
		array<int>^ GetQuads32();

		array<short>^ GetTriangles16();
		array<int>^ GetTriangles32();

		property array<Vector3>^ Points;
		property array<float>^ InverseMasses;
		property array<Byte>^ Quads;
		property array<Byte>^ Triangles;
		property MeshFlag Flags;
	};
};