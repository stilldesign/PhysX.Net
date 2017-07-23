#include "StdAfx.h"
#include "SimulationFilterCallback.h"
#include "FilterData.h"

SimulationFilterCallback::SimulationFilterCallback()
{
	_callback = new InternalSimulationFilterCallback(this);
}
SimulationFilterCallback::~SimulationFilterCallback()
{
	this->!SimulationFilterCallback();
}
SimulationFilterCallback::!SimulationFilterCallback()
{
	SAFE_DELETE(_callback);
}

PxSimulationFilterCallback* SimulationFilterCallback::UnmanagedPointer::get()
{
	return _callback;
}

//

InternalSimulationFilterCallback::InternalSimulationFilterCallback(gcroot<PhysX::SimulationFilterCallback^> managed)
{
	_managed = managed;
}

PxFilterFlags InternalSimulationFilterCallback::pairFound(PxU32 pairID,
	PxFilterObjectAttributes attributes0, PxFilterData filterData0, const PxActor* a0, const PxShape* s0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1, const PxActor* a1, const PxShape* s1,
	PxPairFlags& pairFlags)
{
	auto a0_ = ObjectTable::Instance->TryGetObject<PhysX::Actor^>((intptr_t)a0);
	auto a1_ = ObjectTable::Instance->TryGetObject<PhysX::Actor^>((intptr_t)a1);

	auto s0_ = ObjectTable::Instance->TryGetObject<PhysX::Shape^>((intptr_t)s0);
	auto s1_ = ObjectTable::Instance->TryGetObject<PhysX::Shape^>((intptr_t)s1);

	auto result = _managed->PairFound(pairID,
		attributes0, FilterData::ToManaged(filterData0), a0_, s0_,
		attributes1, FilterData::ToManaged(filterData1), a1_, s0_,
		ToManagedEnum(PairFlag, pairFlags));

	pairFlags = ToUnmanagedEnum(PxPairFlag, result.PairFlags);

	return ToUnmanagedEnum(PxFilterFlag, result.FilterFlags);
}

void InternalSimulationFilterCallback::pairLost(PxU32 pairID,
	PxFilterObjectAttributes attributes0,
	PxFilterData filterData0,
	PxFilterObjectAttributes attributes1,
	PxFilterData filterData1,
	bool objectRemoved)
{
	_managed->PairLost(pairID,
		attributes0, FilterData::ToManaged(filterData0),
		attributes1, FilterData::ToManaged(filterData1),
		objectRemoved);
}

bool InternalSimulationFilterCallback::statusChange(PxU32& pairID, PxPairFlags& pairFlags, PxFilterFlags& filterFlags)
{
	auto result = _managed->StatusChange(pairID, ToManagedEnum(PairFlag, pairFlags), ToManagedEnum(FilterFlag, filterFlags));

	if (result.HasValue)
	{
		auto r = result.Value;

		pairID = r.PairId;
		pairFlags = ToUnmanagedEnum(PxPairFlag, r.PairFlags);
		filterFlags = ToUnmanagedEnum(PxFilterFlag, r.FilterFlags);

		return true;
	}
	else
	{
		return false;
	}
}