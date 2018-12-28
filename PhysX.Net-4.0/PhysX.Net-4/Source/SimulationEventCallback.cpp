#include "StdAfx.h"
#include "SimulationEventCallback.h"
#include "ConstraintInfo.h"
#include "ContactPair.h"
#include "ContactPairHeader.h"
#include "RigidBody.h"

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
	array<Actor^>^ a = ObjectTable::Instance->GetObjects<Actor^>((intptr_t*)actors, count);

	_callback->OnWake(a);
}
void InternalSimulationEventCallback::onSleep (PxActor **actors, PxU32 count)
{
	array<Actor^>^ a = ObjectTable::Instance->GetObjects<Actor^>((intptr_t*)actors, count);

	_callback->OnSleep(a);
}
void InternalSimulationEventCallback::onContact (const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs)
{
	auto ph = ContactPairHeader::ToManaged(pairHeader);

	auto p = gcnew array<ContactPair^>(nbPairs);
	for (unsigned int i = 0; i < nbPairs; i++)
	{
		PxContactPair x = pairs[i];

		p[i] = gcnew ContactPair(&x);
	}

	_callback->OnContact(ph, p);

	// The PhysX SDK docs clearly say not to hold onto objects passed into this function, as they will be invalid
	// after we exit this method.
	// As ContactPair class holds onto the pointer pass into it, that means our ContactPair instances must be disposed of.
	for each (auto x in p)
	{
		delete x;
	}
	p = nullptr;
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
void InternalSimulationEventCallback::onAdvance(const PxRigidBody*const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
{
	auto bodies = gcnew array<RigidBody^>(count);
	auto poses = gcnew array<Matrix4x4>(count);

	for (unsigned int i = 0; i < count; i++)
	{
		bodies[i] = ObjectTable::Instance->TryGetObject<RigidBody^>((intptr_t)bodyBuffer[i]);

		poses[i] = MathUtil::PxTransformToMatrix((PxTransform*)&(poseBuffer[i]));
	}

	_callback->OnAdvance(bodies, poses);
}

//

SimulationEventCallback::SimulationEventCallback()
{
	_callback = new InternalSimulationEventCallback(this);

	ObjectTable::Instance->Add((intptr_t)_callback, this, nullptr);
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
void SimulationEventCallback::OnContact(ContactPairHeader^ pairHeader, array<ContactPair^>^ pairs)
{

}
void SimulationEventCallback::OnTrigger(array<TriggerPair^>^ pairs)
{

}
void SimulationEventCallback::OnAdvance(array<RigidBody^>^ rigidBodies, array<Matrix4x4>^ poses)
{

}

PxSimulationEventCallback* SimulationEventCallback::UnmanagedPointer::get()
{
	return _callback;
}