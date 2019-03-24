#pragma once

#include <PxBroadPhase.h>

namespace PhysX
{
	ref class BroadPhaseCallback;
};

class InternalBroadPhaseCallback : public PxBroadPhaseCallback
{
private:
	gcroot<PhysX::BroadPhaseCallback^> _managed;

public:
	InternalBroadPhaseCallback(gcroot<PhysX::BroadPhaseCallback^> managed);

	virtual void onObjectOutOfBounds(PxShape &shape, PxActor &actor);
	virtual void onObjectOutOfBounds(PxAggregate &aggregate);
};

namespace PhysX
{
	ref class Shape;
	ref class Actor;
	ref class Aggregate;

	public ref class BroadPhaseCallback abstract
	{
	private:
		InternalBroadPhaseCallback* _internal;

	public:
		BroadPhaseCallback();
		~BroadPhaseCallback();
	protected:
		!BroadPhaseCallback();

	public:
		virtual void OnObjectOutOfBounds(Shape^ shape, Actor^ actor) abstract;
		virtual void OnObjectOutOfBounds(Aggregate^ aggregate) abstract;

	internal:
		property PxBroadPhaseCallback* UnmanagedPointer
		{
			PxBroadPhaseCallback* get();
		}
	};
};