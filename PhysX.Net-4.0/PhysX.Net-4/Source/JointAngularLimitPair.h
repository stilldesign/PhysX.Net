#pragma once

#include "JointLimitParameters.h"
#include "Spring.h"

namespace PhysX
{
	public ref class JointAngularLimitPair : JointLimitParameters
	{
	private:
		JointAngularLimitPair(PxJointAngularLimitPair* unmanaged);
	public:
		JointAngularLimitPair(float lowerLimit, float upperLimit, [Optional] Nullable<float> contactDistance);
		JointAngularLimitPair(float lowerLimit, float upperLimit, Spring spring);
	public:
		~JointAngularLimitPair();
	protected:
		!JointAngularLimitPair();

	internal:
		static JointAngularLimitPair^ ToManaged(PxJointAngularLimitPair unmanaged);
		static PxJointAngularLimitPair ToUnmanaged(JointAngularLimitPair^ managed);

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
		property PxJointAngularLimitPair* UnmanagedPointer
		{
			PxJointAngularLimitPair* get();
		}
	};
}