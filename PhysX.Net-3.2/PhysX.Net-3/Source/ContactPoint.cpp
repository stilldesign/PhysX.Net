#include "StdAfx.h"
#include "ContactPoint.h"

// Note: PxContactPoint causes a C2711, so we pass the argument in by ref to be fill instead of returning.
void ContactPoint::ToUnmanaged(ContactPoint point, PxContactPoint& p)
{
	p.separation = point.Separation;
	p.internalFaceIndex0 = point.InternalFaceIndex0;
	p.internalFaceIndex1 = point.InternalFaceIndex1;
}
ContactPoint ContactPoint::ToManaged(PxContactPoint& point)
{
	ContactPoint p;
		p.Separation = point.separation;
		p.InternalFaceIndex0 = point.internalFaceIndex0;
		p.InternalFaceIndex1 = point.internalFaceIndex1;

	return p;
}