#pragma once

#include "FilterData.h"
#include "PhysicsEnum.h"

class UnmanagedSimulationFilterShader;

namespace PhysX
{
	public value class FilterResult
	{
	public:
		PhysX::FilterFlag FilterFlag;
		PhysX::PairFlag PairFlags;
	};

	public ref class SimulationFilterShader abstract
	{
	protected:
		SimulationFilterShader()
		{

		}

	public:
		virtual FilterResult Filter(int attributes0, FilterData filterData0, int attributes1, FilterData filterData1) abstract;
	};
};

class UnmanagedSimulationFilterShader
{
public:
	// Declare our variable
	static gcroot<PhysX::SimulationFilterShader^> Managed;

	static PxFilterFlags Filter(PxFilterObjectAttributes attributes0, PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, PxPairFlags &pairFlags, const void *constantBlock, PxU32 constantBlockSize);
};