#pragma once

#include "Joint.h"
#include "JointEnum.h"

namespace PhysX
{
	ref class JointLinearLimit;
	ref class JointAngularLimitPair;
	ref class JointLimitCone;
	ref class D6JointDrive;

	/// <summary>
	/// A D6 joint is a general constraint between two actors.
	/// </summary>
	public ref class D6Joint : Joint
	{
	internal:
		D6Joint(PxD6Joint* joint, PhysX::Physics^ owner);

	public:
		/// <summary>
		/// Get the motion type around the specified axis.
		/// </summary>
		/// <param name="axis">The degree of freedom around which the motion type is specified.</param>
		/// <returns>The motion type around the specified axis</returns>
		D6Motion GetMotion(D6Axis axis);
		/// <summary>
		/// Set the motion type around the specified axis.
		/// Each axis may independently specify that the degree of freedom is locked (blocking relative movement
		/// along or around this axis), limited by the corresponding limit, or free.
		/// </summary>
		/// <param name="axis">The axis around which motion is specified.</param>
		/// <param name="motion">The motion type around the specified axis.</param>
		void SetMotion(D6Axis axis, D6Motion motion);

		/// <summary>
		/// Get the drive parameters for the specified drive type. 
		/// </summary>
		D6JointDrive^ GetDrive(D6Drive index);
		/// <summary>
		/// Set the drive parameters for the specified drive type.
		/// </summary>
		/// <remarks>
		/// The default drive spring and damping values are zero, the force limit is zero, and no flags are set.
		/// </remarks>
		void SetDrive(D6Drive index, D6JointDrive^ drive);

		//

		/// <summary>
		/// Gets or sets the linear limit for the joint.
		/// </summary>
		property JointLinearLimit^ LinearLimit
		{
			JointLinearLimit^ get();
			void set(JointLinearLimit^ value);
		}

		/// <summary>
		/// Gets or sets the twist limit for the joint.
		/// </summary>
		property JointAngularLimitPair^ TwistLimit
		{
			JointAngularLimitPair^ get();
			void set(JointAngularLimitPair^ value);
		}

		/// <summary>
		/// Gets or sets the swing cone limit for the joint. 
		/// </summary>
		property JointLimitCone^ SwingLimit
		{
			JointLimitCone^ get();
			void set(JointLimitCone^ value);
		}

		/// <summary>
		/// Gets or sets the drive goal pose.
		/// </summary>
		property Matrix DrivePosition
		{
			Matrix get();
			void set(Matrix value);
		}

		/// <summary>
		/// Gets or sets the target goal velocity for the drive.
		/// </summary>
		property Vector3 DriveLinearVelocity
		{
			Vector3 get();
			void set(Vector3 value);
		}

		/// <summary>
		/// Gets or sets the target goal velocity for the drive.
		/// </summary>
		property Vector3 DriveAngularVelocity
		{
			Vector3 get();
			void set(Vector3 value);
		}

		/// <summary>
		/// Gets or sets the linear tolerance threshold for projection.
		/// Projection is enabled if ConstraintFlag::Projection is set for the joint.
		/// </summary>
		property float ProjectionLinearTolerance
		{
			float get();
			void set(float value);
		}

		/// <summary>
		/// Gets or sets the angular tolerance threshold for projection.
		/// Projection is enabled if ConstraintFlag::Projection is set for the joint.
		/// </summary>
		property float ProjectionAngularTolerance
		{
			float get();
			void set(float value);
		}

	internal:
		property PxD6Joint* UnmanagedPointer
		{
			virtual PxD6Joint* get() new;
		}
	};
};