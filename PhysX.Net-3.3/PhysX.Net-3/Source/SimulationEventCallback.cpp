#include "StdAfx.h"
#include "SimulationEventCallback.h"
#include "ConstraintInfo.h"

using namespace PhysX;

InternalSimulationEventCallback::InternalSimulationEventCallback(gcroot<SimulationEventCallback^> callback)
{
	_callback = callback;
}

void InternalSimulationEventCallback::onConstraintBreak (PxConstraintInfo *constraints, PxU32 count)
{
	auto c = gcnew array<ConstraintInfo^>(count);

	for (unsigned int i = 0; i < count; i++)
	{
		c[i] = ConstraintInfo::ToManaged(&constraints[i]);
	}

	_callback->OnConstraintBreak(c);
}
void InternalSimulationEventCallback::onWake (PxActor **actors, PxU32 count)
{
	array<Actor^>^ a = ObjectTable::GetObjects<Actor^>((intptr_t*)actors, count);

	_callback->OnWake(a);
}
void InternalSimulationEventCallback::onSleep (PxActor **actors, PxU32 count)
{
	array<Actor^>^ a = ObjectTable::GetObjects<Actor^>((intptr_t*)actors, count);

	_callback->OnSleep(a);
}
void InternalSimulationEventCallback::onContact (const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs)
{

}
void InternalSimulationEventCallback::onTrigger (PxTriggerPair *pairs, PxU32 count)
{
	auto p = gcnew array<TriggerPair^>(count);

	for (unsigned int i = 0; i < count; i++)
	{
		p[i] = TriggerPair::ToManaged(pairs[i]);
	}

	_callback->OnTrigger(p);
}

//

SimulationEventCallback::SimulationEventCallback()
{
	_callback = new InternalSimulationEventCallback(this);

	ObjectTable::Add((intptr_t)_callback, this, nullptr);
}
SimulationEventCallback::~SimulationEventCallback()
{
	this->!SimulationEventCallback();
}
SimulationEventCallback::!SimulationEventCallback()
{
	OnDisposing(this, nullptr);

	SAFE_DELETE(_callback);

	OnDisposed(this, nullptr);
}

bool SimulationEventCallback::Disposed::get()
{
	return (_callback == NULL);
}

void SimulationEventCallback::OnConstraintBreak(array<ConstraintInfo^>^ constraints)
{

}
void SimulationEventCallback::OnWake(array<Actor^>^ actors)
{

}
void SimulationEventCallback::OnSleep(array<Actor^>^ actors)
{

}
//virtual void OnContact (const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs);
void SimulationEventCallback::OnTrigger(array<TriggerPair^>^ pairs)
{

}

PxSimulationEventCallback* SimulationEventCallback::UnmanagedPointer::get()
{
	return _callback;
}