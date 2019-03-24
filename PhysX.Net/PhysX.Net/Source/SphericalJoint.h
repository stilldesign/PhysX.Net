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
			SphericalJoint(PxSphericalJoint* joint, PhysX::Physics^ owner);

		public:
			/// <summary>
			/// Gets a copy of the limit cone.
			/// </summary>
			JointLimitCone^ GetLimitCone();
			/// <summary>
			/// Sets the limit cone using the values supplied in the argument.
			/// </summary>
			void SetLimitCone(JointLimitCone^ limitCone);

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

			property float SwingYAngle
			{
				float get();
			}
			property float SwingZAngle
			{
				float get();
			}

		internal:
			property PxSphericalJoint* UnmanagedPointer
			{
				virtual PxSphericalJoint* get() new;
			}
	};
};