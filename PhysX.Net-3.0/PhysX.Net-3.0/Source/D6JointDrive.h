#pragma once

#include "JointEnum.h"
#include <PxD6Joint.h> 

namespace PhysX
{
	public ref class D6JointDrive
	{
		internal:
			static D6JointDrive^ ToManaged(PxD6JointDrive drive);
			static PxD6JointDrive ToUnmanaged(D6JointDrive^ drive);

		public:
			D6JointDrive();
			D6JointDrive(float driveSpring, float driveDamping, float forceLimit, bool isAcceleration);

			/// <summary>
			/// 
			/// </summary>
			property float Spring;

			/// <summary>
			/// 
			/// </summary>
			property float Damping;

			/// <summary>
			/// 
			/// </summary>
			property float ForceLimit;

			/// <summary>
			/// 
			/// </summary>
			property D6JointDriveFlag Flags;
	};
};