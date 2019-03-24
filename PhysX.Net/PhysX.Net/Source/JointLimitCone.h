#pragma once

#include "JointLimitParameters.h"
#include "Spring.h"

namespace PhysX
{
	/// <summary>
	/// Describes an elliptical conical joint limit. Note that very small or highly elliptical limit cones may result in jitter.
	/// </summary>
	public ref class JointLimitCone : JointLimitParameters
	{
	private:
		JointLimitCone(PxJointLimitCone* unmanaged);
	public:
		JointLimitCone();
		JointLimitCone(float yLimitAngle, float zLimitAngle, [Optional] Nullable<float> contactDistance);
		JointLimitCone(float yLimitAngle, float zLimitAngle, Spring spring);
		~JointLimitCone();
	protected:
		!JointLimitCone();

	internal:
		static JointLimitCone^ ToManaged(PxJointLimitCone unmanaged);
		static PxJointLimitCone ToUnmanaged(JointLimitCone^ managed);

	public:
		/// <summary>
		/// The angle from the Y axis of the constraint frame position beyond which the limit is active.
		/// Unit: Angular: Radians Range: Angular: (0,PI)
		/// Default: PI/2
		/// </summary>
		property float YLimitAngle
		{
			float get();
			void set(float value);
		}

		/// <summary>
		/// The angle from the Z-axis of the constraint frame beyond which the limit is active.
		/// Unit: Angular: Radians Range: Angular: (0,PI)
		/// Default: PI/2
		/// </summary>
		property float ZLimitAngle
		{
			float get();
			void set(float value);
		}

		//

	internal:
		property PxJointLimitCone* UnmanagedPointer
		{
			PxJointLimitCone* get();
		}
	};
};