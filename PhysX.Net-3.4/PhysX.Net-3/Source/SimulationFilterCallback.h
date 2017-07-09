#pragma once

#include "Actor.h"
#include "TriggerPair.h"
#include "ConstraintInfo.h"

class InternalSimulationFilterCallback;

namespace PhysX
{
	value class FilterData;
	value class SimulationFilterCallbackResult;

	public ref class SimulationFilterCallback abstract
	{
	public:
		value class PairFoundResult
		{
		public:
			property PhysX::FilterFlag FilterFlags;
			property PhysX::PairFlag PairFlags;
		};

		value class StatusChangeResult
		{
		public:
			property int PairId;
			property PairFlag PairFlags;
			property int FilterFlags;
		};

		//

	private:
		InternalSimulationFilterCallback* _callback;

	public:
		SimulationFilterCallback();
		~SimulationFilterCallback();
	protected:
		!SimulationFilterCallback();

	public:
		virtual PairFoundResult PairFound(
			int pairId,
			int attributes0, FilterData filterData0, Actor^ a0, Shape^ s0,
			int attributes1, FilterData filterData1, Actor^ a1, Shape^ s1,
			PairFlag pairFlags) abstract;

		virtual void PairLost(int pairId,
			int attributes0,
			FilterData filterData0,
			int attributes1,
			FilterData filterData1,
			bool objectRemoved) abstract;

		virtual Nullable<StatusChangeResult> StatusChange(int pairId, PairFlag pairFlags, FilterFlag filterFlags) abstract;

	internal:
		property PxSimulationFilterCallback* UnmanagedPointer
		{
			PxSimulationFilterCallback* get();
		}
	};
}

class InternalSimulationFilterCallback : public PxSimulationFilterCallback
{
private:
	gcroot<PhysX::SimulationFilterCallback^> _managed;

public:
	InternalSimulationFilterCallback(gcroot<PhysX::SimulationFilterCallback^> managed);

	virtual PxFilterFlags pairFound(PxU32 pairID,
		PxFilterObjectAttributes attributes0, PxFilterData filterData0, const PxActor* a0, const PxShape* s0,
		PxFilterObjectAttributes attributes1, PxFilterData filterData1, const PxActor* a1, const PxShape* s1,
		PxPairFlags& pairFlags);

	virtual void pairLost(PxU32 pairID,
		PxFilterObjectAttributes attributes0,
		PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,
		PxFilterData filterData1,
		bool objectRemoved);

	virtual bool statusChange(PxU32& pairID, PxPairFlags& pairFlags, PxFilterFlags& filterFlags);
};