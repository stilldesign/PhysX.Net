#pragma once

#include "JointLimitParameters.h"

namespace PhysX
{
	public ref class JointLimit : JointLimitParameters
	{
		internal:
			static JointLimit^ ToManaged(PxJointLimit* parameters);
			static PxJointLimit ToUnmanaged(JointLimit^ parameters);

		public:
			property float Value;

			property float LimitContactDistance;
	};
};