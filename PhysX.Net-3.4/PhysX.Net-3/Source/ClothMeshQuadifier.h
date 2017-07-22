#pragma once

namespace PhysX
{
	ref class ClothMeshDesc;

	public ref class ClothMeshQuadifier abstract sealed
	{
	public:
		static ClothMeshDesc^ GetDescriptor(ClothMeshDesc^ clothMeshDesc);
	};
}