#pragma once

//#include <PxQueryReport.h> 

namespace PhysX
{
	ref class RaycastHit;
};

class InternalRaycastCallback : public PxRaycastCallback
{
public:
	gcroot<Func<array<RaycastHit^>^, bool>^> _managedCallback;

	InternalRaycastCallback(PxRaycastHit *aTouches, PxU32 aMaxNbTouches);

	virtual PxAgain processTouches(const PxRaycastHit* buffer, PxU32 nbHits);
};