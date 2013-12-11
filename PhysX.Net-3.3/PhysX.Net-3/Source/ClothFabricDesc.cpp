#include "StdAfx.h"
#include "ClothFabricDesc.h"

PxClothFabricDesc ClothFabricDesc::ToUnmanaged(ClothFabricDesc^ managed)
{
	ThrowIfNull(managed, "managed");
	if (managed->TetherAnchors != nullptr && managed->TetherLengths != nullptr)
	{
		if (managed->TetherAnchors->Length != managed->TetherLengths->Length)
			throw gcnew InvalidOperationException("The length of the tether arrays (TetherAnchors and TetherLengths) must be the same");
	}

	PxClothFabricDesc unmanaged;

		if (managed->Indices != nullptr)
		{
			unmanaged.indices = new PxU32[managed->Indices->Length];
			Util::AsUnmanagedArray(managed->Indices, (void*)unmanaged.indices);
		}

		unmanaged.nbParticles = managed->NumberOfParticles;

		if (managed->Phases != nullptr)
		{
			unmanaged.nbPhases = managed->Phases->Length;
			unmanaged.phases = new PxClothFabricPhase[managed->Phases->Length];
			Util::AsUnmanagedArray(managed->Phases, (void*)unmanaged.phases);
		}

		if (managed->Sets != nullptr)
		{
			unmanaged.nbSets = managed->Sets->Length;
			unmanaged.sets = new PxU32[managed->Sets->Length];
			Util::AsUnmanagedArray(managed->Sets, (void*)unmanaged.sets);
		}

		if (managed->TetherAnchors != nullptr && managed->TetherLengths != nullptr)
		{
			unmanaged.nbTethers = managed->TetherAnchors->Length;

			unmanaged.tetherAnchors = new PxU32[managed->TetherAnchors->Length];
			Util::AsUnmanagedArray(managed->TetherAnchors, (void*)unmanaged.tetherAnchors);

			unmanaged.tetherLengths = new float[managed->TetherLengths->Length];
			Util::AsUnmanagedArray(managed->TetherLengths, (void*)unmanaged.tetherLengths);
		}

		if (managed->RestValues != nullptr)
		{
			unmanaged.restvalues = new float[managed->Indices->Length / 2];
			Util::AsUnmanagedArray(managed->RestValues, (void*)unmanaged.restvalues);
		}

	return unmanaged;
}