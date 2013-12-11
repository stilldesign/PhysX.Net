#pragma once

//#include <PxQueryReport.h> 

namespace PhysX
{
	ref class OverlapHit;
};

class InternalOverlapCallback : public PxOverlapCallback
{
public:
	gcroot<Func<array<OverlapHit^>^, bool>^> _managedCallback;

	InternalOverlapCallback(PxOverlapHit *aTouches, PxU32 aMaxNbTouches);

	virtual PxAgain processTouches(const PxOverlapHit* buffer, PxU32 nbHits);
};