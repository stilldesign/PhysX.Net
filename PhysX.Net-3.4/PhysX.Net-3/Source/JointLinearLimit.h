#pragma once

#include "JointLimitParameters.h"
#include "Spring.h"
#include "TolerancesScale.h"

namespace PhysX
{
	/// <summary>
	/// Describes a one-sided linear limit.
	/// </summary>
	public ref class JointLinearLimit : JointLimitParameters
	{
	private:
		JointLinearLimit(PxJointLinearLimit* unmanaged);
	public:
		JointLinearLimit(TolerancesScale scale, float extent, [Optional] Nullable<float> contactDistance);
		JointLinearLimit(float extent, Spring spring);
		~JointLinearLimit();
	protected:
		!JointLinearLimit();

	internal:
		static JointLinearLimit^ ToManaged(PxJointLinearLimit unmanaged);
		static PxJointLinearLimit ToUnmanaged(JointLinearLimit^ managed);

	public:
		property float Value
		{
			float get();
			void set(float value);
		}

		//

	internal:
		property PxJointLinearLimit* UnmanagedPointer
		{
			PxJointLinearLimit* get();
		}
	};
};