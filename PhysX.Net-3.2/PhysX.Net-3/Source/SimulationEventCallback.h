#pragma once

#include "Actor.h"
#include "TriggerPair.h"
#include "ConstraintInfo.h"
#include <PxSimulationEventCallback.h>

namespace PhysX
{
	ref class SimulationEventCallback;

	class InternalSimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		InternalSimulationEventCallback(gcroot<SimulationEventCallback^> callback);

		gcroot<SimulationEventCallback^> _callback;

		virtual void onConstraintBreak (PxConstraintInfo *constraints, PxU32 count);
		virtual void onWake (PxActor **actors, PxU32 count);
		virtual void onSleep (PxActor **actors, PxU32 count);
		virtual void onContact (const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs);
		virtual void onTrigger (PxTriggerPair *pairs, PxU32 count);
	};

	public ref class SimulationEventCallback abstract : IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		PxSimulationEventCallback* _callback;

	public:
		SimulationEventCallback();
	public:
		~SimulationEventCallback();
	protected:
		!SimulationEventCallback();

	public:
		property bool Disposed
		{
			virtual bool get();
		}

		virtual void OnConstraintBreak (array<ConstraintInfo^>^ constraints);
		virtual void OnWake(array<Actor^>^ actors);
		virtual void OnSleep(array<Actor^>^ actors);
		//virtual void OnContact (const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs);
		virtual void OnTrigger(array<TriggerPair^>^ pairs);

	internal:
		property PxSimulationEventCallback* UnmanagedPointer
		{
			PxSimulationEventCallback* get();
		}
	};
};