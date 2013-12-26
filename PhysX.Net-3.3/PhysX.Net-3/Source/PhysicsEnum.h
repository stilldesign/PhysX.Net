#pragma once

//#include <PxLockedData.h>
//#include <PxMaterial.h>
//#include <PxErrors.h>
//#include <PxFiltering.h> 
//#include <PxSceneDesc.h>
//#include <PxBatchQueryDesc.h> 

namespace PhysX
{
	/// <summary>
	/// Flag that determines the combine mode. When two actors come in contact with each other, they each have materials
	/// with various coefficients, but we only need a single set of coefficients for the pair.
	/// Physics doesn't have any inherent combinations because the coefficients are determined empirically on a
	/// case by case basis. However, simulating this with a pairwise lookup table is often impractical.
	///
	///	For this reason the following combine behaviors are available:
	/// Average, Min, Multiply, Max
	///
	///	The effective combine mode for the pair is maximum(material0.combineMode, material1.combineMode).
	/// </summary>
	public enum class CombineMode
	{
		/// <summary>
		/// Average: (a + b)/2.
		/// </summary>
		Average = PxCombineMode::eAVERAGE,

		/// <summary>
		/// Minimum: minimum(a,b).
		/// </summary>
		Minimum = PxCombineMode::eMIN,

		/// <summary>
		/// Multiply: a*b.
		/// </summary>
		Multiply = PxCombineMode::eMULTIPLY,

		/// <summary>
		/// Maximum: maximum(a,b).
		/// </summary>
		Max = PxCombineMode::eMAX
	};

	public enum class DataAccessFlag
	{
		Readable = PxDataAccessFlag::eREADABLE,
		Writable = PxDataAccessFlag::eWRITABLE
	};

	/// <summary>
	/// Error codes.
	/// These error codes are passed to #PxErrorCallback.
	/// </summary>
	public enum class ErrorCode
	{
		NoError = PxErrorCode::eNO_ERROR,

		/// <summary>
		/// An informational message.
		/// </summary>
		DebugInfo = PxErrorCode::eDEBUG_INFO,

		/// <summary>
		/// A warning message for the user to help with debugging.
		/// </summary>
		Warning = PxErrorCode::eDEBUG_WARNING,

		/// <summary>
		/// Method called with invalid parameter(s).
		/// </summary>
		InvalidParameter = PxErrorCode::eINVALID_PARAMETER,

		/// <summary>
		/// Method was called at a time when an operation is not possible.
		/// </summary>
		InvalidOperation = PxErrorCode::eINVALID_OPERATION,

		/// <summary>
		/// Method failed to allocate some memory.
		/// </summary>
		OutOfMemory = PxErrorCode::eOUT_OF_MEMORY,

		/// <summary>
		/// The library failed for some reason.
		/// Possibly you have passed invalid values like NaNs, which are not checked for.
		/// </summary>
		InternalError = PxErrorCode::eINTERNAL_ERROR,
	};

	public enum class PairFlag
	{
		/// <summary>
		/// Process the contacts of this collision pair in the dynamics solver.
		/// Note: Only takes effect if the colliding actors are rigid bodies.  
		/// </summary>
		ResolveContacts = PxPairFlag::eRESOLVE_CONTACTS,

		/// <summary>
		/// Call contact modification callback for this collision pair.
		/// Note: Only takes effect if the colliding actors are rigid bodies.
		/// </summary>
		ModifyContacts = PxPairFlag::eMODIFY_CONTACTS,

		/// <summary>
		/// Call contact report callback or trigger callback when this collision pair starts to be in contact.
		/// If one of the two collision objects is a trigger shape (see PxShapeFlag::eTRIGGER_SHAPE) then the
		/// trigger callback will get called as soon as the other object enters the trigger volume.
		/// If none of the two collision objects is a trigger shape then the contact report callback will get
		/// called when the actors of this collision pair start to be in contact.
		/// Note: Only takes effect if the colliding actors are rigid bodies.
		/// </summary>
		NotifyTouchFound = PxPairFlag::eNOTIFY_TOUCH_FOUND,

		/// <summary>
		/// Call contact report callback or trigger callback while this collision pair is in contact.
		/// If one of the two collision objects is a trigger shape (see PxShapeFlag::eTRIGGER_SHAPE) then the
		/// trigger callback will get called as long as the other object stays within the trigger volume.
		/// If none of the two collision objects is a trigger shape then the contact report callback will get
		/// called while the actors of this collision pair are in contact.
		/// Note: Only takes effect if the colliding actors are rigid bodies.
		/// </summary>
		NotifyTouchPersists = PxPairFlag::eNOTIFY_TOUCH_PERSISTS,

		/// <summary>
		/// Call contact report callback or trigger callback when this collision pair stops to be in contact.
		/// If one of the two collision objects is a trigger shape (see PxShapeFlag::eTRIGGER_SHAPE) then the
		/// trigger callback will get called as soon as the other object leaves the trigger volume.
		/// If none of the two collision objects is a trigger shape then the contact report callback will get
		/// called when the actors of this collision pair stop to be in contact.
		/// Note: Only takes effect if the colliding actors are rigid bodies.
		/// </summary>
		NotifyTouchLost = PxPairFlag::eNOTIFY_TOUCH_LOST,

		/// <summary>
		/// Call contact report callback when the contact force between the actors of this collision pair
		/// exceeds one of the actor-defined force thresholds.
		/// Note: Only takes effect if the colliding actors are rigid bodies.
		/// </summary>
		NotifyThresholdForceFound = PxPairFlag::eNOTIFY_THRESHOLD_FORCE_FOUND,

		/// <summary>
		/// Call contact report callback when the contact force between the actors of this collision pair
		/// continues to exceed one of the actor-defined force thresholds.
		/// Note: Only takes effect if the colliding actors are rigid bodies.
		/// </summary>
		NotifyThresholdForcePersists = PxPairFlag::eNOTIFY_THRESHOLD_FORCE_PERSISTS,

		/// <summary>
		/// Call contact report callback when the contact force between the actors of this collision pair
		/// falls below one of the actor-defined force thresholds (includes the case where this collision
		/// pair stops being in contact).
		/// Note: Only takes effect if the colliding actors are rigid bodies.
		/// </summary>
		NotifyThresholdForceLost = PxPairFlag::eNOTIFY_THRESHOLD_FORCE_LOST,

		/// <summary>
		/// Provide contact points in contact reports for this collision pair.
		/// </summary>
		NotifyContactPoints = PxPairFlag::eNOTIFY_CONTACT_POINTS,

		/// <summary>
		/// Provided default flag to do simple contact processing for this collision pair.
		/// </summary>
		ContactDefault = PxPairFlag::eCONTACT_DEFAULT,

		/// <summary>
		/// Provided default flag to get commonly used trigger behavior for this collision pair.
		/// </summary>
		TriggerDefault = PxPairFlag::eTRIGGER_DEFAULT
	};

	/// <summary>
	/// Enum for selecting the friction algorithm used for simulation.
	/// </summary>
	public enum FrictionType
	{
		/// <summary>
		/// Select default patch-friction model.
		/// </summary>
		Patch = PxFrictionType::ePATCH,

		/// <summary>
		/// Select one directional per-contact friction model. 
		/// </summary>
		OneDirectional = PxFrictionType::eONE_DIRECTIONAL,

		/// <summary>
		/// Select two directional per-contact friction model.
		/// </summary>
		TwoDirectional = PxFrictionType::eTWO_DIRECTIONAL,

		/// <summary>
		/// Select patch friction model with behavior unchanged from PhysX version 3.2 and prior.
		/// </summary>
		LegacyPatch = PxFrictionType::eLEGACY_PATCH
	};

	public enum BatchQueryStatus
	{
		/// <summary>
		/// This is the initial state before a query starts.
		/// </summary>
		Pending = PxBatchQueryStatus::ePENDING,

		/// <summary>
		/// The query is finished; results have been written into the result and hit buffers.
		/// </summary>
		Success = PxBatchQueryStatus::eSUCCESS,

		/// <summary>
		/// The query results were incomplete due to touch hit buffer overflow. Blocking hit is still correct.
		/// </summary>
		Overflow = PxBatchQueryStatus::eOVERFLOW
	};

	public enum class FilterFlag
	{
		Kill = PxFilterFlag::eKILL,
		Supress = PxFilterFlag::eSUPPRESS,
		Callback = PxFilterFlag::eCALLBACK,
		Notify = PxFilterFlag::eNOTIFY,
		Default = PxFilterFlag::eDEFAULT
	};
};