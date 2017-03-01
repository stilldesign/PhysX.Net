#pragma once

#include "Joint.h"

namespace PhysX
{
	/// <summary>
	/// A fixed joint permits no relative movement between two bodies. ie the bodies are glued together.
	/// </summary>
	public ref class FixedJoint : Joint
	{
		internal:
			FixedJoint(PxFixedJoint* joint, PhysX::Physics^ owner);

		public:
			/// <summary>
			/// Gets or sets the linear tolerance threshold for projection.
			/// Projection is enabled if ConstraintFlag::Projection is set for the joint.
			/// </summary>
			property float ProjectionLinearTolerance
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the angular tolerance threshold for projection.
			/// Projection is enabled if ConstraintFlag::Projection is set for the joint.
			/// </summary>
			property float ProjectionAngularTolerance
			{
				float get();
				void set(float value);
			}

		internal:
			property PxFixedJoint* UnmanagedPointer
			{
				virtual PxFixedJoint* get() new;
			}
	};
};