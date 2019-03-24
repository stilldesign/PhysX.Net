#include "StdAfx.h"
#include "InternalSweepCallback.h"
#include "SweepHit.h"

InternalSweepCallback::InternalSweepCallback(PxSweepHit *aTouches, PxU32 aMaxNbTouches, gcroot<Func<array<SweepHit^>^, bool>^> managedCallback)
	: PxHitCallback<PxSweepHit>(aTouches, aMaxNbTouches)
{
	Func<array<SweepHit^>^, bool>^ c = managedCallback;

	if (c == nullptr)
		throw gcnew InvalidOperationException("The hit call back cannot be null");

	_managedCallback = managedCallback;
}

PxAgain InternalSweepCallback::processTouches(const PxSweepHit* buffer, PxU32 nbHits)
{
	auto managedHits = gcnew array<SweepHit^>(nbHits);

	for (unsigned int i = 0; i < nbHits; i++)
	{
		auto hit = SweepHit::ToManaged((PxSweepHit)buffer[i]);

		managedHits[i] = hit;
	}

	bool again = _managedCallback->Invoke(managedHits);

	return again;
}