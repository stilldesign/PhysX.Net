#pragma once

#include "SimpleContact.h"

namespace PhysX
{
	/// <summary>
	/// Extended contact point data including face (feature) indices.
	/// </summary>
	public ref class ExtendedContact : SimpleContact
	{
	internal:
		static PxExtendedContact* ToUnmanaged(ExtendedContact^ managed);
		static ExtendedContact^ ToManaged(PxExtendedContact* unmanaged);

	protected:
		static void PopulateUnmanaged(ExtendedContact^ managed, PxExtendedContact* unmanaged);

	public:
		/// <summary>
		/// Face index on shape A.
		/// </summary>
		property Vector3 TargetVelocity;
		/// <summary>
		/// Face index on shape B.
		/// </summary>
		property float MaxImpulse;
	};
};