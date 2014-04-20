#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public enum class JointType
		{
			Prismatic = NX_JOINT_PRISMATIC,
			Revolute = NX_JOINT_REVOLUTE,
			Cylindrical = NX_JOINT_CYLINDRICAL,
			Spherical = NX_JOINT_SPHERICAL,
			PointOnLine = NX_JOINT_POINT_ON_LINE,
			PointInPlane = NX_JOINT_POINT_IN_PLANE,
			Distance = NX_JOINT_DISTANCE,
			Pulley = NX_JOINT_PULLEY,
			Fixed = NX_JOINT_FIXED,
			D6 = NX_JOINT_D6
		};
		public enum class JointState
		{
			Unbound = NX_JS_UNBOUND,
			Simulating = NX_JS_SIMULATING,
			Broken = NX_JS_BROKEN
		};
		public enum class JointProjectionMode
		{
			None = NX_JPM_NONE,
			PointMinimumDistance = NX_JPM_POINT_MINDIST,
			LinearMinimumDistance = NX_JPM_LINEAR_MINDIST
		};
		
		[Flags]
		public enum class JointFlag
		{
			CollisionEnabled = NX_JF_COLLISION_ENABLED,
			Visualization = NX_JF_VISUALIZATION
		};
		
		[Flags]
		public enum class RevoluteJointFlag
		{
			LimitEnabled = NX_RJF_LIMIT_ENABLED,
			MotorEnabled = NX_RJF_MOTOR_ENABLED,
			SpringEnabled = NX_RJF_SPRING_ENABLED
		};
		
		[Flags]
		public enum class PulleyJointFlag
		{
			IsRigid = NX_PJF_IS_RIGID,
			MotorEnabled = NX_PJF_MOTOR_ENABLED
		};
		
		[Flags]
		public enum class DistanceJointFlag
		{
			EnforceMaximumDistance = NX_DJF_MAX_DISTANCE_ENABLED,
			EnforceMinimumDistance = NX_DJF_MIN_DISTANCE_ENABLED,
			EnableSpring = NX_DJF_SPRING_ENABLED
		};
		
		public enum class D6JointMotion
		{
			Locked = NX_D6JOINT_MOTION_LOCKED,
			Limited = NX_D6JOINT_MOTION_LIMITED,
			Free = NX_D6JOINT_MOTION_FREE
		};
		[Flags]
		public enum class D6JointFlag
		{
			SphericalLinearInterpolationDrive = NX_D6JOINT_SLERP_DRIVE,
			GearEnabled = NX_D6JOINT_GEAR_ENABLED
		};
		
		[Flags]
		public enum class SphericalJointFlag
		{
			TwistLimitEnabled = NX_SJF_TWIST_LIMIT_ENABLED,
			SwingLimitEnabled = NX_SJF_SWING_LIMIT_ENABLED,
			TwistSpringEnabled = NX_SJF_TWIST_SPRING_ENABLED,
			SwingSpringEnabled = NX_SJF_SWING_SPRING_ENABLED,
			JointSpringEnabled = NX_SJF_JOINT_SPRING_ENABLED,
			PerpendicularDirectionalConstraints = NX_SJF_PERPENDICULAR_DIR_CONSTRAINTS
		};
		
		public enum class JointAccelerationSpringType
		{
			Force = 0,
			Acceleration = 1
		};
	};
};