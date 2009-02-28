#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public enum class FluidSimulationMethod
		{
			SmoothedParticleHydrodynamics = NX_F_SPH,
			NoParticleInteraction = NX_F_NO_PARTICLE_INTERACTION,
			MixedMode = NX_F_MIXED_MODE
		};
		
		public enum class FluidCollisionMethod
		{
			Static = NX_F_STATIC,
			Dynamic = NX_F_DYNAMIC
		};
		
		public enum class FluidFlag
		{
			Visualization = NX_FF_VISUALIZATION,
			DisableGravity = NX_FF_DISABLE_GRAVITY,
			CollisionTwoway = NX_FF_COLLISION_TWOWAY,
			Enabled = NX_FF_ENABLED,
			Hardware = NX_FF_HARDWARE,
			PriorityMode = NX_FF_PRIORITY_MODE,
			ForceStrictCookingFormat = NX_FF_FORCE_STRICT_COOKING_FORMAT,
			ProjectToPlane = NX_FF_PROJECT_TO_PLANE
		};
		
		[Flags]
		public enum class EmitterType
		{
			ConstantPressure = NX_FE_CONSTANT_PRESSURE,
			ConstantFlowRate = NX_FE_CONSTANT_FLOW_RATE
		};
		
		public enum class EmitterShape
		{
			Rectangular = NX_FE_RECTANGULAR,
			Ellipse = NX_FE_ELLIPSE
		};
		
		public enum class FluidEmitterFlag
		{
			Visualization = NX_FEF_VISUALIZATION,
			ForceOnBody = NX_FEF_FORCE_ON_BODY,
			AddBodyVelocity = NX_FEF_ADD_BODY_VELOCITY,
			Enabled = NX_FEF_ENABLED
		};
		
		public enum class FluidDescriptionType
		{
			Default = NX_FDT_DEFAULT,
			Allocator = NX_FDT_ALLOCATOR
		};
		
		public enum class ParticleDataFlag
		{
			Delete = NX_FP_DELETE
		};
		
		public enum class ParticleFlag
		{
			CollisionWithStatic = NX_FP_COLLISION_WITH_STATIC,
			CollisionWithDynamic = NX_FP_COLLISION_WITH_DYNAMIC,
			Sparated = NX_FP_SEPARATED,
			MotionLimitReached = NX_FP_MOTION_LIMIT_REACHED
		};
	};
};