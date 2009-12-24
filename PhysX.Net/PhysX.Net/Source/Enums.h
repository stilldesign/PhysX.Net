#pragma once

#include "Physics Parameters.h"
#include "Fluid Enums.h"
#include "Joint Enums.h"
#include "Controller Enums.h"

namespace StillDesign
{
	namespace PhysX
	{
		public enum class SimulationStatus
		{
			RigidBodyFinished = NX_RIGID_BODY_FINISHED,
			AllFinished = NX_ALL_FINISHED,
			PrimaryFinished = NX_PRIMARY_FINISHED
		};
		
		public enum class ForceMode
		{
			/// <summary>parameter has unit of mass * distance/ time^2, i.e. a force</summary>
			Force = NX_FORCE,
			Impulse = NX_IMPULSE,
			VelocityChange = NX_VELOCITY_CHANGE,
			SmoothImpulse = NX_SMOOTH_IMPULSE,
			SmoothVelocityChange = NX_SMOOTH_VELOCITY_CHANGE,
			Acceleration = NX_ACCELERATION
		};
		
		[Flags]
		public enum class MeshFlag
		{
			FlipNormals = NX_MF_FLIPNORMALS,
			Indices16Bit = NX_MF_16_BIT_INDICES,
			HardwareMesh = NX_MF_HARDWARE_MESH
		};
		
		public enum class Axis
		{
			X = NX_X,
			Y = NX_Y,
			Z = NX_Z
		};
		
		[Flags]
		public enum class ContactPairFlag
		{
			IgnorePair = NX_IGNORE_PAIR,
			
			OnStartTouch = NX_NOTIFY_ON_START_TOUCH,
			OnEndTouch = NX_NOTIFY_ON_END_TOUCH,
			OnTouch = NX_NOTIFY_ON_TOUCH,
			OnImpact = NX_NOTIFY_ON_IMPACT,
			OnRoll = NX_NOTIFY_ON_ROLL,
			OnSlide = NX_NOTIFY_ON_SLIDE,
			Forces = NX_NOTIFY_FORCES,
			OnStartTouchForceThreshold = NX_NOTIFY_ON_START_TOUCH_FORCE_THRESHOLD,
			OnEndTouchForceThreshold = NX_NOTIFY_ON_END_TOUCH_FORCE_THRESHOLD,
			OnTouchForceThreshold = NX_NOTIFY_ON_TOUCH_FORCE_THRESHOLD,
			ContactModification = NX_NOTIFY_CONTACT_MODIFICATION,
			
			All = NX_NOTIFY_ALL
		};
		
		public enum class Platform
		{
			PC = PLATFORM_PC,
			Xenon = PLATFORM_XENON,
			PlayStation3 = PLATFORM_PLAYSTATION3
		};
		
		public enum class InternalArray
		{
			Triangles = NX_ARRAY_TRIANGLES,
			Vertices = NX_ARRAY_VERTICES,
			Normals = NX_ARRAY_NORMALS,
			HullVertices = NX_ARRAY_HULL_VERTICES,
			HullPolygons = NX_ARRAY_HULL_POLYGONS,
			TrianglesRemap = NX_ARRAY_TRIANGLES_REMAP
		};
		
		public enum class InternalFormat
		{
			NoData = NX_FORMAT_NODATA,
			Float = NX_FORMAT_FLOAT,
			Byte = NX_FORMAT_BYTE,
			Short = NX_FORMAT_SHORT,
			Integer = NX_FORMAT_INT
		};
		
		[Flags]
		public enum class MeshShapeFlag
		{
			SmoothSphereCollisions = NX_MESH_SMOOTH_SPHERE_COLLISIONS,
			DoubleSided = NX_MESH_DOUBLE_SIDED
		};
		
		public enum class MeshPagingMode
		{
			Manual = NX_MESH_PAGING_MANUAL,
			FallBack = NX_MESH_PAGING_FALLBACK,
			Auto = NX_MESH_PAGING_AUTO
		};
		
		public enum class ErrorCode
		{
			NoError = NXE_NO_ERROR,
			InvalidParameter = NXE_INVALID_PARAMETER,
			InvalidOperation = NXE_INVALID_OPERATION,
			OutOfMemory = NXE_OUT_OF_MEMORY,
			InternalError = NXE_INTERNAL_ERROR,
			Assertion = NXE_ASSERTION,
			DebugInfo = NXE_DB_INFO,
			DebugWarning = NXE_DB_WARNING,
			DebugPrint = NXE_DB_PRINT
		};
		
		public enum class AssertResponse
		{
			Continue = NX_AR_CONTINUE,
			Ignore = NX_AR_IGNORE,
			Breakpoint = NX_AR_BREAKPOINT
		};
		
		[Flags]
		public enum class ConvexFlag
		{
			FlipNormals = NX_CF_FLIPNORMALS,
			Indices16Bit = NX_CF_16_BIT_INDICES,
			ComputeConvex = NX_CF_COMPUTE_CONVEX,
			InflateConvex = NX_CF_INFLATE_CONVEX,
			//UseLegacyCooker = NX_CF_USE_LEGACY_COOKER,
			UseUncompressedNormals = NX_CF_USE_UNCOMPRESSED_NORMALS
		};
		
		public enum class QueryFlag
		{
			WorldSpace = NX_QUERY_WORLD_SPACE,
			FirstContact = NX_QUERY_FIRST_CONTACT
		};
		
		[Flags]
		public enum class ActorFlag
		{
			DisableCollision = NX_AF_DISABLE_COLLISION,
			DisableResponse = NX_AF_DISABLE_RESPONSE,
			LockCenterOfMass = NX_AF_LOCK_COM,
			DisableFluidCollision = NX_AF_FLUID_DISABLE_COLLISION,
			ContactModification = NX_AF_CONTACT_MODIFICATION,
			ForceConeFriction = NX_AF_FORCE_CONE_FRICTION,
			UserActorPairFiltering = NX_AF_USER_ACTOR_PAIR_FILTERING
		};
		public enum class ActorDescriptionType
		{
			Shapeless = NX_ADT_SHAPELESS,
			Default = NX_ADT_DEFAULT,
			Allocator = NX_ADT_ALLOCATOR,
			ListType = NX_ADT_LIST,
			Pointer = NX_ADT_POINTER
		};
		
		[Flags]
		public enum class BodyFlag
		{
			DisableGravity = NX_BF_DISABLE_GRAVITY,
			
			FrozenPositionX = NX_BF_FROZEN_POS_X,
			FrozenPositionY = NX_BF_FROZEN_POS_Y,
			FrozenPositionZ = NX_BF_FROZEN_POS_Z,
			
			FrozenRotationX = NX_BF_FROZEN_ROT_X,
			FrozenRotationY = NX_BF_FROZEN_ROT_Y,
			FrozenRotationZ = NX_BF_FROZEN_ROT_Z,
			
			FrozenPosition = NX_BF_FROZEN_POS,
			FrozenRotation = NX_BF_FROZEN_ROT,
			
			Frozen = NX_BF_FROZEN,
			Kinematic = NX_BF_KINEMATIC,
			
			Visualization = NX_BF_VISUALIZATION,
			
			//PoseSleepTest = NX_BF_POSE_SLEEP_TEST,
			FilterSleepVelocity = NX_BF_FILTER_SLEEP_VEL,
			EnergySleepTest = NX_BF_ENERGY_SLEEP_TEST
		};
		
		[Flags]
		public enum class ClothAttachmentFlag
		{
			Tearable = NX_CLOTH_ATTACHMENT_TEARABLE,
			Twoway = NX_CLOTH_ATTACHMENT_TWOWAY
		};
		
		public enum class SimulationType
		{
			Software = NX_SIMULATION_SW,
			Hardware = NX_SIMULATION_HW
		};
		
		public enum class CoreCreationFlag
		{
			NoHardware = NX_SDKF_NO_HARDWARE
		};
		
		public enum class CoreCreationError
		{
			NoError = NXCE_NO_ERROR,
			PhysXNotFound = NXCE_PHYSX_NOT_FOUND,
			WrongVersion = NXCE_WRONG_VERSION,
			DescriptorInvalid = NXCE_DESCRIPTOR_INVALID,
			ConnectionError = NXCE_CONNECTION_ERROR,
			ResetError = NXCE_RESET_ERROR,
			InUseError = NXCE_IN_USE_ERROR,
			BundleError = NXCE_BUNDLE_ERROR
		};
		
		public enum class ForceFieldCoordinate
		{
			Cartesian = NX_FFC_CARTESIAN,
			Spherical = NX_FFC_SPHERICAL, 
			Cylindrical = NX_FFC_CYLINDRICAL,
			Toroidal = NX_FFC_TOROIDAL
		};
		
		public enum class HardwareVersion
		{
			None = NX_HW_VERSION_NONE,
			Athena_1_0 = NX_HW_VERSION_ATHENA_1_0
		};
		
		[Flags]
		public enum class SoftBodyMeshFlag
		{
			SixteenBitIndices = NX_SOFTBODY_MESH_16_BIT_INDICES,
			Tearable = NX_SOFTBODY_MESH_TEARABLE
		};
		
		[Flags]
		public enum class SoftBodyVertexFlag
		{
			Tearable = NX_SOFTBODY_VERTEX_TEARABLE,
			Secondary = NX_SOFTBODY_VERTEX_SECONDARY
		};
		
		[Flags]
		public enum class SoftBodyFlag
		{
			Static = NX_SBF_STATIC,
			DisableCollision = NX_SBF_DISABLE_COLLISION,
			SelfCollision = NX_SBF_SELFCOLLISION,
			Visualization = NX_SBF_VISUALIZATION,
			Gravity = NX_SBF_GRAVITY,
			VolumeConservation = NX_SBF_VOLUME_CONSERVATION,
			Damping = NX_SBF_DAMPING,
			CollisionTwoway = NX_SBF_COLLISION_TWOWAY,
			Tearable = NX_SBF_TEARABLE,
			CenterOfMassDamping = NX_SBF_COMDAMPING,
			ValidBounds = NX_SBF_VALIDBOUNDS,
			FluidCollision = NX_SBF_FLUID_COLLISION,
			DisableDynamicCCD = NX_SBF_DISABLE_DYNAMIC_CCD,
			Adhere = NX_SBF_ADHERE,
			HardStretchLimitation = NX_SBF_HARD_STRETCH_LIMITATION,
			InterCollision = NX_SBF_INTER_COLLISION
		};
		
		[Flags]
		public enum class ClothFlag
		{
			Pressure = NX_CLF_PRESSURE,
			Static = NX_CLF_STATIC,
			DisableCollision =  NX_CLF_DISABLE_COLLISION,
			SelfCollision = NX_CLF_SELFCOLLISION,
			Visualization = NX_CLF_VISUALIZATION,
			Gravity = NX_CLF_GRAVITY,
			Bending = NX_CLF_BENDING,
			BendingOrthogonal = NX_CLF_BENDING_ORTHO,
			Damping = NX_CLF_DAMPING,
			CollisionTwoway = NX_CLF_COLLISION_TWOWAY,
			TriangleCollision = NX_CLF_TRIANGLE_COLLISION,
			Tearable = NX_CLF_TEARABLE,
			Hardware = NX_CLF_HARDWARE,
			CenterOfMassDamping = NX_CLF_COMDAMPING,
			ValidBounds = NX_CLF_VALIDBOUNDS,
			FluidCollision = NX_CLF_FLUID_COLLISION,
			DisableDynamicCCD = NX_CLF_DISABLE_DYNAMIC_CCD,
			Adhere = NX_CLF_ADHERE,
			HardStretchLimitation = NX_CLF_HARD_STRETCH_LIMITATION,
			Untangling = NX_CLF_UNTANGLING,
			InterCollision = NX_CLF_INTER_COLLISION
		};
		
		public enum class HeightFieldFormat
		{
			S16_TM = NX_HF_S16_TM
		};
		
		public enum class HeightFieldFlag
		{
			NoBoundaryEdges = NX_HF_NO_BOUNDARY_EDGES
		};
		
		[Flags]
		public enum class TriangleFlag
		{
			ActiveEdge01 = NXTF_ACTIVE_EDGE01,
			ActiveEdge12 = NXTF_ACTIVE_EDGE12,
			ActiveEdge20 = NXTF_ACTIVE_EDGE20,
			DoubleSided = NXTF_DOUBLE_SIDED,
			BoundaryEdge01 = NXTF_BOUNDARY_EDGE01,
			BoundaryEdge12 = NXTF_BOUNDARY_EDGE12,
			BoundaryEdge20 = NXTF_BOUNDARY_EDGE20
		};
		
		public enum class CompartmentType
		{
			RigidBody = NX_SCT_RIGIDBODY,
			Fluid = NX_SCT_FLUID, 
			Cloth = NX_SCT_CLOTH, 
			Softbody = NX_SCT_SOFTBODY 
		};
		
		public enum class DeviceCode
		{ 
			PPU0 = NX_DC_PPU_0,
			PPU1 = NX_DC_PPU_1,
			PPU2 = NX_DC_PPU_2,
			PPU3 = NX_DC_PPU_3,
			PPU4 = NX_DC_PPU_4,
			PPU5 = NX_DC_PPU_5,
			PPU6 = NX_DC_PPU_6,
			PPU7 = NX_DC_PPU_7,
			PPU8 = NX_DC_PPU_8,
			CPU = NX_DC_CPU,
			PPU_AutoAssign = NX_DC_PPU_AUTO_ASSIGN
		};
		
		public enum class ShapePairStreamFlag
		{ 
			HasMatsPerPoint = NX_SF_HAS_MATS_PER_POINT,
			HasFeaturesPerPoint = NX_SF_HAS_FEATURES_PER_POINT
		};
		
		public enum class EffectorType
		{
			SpringAndDamper = NX_EFFECTOR_SPRING_AND_DAMPER
		};
		
		public enum class FluidEventType
		{
			NoParticlesLeft = NX_FET_NO_PARTICLES_LEFT
		};
		
		public enum class FluidEmitterEventType
		{
			EmitterEmpty = NX_FEET_EMITTER_EMPTY
		};
		
		public enum class ForceFieldType
		{
			Gravitational = NX_FF_TYPE_GRAVITATIONAL,
			Other = NX_FF_TYPE_OTHER,
			NoInteraction = NX_FF_TYPE_NO_INTERACTION
		};
		
		[Flags]
		public enum class ForceFieldFlag
		{
			ScalingFluid = NX_FFF_VOLUMETRIC_SCALING_FLUID,
			ScalingCloth = NX_FFF_VOLUMETRIC_SCALING_CLOTH,
			ScalingSoftBody = NX_FFF_VOLUMETRIC_SCALING_SOFTBODY,
			ScalingRigidBody = NX_FFF_VOLUMETRIC_SCALING_RIGIDBODY
		};
		
		public enum HeightFieldAxis
		{
			X = NX_X, 
			Y = NX_Y, 
			Z = NX_Z, 
			NotAHeightField = NX_NOT_HEIGHTFIELD
		};
		
		[Flags]
		public enum class D6JointDriveType
		{
			DrivePosition = NX_D6JOINT_DRIVE_POSITION,
			DriveVelocity = NX_D6JOINT_DRIVE_VELOCITY
		};
		
		[Flags]
		public enum class CompartmentFlag
		{
			SleepNotification = NX_CF_SLEEP_NOTIFICATION,
			ContinuousCD = NX_CF_CONTINUOUS_CD,
			RestrictedScene = NX_CF_RESTRICTED_SCENE,
			InheritSettings = NX_CF_INHERIT_SETTINGS
		};
				
		public enum FilterOperation
		{ 
			AND = NX_FILTEROP_AND, 
			OR = NX_FILTEROP_OR, 
			XOR = NX_FILTEROP_XOR, 
			NAND = NX_FILTEROP_NAND, 
			NOR = NX_FILTEROP_NOR, 
			NXOR = NX_FILTEROP_NXOR, 
			SwapAND = NX_FILTEROP_SWAP_AND
		};
		
		public enum class SepAxis
		{
			Overlap = NX_SEP_AXIS_OVERLAP,
			A0 = NX_SEP_AXIS_A0,
			A1 = NX_SEP_AXIS_A1,
			A2 = NX_SEP_AXIS_A2,
			B0 = NX_SEP_AXIS_B0,
			B1 = NX_SEP_AXIS_B1,
			B2 = NX_SEP_AXIS_B2,
			A0CrossB0 = NX_SEP_AXIS_A0_CROSS_B0,
			A0CrossB1 = NX_SEP_AXIS_A0_CROSS_B1,
			A0CrossB2 = NX_SEP_AXIS_A0_CROSS_B2,
			A1CrossB0 = NX_SEP_AXIS_A1_CROSS_B0,
			A1CrossB1 = NX_SEP_AXIS_A1_CROSS_B1,
			A1CrossB2 = NX_SEP_AXIS_A1_CROSS_B2,
			A2CrossB0 = NX_SEP_AXIS_A2_CROSS_B0,
			A2CrossB1 = NX_SEP_AXIS_A2_CROSS_B1,
			A2CrossB2 = NX_SEP_AXIS_A2_CROSS_B2
		};
		
		public enum class HeightFieldTessFlag
		{
			Tess0thVertexShaded
		};
		
		public enum class CookingValue
		{
			ConvexVersionPC = NX_COOKING_CONVEX_VERSION_PC, 
			MeshVersionPC = NX_COOKING_MESH_VERSION_PC, 
			ConvexVersionXenon = NX_COOKING_CONVEX_VERSION_XENON, 
			MeshVersionXenon = NX_COOKING_MESH_VERSION_XENON, 
			ConvexVersionPlaystation3 = NX_COOKING_CONVEX_VERSION_PLAYSTATION3, 
			MeshVersionPlaystation3 = NX_COOKING_MESH_VERSION_PLAYSTATION3
		};
		
		public enum StandardFences
		{
			RunFinished = NX_FENCE_RUN_FINISHED,
			NumberStandardFences = NX_NUM_STANDARD_FENCES
		};
		
		public enum class ThreadPollResult
		{
			NoWork = NX_THREAD_NOWORK,
			MoreWork = NX_THREAD_MOREWORK,
			SimulationEnd = NX_THREAD_SIMULATION_END,
			Shutdown = NX_THREAD_SHUTDOWN
		};
		
		public enum class ThreadWait
		{
			None = NX_WAIT_NONE,
			SimulationEnd = NX_WAIT_SIMULATION_END,
			Shutdown = NX_WAIT_SHUTDOWN
		};
		
		[Flags]
		public enum class SweepFlags
		{
			Statics = NX_SF_STATICS,
			Dynamics = NX_SF_DYNAMICS,
			Asynchronous = NX_SF_ASYNC,
			AllHits = NX_SF_ALL_HITS,
			//DebugSM = NX_SF_DEBUG_SM,
			//DebugET = NX_SF_DEBUG_ET
		};
		
		[Flags]
		public enum class ProfileZoneName
		{ 
			ClientFrame = NX_PZ_CLIENT_FRAME,
			CPUSimulate = NX_PZ_CPU_SIMULATE,
			PPU0Simulate = NX_PZ_PPU0_SIMULATE,
			PPU1Simulate = NX_PZ_PPU1_SIMULATE,
			PPU2Simulate = NX_PZ_PPU2_SIMULATE,
			PPU3Simulate = NX_PZ_PPU3_SIMULATE,
			TotalSimulatation = NX_PZ_TOTAL_SIMULATION
		};
		
		public enum class PruningStructure
		{
			None = NX_PRUNING_NONE, 
			Octree = NX_PRUNING_OCTREE, 
			Quadtree = NX_PRUNING_QUADTREE, 
			DynamicAABBTree = NX_PRUNING_DYNAMIC_AABB_TREE, 
			StaticAABBTree = NX_PRUNING_STATIC_AABB_TREE
		};
		
		[Flags]
		public enum class SceneFlag
		{
			DisableSSE = NX_SF_DISABLE_SSE,
			DisableCollisions = NX_SF_DISABLE_COLLISIONS,
			SimulateSeparateThread = NX_SF_SIMULATE_SEPARATE_THREAD,
			EnableMultithread = NX_SF_ENABLE_MULTITHREAD,
			EnableActiveTransforms = NX_SF_ENABLE_ACTIVETRANSFORMS,
			RestrictedScene = NX_SF_RESTRICTED_SCENE,
			DisableSceneMutex = NX_SF_DISABLE_SCENE_MUTEX,
			ForceConeFrictions = NX_SF_FORCE_CONE_FRICTION,
			SequentialPrimart = NX_SF_SEQUENTIAL_PRIMARY,
			FluidPerformanceHint = NX_SF_FLUID_PERFORMANCE_HINT,
			AlternativeFluidTriangleCollision = NX_SF_ALTERNATIVE_FLUID_TRIANGLE_COLLISION,
			MultithreadedForcefield = NX_SF_MULTITHREADED_FORCEFIELD
		};
		
		public enum class SceneQueryExecuteMode
		{ 
			Synchronous = NX_SQE_SYNCHRONOUS, 
			Asynchronous = NX_SQE_ASYNCHRONOUS
		};
		
		public enum class QueryReportResult
		{
			NX_SQR_CONTINUE, 
			NX_SQR_ABORT_QUERY, 
			NX_SQR_ABORT_ALL_QUERIES
		};
		
		public enum class ShapesType
		{
			Static =  NX_STATIC_SHAPES,
			Dynamic = NX_DYNAMIC_SHAPES,
			All = NX_ALL_SHAPES
		};
		
		public enum class ShapeType
		{
			Plane = NX_SHAPE_PLANE,
			Sphere = NX_SHAPE_SPHERE,
			Box = NX_SHAPE_BOX,
			Capsule = NX_SHAPE_CAPSULE,
			Wheel = NX_SHAPE_WHEEL,
			Convex = NX_SHAPE_CONVEX,
			Mesh = NX_SHAPE_MESH,
			Heightfield = NX_SHAPE_HEIGHTFIELD
		};
		
		[Flags]
		public enum class ShapeFlag
		{
			TriggerOnEnter = NX_TRIGGER_ON_ENTER,
			TriggerOnLeave = NX_TRIGGER_ON_LEAVE,
			TriggerOnStay = NX_TRIGGER_ON_STAY,
			TriggerEnable = NX_TRIGGER_ENABLE,
			Visualization = NX_SF_VISUALIZATION,
			DisableCollision = NX_SF_DISABLE_COLLISION,
			FeatureIndices = NX_SF_FEATURE_INDICES,
			DisableRaycasting = NX_SF_DISABLE_RAYCASTING,
			PointContactForce = NX_SF_POINT_CONTACT_FORCE,
			FluidDrain = NX_SF_FLUID_DRAIN,
			FluidDisableCollision = NX_SF_FLUID_DISABLE_COLLISION,
			FluidTwoway = NX_SF_FLUID_TWOWAY,
			DisableResponse = NX_SF_DISABLE_RESPONSE,
			DynamicDynamicCCD = NX_SF_DYNAMIC_DYNAMIC_CCD,
			DisableSceneQueries = NX_SF_DISABLE_SCENE_QUERIES,
			ClothDrain = NX_SF_CLOTH_DRAIN,
			ClothDisableCollision = NX_SF_CLOTH_DISABLE_COLLISION,
			ClothTwoway = NX_SF_CLOTH_TWOWAY,
			SoftBodyDrain = NX_SF_SOFTBODY_DRAIN,
			SoftBodyDisableCollision = NX_SF_SOFTBODY_DISABLE_COLLISION,
			SoftBodyTwoway = NX_SF_SOFTBODY_TWOWAY
		};
		
		public enum class SphereGenerationMethod
		{
			None,
			Gems,
			Miniball
		};
		
		public enum class CapsuleShapeFlag
		{
			SweptShape = NX_SWEPT_SHAPE
		};
		
		[Flags]
		public enum class RaycastBit
		{
			Shape = NX_RAYCAST_SHAPE,
			Impact = NX_RAYCAST_IMPACT,
			Normal = NX_RAYCAST_NORMAL,
			FaceIndex = NX_RAYCAST_FACE_INDEX,
			Distance = NX_RAYCAST_DISTANCE,
			UV = NX_RAYCAST_UV,
			FaceNormal = NX_RAYCAST_FACE_NORMAL,
			Material = NX_RAYCAST_MATERIAL
		};
		
		public enum class MeshDataFlag
		{
			SixteenBitIndices = NX_MDF_16_BIT_INDICES
		};
		public enum class MeshDataDirtyBufferFlags
		{
			DirtyPositionVertices = NX_MDF_VERTICES_POS_DIRTY,
			DirtyNormalVertices = NX_MDF_VERTICES_NORMAL_DIRTY,
			DirtyIndices = NX_MDF_INDICES_DIRTY,
			DiretyParentIndices = NX_MDF_PARENT_INDICES_DIRTY
		};
		
		public enum class TimestepMethod
		{
			Fixed = NX_TIMESTEP_FIXED,
			Variable = NX_TIMESTEP_VARIABLE
		};
		
		public enum class SoftBodyAttachmentFlag
		{
			Twoway = NX_SOFTBODY_ATTACHMENT_TWOWAY,
			Tearable = NX_SOFTBODY_ATTACHMENT_TEARABLE 
		};
		
		public enum class CapsuleClimbingMode
		{
			Easy = CLIMB_EASY,
			Constrained = CLIMB_CONSTRAINED
		};
		
		public enum class ClothVertexAttachmentStatus
		{
			None = NX_CLOTH_VERTEX_ATTACHMENT_NONE,
			Global = NX_CLOTH_VERTEX_ATTACHMENT_GLOBAL,
			Shape = NX_CLOTH_VERTEX_ATTACHMENT_SHAPE
		};
		
		public enum class CookingResourceType
		{
			Performance,
			LessMemory
		};
		
		[Flags]
		public enum class WheelShapeFlag
		{
			WheelAxisContactNormal = NX_WF_WHEEL_AXIS_CONTACT_NORMAL,
			InputLaterialSlipVelocity = NX_WF_INPUT_LAT_SLIPVELOCITY,
			InputLongutudalSlipVelocity = NX_WF_INPUT_LNG_SLIPVELOCITY,
			UnscaledSpringBehaviour = NX_WF_UNSCALED_SPRING_BEHAVIOR,
			AxleSpeedOverride = NX_WF_AXLE_SPEED_OVERRIDE,
			EmulateLegacyWheel = NX_WF_EMULATE_LEGACY_WHEEL,
			ClampedFriction = NX_WF_CLAMPED_FRICTION
		};
		
		public enum class ThreadPriority
		{
			High = NX_TP_HIGH,
			AboveNormal = NX_TP_ABOVE_NORMAL,
			Normal = NX_TP_NORMAL,
			BelowNormal = NX_TP_BELOW_NORMAL,
			Low = NX_TP_LOW
		};
		
		[Flags]
		public enum class TriggerFlag
		{
			OnEnter = NX_TRIGGER_ON_ENTER,
			OnLeave = NX_TRIGGER_ON_LEAVE,
			OnStay = NX_TRIGGER_ON_STAY
		};
		
		public enum class ClothVertexFlag
		{
			Attached = NX_CLOTH_VERTEX_ATTACHED,
			Tearable = NX_CLOTH_VERTEX_TEARABLE
		};
		
		public enum class ForceFieldShapeGroupFlag
		{
			ExcludeGroup = NX_FFSG_EXCLUDE_GROUP
		};
		
		public enum class ClothMeshFlag
		{
			Tearable = NX_CLOTH_MESH_TEARABLE,
			WeldVertices = NX_CLOTH_MESH_WELD_VERTICES
		};
		
		public enum class BroadPhaseType
		{
			SAPSingle = NX_BP_TYPE_SAP_SINGLE,
			SAPMulti = NX_BP_TYPE_SAP_MULTI
		};
		
		public enum class ShapeCompartmentType
		{
			SoftwareRigidBody = NX_COMPARTMENT_SW_RIGIDBODY,
			HardwareRigidBody = NX_COMPARTMENT_HW_RIGIDBODY,
			SoftwareFluid = NX_COMPARTMENT_SW_FLUID,
			HardwareFluid = NX_COMPARTMENT_HW_FLUID,
			SoftwareCloth = NX_COMPARTMENT_SW_CLOTH,
			HardwareCloth = NX_COMPARTMENT_HW_CLOTH,
			SoftwareSoftBody = NX_COMPARTMENT_SW_SOFTBODY,
			HardwareSoftBody = NX_COMPARTMENT_HW_SOFTBODY	
		};
		
		namespace Utilities
		{
			public enum class UtilitiesFileType
			{
				Binary = NXU::FT_BINARY,
				Xml = NXU::FT_XML,
				Collada = NXU::FT_COLLADA
			};
		};
	};
};