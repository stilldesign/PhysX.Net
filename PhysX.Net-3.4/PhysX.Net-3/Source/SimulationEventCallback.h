#pragma once

#include "Actor.h"
#include "TriggerPair.h"
#include "ConstraintInfo.h"

namespace PhysX
{
	ref class SimulationEventCallback;
	ref class ContactPairHeader;
	ref class ContactPair;
	ref class RigidBody;

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
		virtual void onAdvance(const PxRigidBody*const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count);
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

		/// <summary>
		/// The user needs to implement this interface class in order to be notified when certain contact events occur.
		/// The method will be called for a pair of actors if one of the colliding shape pairs requested contact notification.
		/// You request which events are reported using the filter shader / callback
		/// mechanism(see PxSimulationFilterShader, PxSimulationFilterCallback, PxPairFlag).
		/// Do not keep references to the passed objects, as they will be invalid after this function returns.
		/// </summary>
		virtual void OnContact (ContactPairHeader^ pairHeader, array<ContactPair^>^ pairs);
		virtual void OnTrigger(array<TriggerPair^>^ pairs);

		virtual void OnAdvance(array<RigidBody^>^ rigidBodies, array<Matrix4x4>^ poses);

	internal:
		property PxSimulationEventCallback* UnmanagedPointer
		{
			PxSimulationEventCallback* get();
		}
	};
};