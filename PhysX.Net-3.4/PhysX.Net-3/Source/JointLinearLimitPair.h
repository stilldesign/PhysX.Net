#pragma once

#include "JointLimitParameters.h"
#include "Spring.h"
#include "TolerancesScale.h"

namespace PhysX
{
	public ref class JointLinearLimitPair : JointLimitParameters
	{
	private:
		JointLinearLimitPair(PxJointLinearLimitPair* unmanaged);
	public:
		JointLinearLimitPair(TolerancesScale scale, float lowerLimit, float upperLimit, [Optional] Nullable<float> contactDistance);
		JointLinearLimitPair(float lowerLimit, float upperLimit, Spring spring);
	public:
		~JointLinearLimitPair();
	protected:
		!JointLinearLimitPair();

	internal:
		static JointLinearLimitPair^ ToManaged(PxJointLinearLimitPair unmanaged);
		static PxJointLinearLimitPair ToUnmanaged(JointLinearLimitPair^ managed);

	public:
		property float Upper
		{
			float get();
			void set(float value);
		}
		property float Lower
		{
			float get();
			void set(float value);
		}

	internal:
		property PxJointLinearLimitPair* UnmanagedPointer
		{
			PxJointLinearLimitPair* get();
		}
	};
};