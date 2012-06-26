#pragma once

#include <PxController.h> 
#include <PxClient.h>
#include <PxCapsuleController.h>

namespace PhysX
{
	/// <summary>
	/// Multiclient behavior bit flags for clients.
	/// </summary>
	public enum class ClientBehaviorBit
	{
		TriggerNotify = PxClientBehaviorBit::eREPORT_FOREIGN_OBJECTS_TO_TRIGGER_NOTIFY,
		ContactNotify = PxClientBehaviorBit::eREPORT_FOREIGN_OBJECTS_TO_CONTACT_NOTIFY,
		ConstraintBreakNotify = PxClientBehaviorBit::eREPORT_FOREIGN_OBJECTS_TO_CONSTRAINT_BREAK_NOTIFY,
		SceneQuery = PxClientBehaviorBit::eREPORT_FOREIGN_OBJECTS_TO_SCENE_QUERY
	};

	/// <summary>
	/// Specifies which sides a character is colliding with.
	/// </summary>
	public enum class ControllerFlag
	{
		/// <summary>
		/// Character is colliding to the sides.
		/// </summary>
		Sides = PxControllerFlag::eCOLLISION_SIDES,

		/// <summary>
		/// Character has collision above.
		/// </summary>
		Up = PxControllerFlag::eCOLLISION_UP,

		/// <summary>
		/// Character has collision below.
		/// </summary>
		Down = PxControllerFlag::eCOLLISION_DOWN
	};

	/// <summary>
	/// Specifies how a CCT interacts with other CCTs.
	/// This member controls if a character controller will collide with another controller.
	/// There are 3 options: always collide, never collide and collide based on the shape group.
	/// This flag only affects other controllers when they move; when this controller moves, the
	/// flag is ignored and the flags of the other controllers determine collision.
	/// </summary>
	public enum class CCTInteractionMode
	{
		/// <summary>
		/// Always collide character controllers.
		/// </summary>
		Include = PxCCTInteractionMode::eINCLUDE,

		/// <summary>
		/// Never collide character controllers.
		/// </summary>
		Exclude = PxCCTInteractionMode::eEXCLUDE,

		/// <summary>
		/// Collide based on a group identifier stored in the shape collision filter data.
		/// </summary>
		UseFilter = PxCCTInteractionMode::eUSE_FILTER
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

	public enum CapsuleClimbingMode
	{
		/// <summary>
		/// Standard mode, let the capsule climb over surfaces according to impact normal.
		/// </summary>
		Easy = PxCapsuleClimbingMode::eEASY, 
		/// <summary>
		/// Constrained mode, try to limit climbing according to the step offset.
		/// </summary>
		Constrained = PxCapsuleClimbingMode::eCONSTRAINED,
		/// <summary>
		/// 
		/// </summary>
		Last = PxCapsuleClimbingMode::eLAST
	};

	//public enum class ControllerAction
	//{
	//	/// <summary>
	//	/// Don't apply forces to touched actor.
	//	/// </summary>
	//	None = PxControllerAction::eNONE,
	//	/// <summary>
	//	/// Automatically compute & apply forces to touched actor (push).
	//	/// </summary>
	//	Push = PxControllerAction::ePUSH
	//};

	public enum class ControllerType
	{
		PxControllerType
	};
};