#pragma once

#include "JointEnum.h"

namespace PhysX
{
	public ref class D6JointDrive
	{
		internal:
			static D6JointDrive^ ToManaged(PxD6JointDrive drive);
			static PxD6JointDrive ToUnmanaged(D6JointDrive^ drive);

		public:
			D6JointDrive();
			D6JointDrive(float driveStiffness, float driveDamping, float forceLimit, bool isAcceleration);

			/// <summary>
			/// 
			/// </summary>
			property float Stiffness;

			/// <summary>
			/// 
			/// </summary>
			property float Damping;

			/// <summary>
			/// The force limit of the drive - may be an impulse or a force depending on ConstraintFlag.DriveLimitsAreForces.
			/// </summary>
			property float ForceLimit;

			/// <summary>
			/// 
			/// </summary>
			property D6JointDriveFlag Flags;
	};
};