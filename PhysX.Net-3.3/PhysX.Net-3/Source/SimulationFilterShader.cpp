#include "StdAfx.h"
#include "SimulationFilterShader.h"

// Define static variable
gcroot<PhysX::SimulationFilterShader^> UnmanagedSimulationFilterShader::Managed;

PxFilterFlags UnmanagedSimulationFilterShader::Filter(PxFilterObjectAttributes attributes0, PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, PxPairFlags &pairFlags, const void *constantBlock, PxU32 constantBlockSize)
{
	auto result = Managed->Filter(attributes0, FilterData::ToManaged(filterData0), attributes1, FilterData::ToManaged(filterData1));

	pairFlags = ToUnmanagedEnum(PxPairFlag, result.PairFlags);

	return ToUnmanagedEnum(PxFilterFlag, result.FilterFlag);
}