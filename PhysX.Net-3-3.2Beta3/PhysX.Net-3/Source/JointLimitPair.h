#pragma once

#include "JointLimitParameters.h"

namespace PhysX
{
	public ref class JointLimitPair : JointLimitParameters
	{
		internal:
			static JointLimitPair^ ToManaged(PxJointLimitPair* parameters);
			static PxJointLimitPair ToUnmanaged(JointLimitPair^ parameters);

		public:
			/// <summary>
			/// Gets or sets the range beyond which the limit is active. The upper limit must be now lower than the
			/// lower limit, and if they are equal the limited degree of freedom will be treated as locked.
			/// Unit: Angular: Radians Range: Angular: (-PI/2, PI/2)
			/// Range: Linear: [Single.MinValue, Single.MaxValue]
			/// Default: 0.0
			/// </summary>
			property float UpperLimit;

			property float LowerLimit;

			property float LimitContactDistance;
	};
};