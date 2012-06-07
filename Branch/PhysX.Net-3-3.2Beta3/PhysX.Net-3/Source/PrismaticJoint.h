#pragma once

#include "Joint.h"
#include "JointEnum.h"

namespace PhysX
{
	ref class JointLimitPair;

	/// <summary>
	/// A prismatic joint permits relative translational movement between two bodies along an axis, but no relative rotational movement.
	/// </summary>
	public ref class PrismaticJoint : Joint
	{
		internal:
			PrismaticJoint(PxPrismaticJoint* joint, PhysX::Scene^ owner);

		public:
			/// <summary>
			/// Gets or sets the joint upper limit parameters.
			/// </summary>
			property JointLimitPair^ Limit
			{
				JointLimitPair^ get();
				void set(JointLimitPair^ value);
			}

			/// <summary>
			/// Gets or sets the flags specific to the Prismatic Joint.
			/// </summary>
			property PrismaticJointFlag Flag
			{
				PrismaticJointFlag get();
				void set(PrismaticJointFlag value);
			}

			/// <summary>
			/// Gets or sets the linear tolerance threshold for projection.
			/// </summary>
			property float ProjectionLinearTolerance
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the angular tolerance threshold for projection. Projection is enabled
			/// if ConstraintFlag.Projection is set for the joint.
			/// </summary>
			property float ProjectionAngularTolerance
			{
				float get();
				void set(float value);
			}

		internal:
			property PxPrismaticJoint* UnmanagedPointer
			{
				virtual PxPrismaticJoint* get() new;
			}
	};
};