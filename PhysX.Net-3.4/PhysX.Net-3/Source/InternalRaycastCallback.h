#pragma once


namespace PhysX
{
	ref class RaycastHit;
};

class InternalRaycastCallback : public PxRaycastCallback
{
private:
	gcroot<Func<array<RaycastHit^>^, bool>^> _managedCallback;

public:
	InternalRaycastCallback(PxRaycastHit *aTouches, PxU32 aMaxNbTouches, gcroot<Func<array<RaycastHit^>^, bool>^> managedCallback);

	virtual PxAgain processTouches(const PxRaycastHit* buffer, PxU32 nbHits);
};