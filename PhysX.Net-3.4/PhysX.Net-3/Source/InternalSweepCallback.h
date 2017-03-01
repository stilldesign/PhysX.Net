#pragma once

namespace PhysX
{
	ref class SweepHit;
};

class InternalSweepCallback : public PxSweepCallback
{
private:
	gcroot<Func<array<SweepHit^>^, bool>^> _managedCallback;

public:
	InternalSweepCallback(PxSweepHit *aTouches, PxU32 aMaxNbTouches, gcroot<Func<array<SweepHit^>^, bool>^> managedCallback);

	virtual PxAgain processTouches(const PxSweepHit* buffer, PxU32 nbHits);
};