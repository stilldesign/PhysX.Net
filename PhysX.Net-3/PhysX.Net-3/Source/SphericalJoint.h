#pragma once

#include "Joint.h"
#include "JointEnum.h"

namespace PhysX
{
	ref class JointLimitCone;

	/// <summary>
	/// A joint which behaves in a similar way to a ball and socket.
	/// </summary>
	public ref class SphericalJoint : Joint
	{
		internal:
			SphericalJoint(PxSphericalJoint* joint, PhysX::Scene^ owner);

		public:
			/// <summary>
			/// Gets or sets the limit cone.
			/// </summary>
			property JointLimitCone^ LimitCone
			{
				JointLimitCone^ get();
				void set(JointLimitCone^ value);
			}

			/// <summary>
			/// Gets or sets flags specific to the spherical joint.
			/// </summary>
			property SphericalJointFlag Flags
			{
				SphericalJointFlag get();
				void set(SphericalJointFlag value);
			}

			/// <summary>
			/// Gets or sets the linear tolerance threshold for projection.
			/// </summary>
			property float ProjectionLinearTolerance
			{
				float get();
				void set(float value);
			}

		internal:
			property PxSphericalJoint* UnmanagedPointer
			{
				virtual PxSphericalJoint* get() new;
			}
	};
};