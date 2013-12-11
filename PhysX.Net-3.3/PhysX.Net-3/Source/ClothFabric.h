#pragma once

#include "Physics.h"
#include "ClothEnum.h"
#include "ClothFabricPhase.h"
//#include <PxClothFabric.h> 

namespace PhysX
{
	ref class Serializable;

	public ref class ClothFabric : IDisposable
	{
	public:
		/// <summary>Raised before any disposing is performed.</summary>
		virtual event EventHandler^ OnDisposing;
		/// <summary>Raised once all disposing is performed.</summary>
		virtual event EventHandler^ OnDisposed;

	private:
		PxClothFabric* _clothFabric;

	internal:
		ClothFabric(PxClothFabric* clothFabric, PhysX::Physics^ owner);
	public:
		~ClothFabric();
	protected:
		!ClothFabric();

	public:
		property bool Disposed
		{
			virtual bool get();
		}

		array<ClothFabricPhase>^ GetPhases();

		array<int>^ GetSets();

		array<int>^ GetParticleIndices();

		array<float>^ GetRestValues();

		ClothFabricPhaseType GetPhaseType(int phaseIndex);

		array<int>^ GetTetherAnchors();
		array<float>^ GetTetherLengths();

		void ScaleRestLengths(float scale);

		/// <summary>
		/// Gets an object which is responsible for serialization of this type.
		/// </summary>
		Serializable^ AsSerializable();

		//

		property int NumberOfParticles
		{
			int get();
		}

		property int NumberOfPhases
		{
			int get();
		}

		property int NumberOfRestValues
		{
			int get();
		}

		property int NumberOfSets
		{
			int get();
		}

		property int NumberOfParticleIndices
		{
			int get();
		}

		property int NumberOfTethers
		{
			int get();
		}

		property int ReferenceCount
		{
			int get();
		}

	internal:
		property PxClothFabric* UnmanagedPointer
		{
			PxClothFabric* get();
		}
	};
};