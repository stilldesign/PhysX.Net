#pragma once

#include <PxContact.h> 

namespace PhysX
{
	public value class ContactPoint
	{
	internal:
		static void ToUnmanaged(ContactPoint point, PxContactPoint& p);
		static ContactPoint ToManaged(PxContactPoint& point);

	public:
		property float Separation;
		property int InternalFaceIndex0;
		property int InternalFaceIndex1;
	};
};