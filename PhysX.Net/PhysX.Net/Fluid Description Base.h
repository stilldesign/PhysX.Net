#pragma once

#include "Enums.h"
#include "IDisposable.h"

using namespace System;
UsingFrameworkNamespace

class NxFluidDescBase;

namespace StillDesign
{
	namespace PhysX
	{
		ref class ParticleData;
		value class GroupsMask;
		ref class DescriptorValidity;
		ref class Compartment;
		ref class ParticleIdData;
		ref class FluidPacketData;
		
		public ref class FluidDescriptionBase abstract : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
			
			protected:
				NxFluidDescBase* _fluidDescBase;
				
			private:
				ParticleData^ _initialParticleData;
				ParticleData^ _particleWriteData;
				ParticleIdData^ _particleDeletionWriteData;
				ParticleIdData^ _particleCreationWriteData;
				StillDesign::PhysX::FluidPacketData^ _fluidPacketData;
				
				StillDesign::PhysX::Compartment^ _compartment;
				
				Object^ _userData;
			
			protected:
				FluidDescriptionBase( NxFluidDescBase* fluidDescription );
			public:
				~FluidDescriptionBase();
			protected:
				!FluidDescriptionBase();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
				/// <summary>Sets the structure to the default</summary>
				void SetToDefault();
				/// <summary>Returns true if the descriptor is valid</summary>
				DescriptorValidity^ IsValid();
				
				/// <summary>Gets or Sets the particles which are added to the fluid initially</summary>
				property ParticleData^ InitialParticleData
				{
					ParticleData^ get();
				}
				/// <summary>Gets or Sets the user data buffers which are used to store particle data, which can be used for rendering</summary>
				property ParticleData^ ParticleWriteData
				{
					ParticleData^ get();
				}
				/// <summary>Gets or Sets the user data buffer which is used to store IDs of deleted particles</summary>
				property ParticleIdData^ ParticleDeletionIdWriteData
				{
					ParticleIdData^ get();
				}
				/// <summary>Gets or Sets the user data buffer which is used to store IDs of created particles</summary>
				property ParticleIdData^ ParticleCreationIdWriteData
				{
					ParticleIdData^ get();
				}
				/// <summary>Gets or Sets the user data buffer which is used to store fluid packets</summary>
				property StillDesign::PhysX::FluidPacketData^ FluidPacketData
				{
					StillDesign::PhysX::FluidPacketData^ get();
				}
				
				/// <summary>The compartment to place the fluid in. Must be of type Fluid. A null compartment means creating the fluid in the first available fluid compartment (a default fluid compartment is created if none exists).</summary>
				property StillDesign::PhysX::Compartment^ Compartment
				{
					StillDesign::PhysX::Compartment^ get();
					void set( StillDesign::PhysX::Compartment^ value );
				}
				
				/// <summary>Gets or Sets the name of the fluid description</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				property FluidDescriptionType Type
				{
					FluidDescriptionType get();
				}
				
				/// <summary>Gets or Sets the maximal number of particles for the fluid used in the simulation</summary>
				property int MaximumParticles
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the number of particles which are reserved for creation at runtime</summary>
				property int NumberOfReservedParticles
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets particle resolution given as particles per linear meter measured when the fluid is in its rest state (relaxed)</summary>
				property float RestParticlesPerMeter
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the target density for the fluid (water is about 1000)</summary>
				property float RestDensity
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the radius of sphere of influence for particle interaction</summary>
				property float KernelRadiusMultiplier
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the maximal distance a particle is allowed to travel within one timestep</summary>
				property float MotionLimitMultiplier
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the distance between particles and collision geometry, which is maintained during simulation</summary>
				property float CollisionDistanceMultiplier
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the parallelization of the fluid</summary>
				property int PacketSizeMultiplier
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the stiffness of the particle interaction related to the pressure</summary>
				property float Stiffness
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the viscosity of the fluid defines its viscous behavior</summary>
				property float Viscosity
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the fluid surface tension</summary>
				property float SurfaceTension
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the velocity damping constant, which is globally applied to each particle</summary>
				property float Damping
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets defines a timespan for the particle "fade-in"</summary>
				property float FadeInTime
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the acceleration (m/s^2) applied to all particles at all time steps</summary>
				property Vector3 ExternalAcceleration
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the plane the fluid particles are projected to</summary>
				property Plane ProjectionPlane
				{
					Plane get();
					void set( Plane value );
				}
				/// <summary>Gets or Sets the restitution coefficient used for collisions of the fluid particles with static shapes</summary>
				property float RestitutionForStaticShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the "friction" of the fluid regarding the surface of a static shape</summary>
				property float DynamicFrictionForStaticShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the static friction of the fluid regarding the surface of a static shape</summary>
				property float StaticFrictionForStaticShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the strength of attraction between the particles and static rigid bodies on collision</summary>
				property float AttractionForStaticShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the restitution coefficient used for collisions of the fluid particles with dynamic shapes</summary>
				property float RestitutionForDynamicShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the "friction" of the fluid regarding the surface of a dynamic shape</summary>
				property float DynamicFrictionForDynamicShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the static friction of the fluid regarding the surface of a dynamic shape</summary>
				property float StaticFrictionForDynamicShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the strength of attraction between the particles and the dynamic rigid bodies on collision</summary>
				property float AttractionForDynamicShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets a factor for the impulse transfer from fluid to colliding rigid bodies</summary>
				property float CollisionResponseCoefficient
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets whether or not particle interactions are considered in the simulation</summary>
				property FluidSimulationMethod SimulationMethod
				{
					FluidSimulationMethod get();
					void set( FluidSimulationMethod value );
				}
				/// <summary>Gets or Sets whether static collision and/or dynamic collision with the environment is performed</summary>
				property FluidCollisionMethod CollisionMethod
				{
					FluidCollisionMethod get();
					void set( FluidCollisionMethod value );
				}
				/// <summary>Gets or Sets which collision group this fluid is part of</summary>
				property short CollisionGroup
				{
					short get();
					void set( short value );
				}
				/// <summary>Gets or Sets the 128-bit mask used for collision filtering</summary>
				property StillDesign::PhysX::GroupsMask GroupsMask
				{
					StillDesign::PhysX::GroupsMask get();
					void set( StillDesign::PhysX::GroupsMask value );
				}
				property short ForceFieldMaterial
				{
					short get();
					void set( short value );
				}
				/// <summary>Gets or Sets the flags defining certain properties of the fluid</summary>
				property FluidFlag Flags
				{
					FluidFlag get();
					void set( FluidFlag value );
				}
				
				/// <summary>Gets or Sets an arbitary 1:1 object</summary>
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
				
			internal:
				property NxFluidDescBase* UnmanagedPointer
				{
					NxFluidDescBase* get();
				}
		};
	};
};