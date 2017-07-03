#pragma once


namespace PhysX
{
	///// <summary>
	///// Multiclient behavior bit flags for clients.
	///// </summary>
	//public enum class ClientBehaviorBit
	//{
	//	TriggerNotify = PxClientBehaviorBit::eREPORT_FOREIGN_OBJECTS_TO_TRIGGER_NOTIFY,
	//	ContactNotify = PxClientBehaviorBit::eREPORT_FOREIGN_OBJECTS_TO_CONTACT_NOTIFY,
	//	ConstraintBreakNotify = PxClientBehaviorBit::eREPORT_FOREIGN_OBJECTS_TO_CONSTRAINT_BREAK_NOTIFY,
	//	SceneQuery = PxClientBehaviorBit::eREPORT_FOREIGN_OBJECTS_TO_SCENE_QUERY
	//};

	/// <summary>
	/// Specifies which sides a character is colliding with.
	/// </summary>
	[Flags]
	public enum class ControllerCollisionFlag
	{
		None = 0,

		/// <summary>
		/// Character is colliding to the sides.
		/// </summary>
		Sides = PxControllerCollisionFlag::eCOLLISION_SIDES,

		/// <summary>
		/// Character has collision above.
		/// </summary>
		Up = PxControllerCollisionFlag::eCOLLISION_UP,

		/// <summary>
		/// Character has collision below.
		/// </summary>
		Down = PxControllerCollisionFlag::eCOLLISION_DOWN
	};

	/// <summary>
	/// Specifies how a CCT interacts with other CCTs.
	/// This member controls if a character controller will collide with another controller.
	/// There are 3 options: always collide, never collide and collide based on the shape group.
	/// This flag only affects other controllers when they move; when this controller moves, the
	/// flag is ignored and the flags of the other controllers determine collision.
	/// </summary>
	//public enum class CCTInteractionMode
	//{
	//	/// <summary>
	//	/// Always collide character controllers.
	//	/// </summary>
	//	Include = PxCCTInteractionMode::eINCLUDE,

	//	/// <summary>
	//	/// Never collide character controllers.
	//	/// </summary>
	//	Exclude = PxCCTInteractionMode::eEXCLUDE,

	//	/// <summary>
	//	/// Collide based on a group identifier stored in the shape collision filter data.
	//	/// </summary>
	//	UseFilter = PxCCTInteractionMode::eUSE_FILTER
	//};

	public enum class ControllerNonWalkableMode
	{
		/// <summary>
		/// Stops character from climbing up non-walkable slopes, but doesn't move it otherwise.
		/// </summary>
		PreventClimbing = PxControllerNonWalkableMode::ePREVENT_CLIMBING,

		/// <summary>
		/// Stops character from climbing up non-walkable slopes, and forces it to slide down those slopes.
		/// </summary>
		PreventClimbingAndForceSliding = PxControllerNonWalkableMode::ePREVENT_CLIMBING_AND_FORCE_SLIDING
	};

	/// <summary>
	/// The type of controller, eg box, sphere or capsule.
	/// </summary>
	public enum class ControllerShapeType
	{
		/// <summary>
		/// A box controller.
		/// </summary>
		Box = PxControllerShapeType::eBOX,

		/// <summary>
		/// A capsule controller.
		/// </summary>
		Capsule = PxControllerShapeType::eCAPSULE
	};

	public enum class CapsuleClimbingMode
	{
		/// <summary>
		/// Standard mode, let the capsule climb over surfaces according to impact normal.
		/// </summary>
		Easy = PxCapsuleClimbingMode::eEASY, 
		/// <summary>
		/// Constrained mode, try to limit climbing according to the step offset.
		/// </summary>
		Constrained = PxCapsuleClimbingMode::eCONSTRAINED
	};
};