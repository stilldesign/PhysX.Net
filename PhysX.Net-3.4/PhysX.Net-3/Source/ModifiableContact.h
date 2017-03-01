#pragma once

#include "ExtendedContact.h"

namespace PhysX
{
	/// <summary>
	/// A modifiable contact point. This has additional fields per-contact to permit modification by user.
	/// </summary>
	public ref class ModifiableContact : ExtendedContact
	{
		internal:
			// Note: Use a pointer here as the CLR doesn't deal with native byte-aligned structs
			static PxModifiableContact* ToUnmanaged(ModifiableContact^ managed);
			//static ModifiableContact^ ToManaged(PxModifiableContact contact);

		public:
			/// <summary>
			/// The desired target velocity at the contact point in the direction of the contact normal. For resting
			/// contact, this is zero, or positive to make the objects pop apart.
			/// </summary>
			property Vector3 Normal;
			property float Restitution;
			property int MaterialFlags;
			property int MaterialIndex0;
			property int MaterialIndex1;
			property float StaticFriction;
			property float DynamicFriction;
	};
};