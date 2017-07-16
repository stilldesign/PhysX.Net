#pragma once


namespace PhysX
{
	/// <summary>
	/// Used to specify one of the degrees of freedom of a D6 joint.
	/// </summary>
	public enum class D6Axis
	{
		/// <summary>
		/// Motion along the X axis.
		/// </summary>
		X = PxD6Axis::eX,

		/// <summary>
		/// Motion along the Y axis.
		/// </summary>
		Y = PxD6Axis::eY,

		/// <summary>
		/// Motion along the Z axis.
		/// </summary>
		Z = PxD6Axis::eZ,

		/// <summary>
		/// Motion around the X axis.
		/// </summary>
		Twist = PxD6Axis::eTWIST,

		/// <summary>
		/// Motion around the Y axis.
		/// </summary>
		Swing1 = PxD6Axis::eSWING1,

		/// <summary>
		/// Motion around the Z axis.
		/// </summary>
		Swing2 = PxD6Axis::eSWING2
	};

	/// <summary>
	/// Used to specify the range of motions allowed for a degree of freedom in a D6 joint.
	/// </summary>
	public enum class D6Motion
	{
		/// <summary>
		/// The DOF is locked, it does not allow relative motion.
		/// </summary>
		Locked = PxD6Motion::eLOCKED,

		/// <summary>
		/// The DOF is limited, it only allows motion within a specific range.
		/// </summary>
		Limited = PxD6Motion::eLIMITED,

		/// <summary>
		/// The DOF is free and has its full range of motion.
		/// </summary>
		Free = PxD6Motion::eFREE
	};

	/// <summary>
	/// 
	/// </summary>
	public enum class D6JointDriveFlag
	{
		/// <summary>
		/// Drive spring is for the acceleration at the joint (rather than the force).
		/// </summary>
		Acceleration = PxD6JointDriveFlag::eACCELERATION
	};

	/// <summary>
	/// Used to specify which axes of a D6 joint are driven.
	/// Each drive is an implicit force-limited damped spring:
	///		force = spring * (target position - position) + damping * (targetVelocity - velocity)
	/// Alternatively, the spring may be configured to generate a specified acceleration instead of a force.
	/// A linear axis is affected by drive only if the corresponding drive flag is set. There are two
	/// possible models for angular drive: swing/twist, which may be used to drive one or more angular
	/// degrees of freedom, or slerp, which may only be used to drive all three angular degrees simultaneously.
	/// </summary>
	public enum class D6Drive
	{
		/// <summary>
		/// Drive along the X-axis.
		/// </summary>
		X = PxD6Drive::eX,

		/// <summary>
		/// Drive along the Y-axis.
		/// </summary>
		Y = PxD6Drive::eY,

		/// <summary>
		/// Drive along the Z-axis.
		/// </summary>
		Z = PxD6Drive::eZ,

		/// <summary>
		/// Drive of displacement from the X-axis.
		/// </summary>
		Swing = PxD6Drive::eSWING,

		/// <summary>
		/// Drive of the displacement around the X-axis.
		/// </summary>
		Twist = PxD6Drive::eTWIST,

		/// <summary>
		/// Drive of all three angular degrees along a SLERP-path.
		/// </summary>
		Slerp = PxD6Drive::eSLERP
	};

	/// <summary>
	/// 
	/// </summary>
	public enum class JointType
	{
		/// <summary>
		/// 
		/// </summary>
		D6 = PxJointConcreteType::eD6,

		/// <summary>
		/// 
		/// </summary>
		Distance = PxJointConcreteType::eDISTANCE,

		/// <summary>
		/// 
		/// </summary>
		Fixed = PxJointConcreteType::eFIXED,

		/// <summary>
		/// 
		/// </summary>
		Prismatic = PxJointConcreteType::ePRISMATIC,

		/// <summary>
		/// 
		/// </summary>
		Revolute = PxJointConcreteType::eREVOLUTE,

		/// <summary>
		/// 
		/// </summary>
		Spherical = PxJointConcreteType::eSPHERICAL
	};

	/// <summary>
	/// 
	/// </summary>
	public enum class DistanceJointFlag
	{
		/// <summary>
		/// 
		/// </summary>
		MaximumDistanceEnabled = PxDistanceJointFlag::eMAX_DISTANCE_ENABLED,

		/// <summary>
		/// 
		/// </summary>
		MinimumDistanceEnabled = PxDistanceJointFlag::eMIN_DISTANCE_ENABLED,

		/// <summary>
		/// 
		/// </summary>
		SpringEnabled = PxDistanceJointFlag::eSPRING_ENABLED
	};

	/// <summary>
	/// Flags specific to the prismatic joint.
	/// </summary>
	public enum class PrismaticJointFlag
	{
		/// <summary>
		/// 
		/// </summary>
		LimitEnabled = PxPrismaticJointFlag ::eLIMIT_ENABLED
	};

	/// <summary>
	/// Flags specific to the prismatic joint.
	/// </summary>
	[Flags]
	public enum class RevoluteJointFlag
	{
		/// <summary>
		/// Enable the limit.
		/// </summary>
		LimitEnabled = PxRevoluteJointFlag::eLIMIT_ENABLED,

		/// <summary>
		/// Enable the drive.
		/// </summary>
		DriveEnabled = PxRevoluteJointFlag::eDRIVE_ENABLED,

		/// <summary>
		/// If the existing velocity is beyond the drive velocity, do not add force.
		/// </summary>
		DriveFreeSpin = PxRevoluteJointFlag::eDRIVE_FREESPIN
	};

	/// <summary>
	/// Flags specific to the spherical joint.
	/// </summary>
	[Flags]
	public enum class SphericalJointFlag
	{
		/// <summary>
		/// The cone limit for the spherical joint is enabled  
		/// </summary>
		LimitEnabled = PxSphericalJointFlag::eLIMIT_ENABLED
	};
};