#pragma once


namespace PhysX
{
	ref class OverlapHit;
};

class InternalOverlapCallback : public PxOverlapCallback
{
private:
	gcroot<Func<array<OverlapHit^>^, bool>^> _managedCallback;

public:
	InternalOverlapCallback(PxOverlapHit *aTouches, PxU32 aMaxNbTouches, gcroot<Func<array<OverlapHit^>^, bool>^> managedCallback);

	virtual PxAgain processTouches(const PxOverlapHit* buffer, PxU32 nbHits);
};