#pragma once

#include <PxJointLimit.h> 

namespace PhysX
{
	/// <summary>
	/// Describes the parameters for a joint limit.
	/// Limits are enabled or disabled by setting flags or other configuration parameters joints, see the
	/// documentation for specific joint types for details.
	/// </summary>
	public ref class JointLimitParameters
	{
		protected:
			void PopulateUnmanaged(PxJointLimitParameters* parameters);
			void PopulateManaged(PxJointLimitParameters* parameters);

		internal:
			static JointLimitParameters^ ToManaged(PxJointLimitParameters* parameters);
			static PxJointLimitParameters* ToUnmanaged(JointLimitParameters^ parameters);

		public:
			/// <summary>
			/// Controls the amount of bounce when the joint hits a limit.
			/// </summary>
			property float Restitution;

			/// <summary>
			/// Gets or sets the spring. If greater than zero, the limit is soft, i.e. a spring pulls the joint back to the limit.
			/// </summary>
			property float Spring;

			/// <summary>
			/// If spring is greater than zero, this is the damping of the limit spring.
			/// </summary>
			property float Damping;

			/// <summary>
			/// The distance inside the limit value at which the limit will be considered to be active by the solver.
			/// </summary>
			property float ContactDistance;
	};
};