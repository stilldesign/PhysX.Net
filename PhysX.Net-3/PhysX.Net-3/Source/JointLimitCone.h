#pragma once

#include "JointLimitParameters.h"

namespace PhysX
{
	/// <summary>
	/// Describes an elliptical conical joint limit. Note that very small or highly elliptical limit cones may result in jitter.
	/// </summary>
	public ref class JointLimitCone : JointLimitParameters
	{
	public:
		JointLimitCone();
		JointLimitCone(float yLimitAngle, float zLimitAngle, float limitContactDistance);

	internal:
		static JointLimitCone^ ToManaged(PxJointLimitCone* parameters);
		static PxJointLimitCone ToUnmanaged(JointLimitCone^ parameters);

	public:
		bool IsValid();

		/// <summary>
		/// The angle from the Y axis of the constraint frame position beyond which the limit is active.
		/// Unit: Angular: Radians Range: Angular: (0,PI)
		/// Default: PI/2
		/// </summary>
		property float YLimitAngle;

		/// <summary>
		/// The angle from the Z-axis of the constraint frame beyond which the limit is active.
		/// Unit: Angular: Radians Range: Angular: (0,PI)
		/// Default: PI/2
		/// </summary>
		property float ZLimitAngle;

		property float LimitContactDistance;
	};
};