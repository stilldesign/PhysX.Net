#include "StdAfx.h"
#include "SimulationFilterShader.h"

// Define static variable
gcroot<PhysX::SimulationFilterShader^> UnmanagedSimulationFilterShader::Managed;

PxFilterFlags UnmanagedSimulationFilterShader::Filter(PxFilterObjectAttributes attributes0, PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, PxPairFlags &pairFlags, const void *constantBlock, PxU32 constantBlockSize)
{
	auto t = Managed->GetType();

	int adi = System::AppDomain::CurrentDomain->Id;

	auto p = IntPtr((intptr_t)constantBlock);
	auto a = Marshal::GetDelegateForFunctionPointer<Action^>(p);
	a->Invoke();
	
	//Managed->A();
	auto result = Managed->Filter(attributes0, FilterData::ToManaged(filterData0), attributes1, FilterData::ToManaged(filterData1));

	//pairFlags = ToUnmanagedEnum(PxPairFlag, result.PairFlags);

	//return ToUnmanagedEnum(PxFilterFlag, result.FilterFlag);

	pairFlags = PxPairFlag::eSOLVE_CONTACT;
	pairFlags |= PxPairFlag::eDETECT_DISCRETE_CONTACT;
	pairFlags |= PxPairFlag::eDETECT_CCD_CONTACT;

	pairFlags |= PxPairFlag::eCCD_LINEAR;

	return PxFilterFlags();
}