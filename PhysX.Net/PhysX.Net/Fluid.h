#pragma once

#include "Enums.h"

#include "Bounds.h"
//#include "Implicit Screen Mesh.h"
#include "Element Collection.h"
#include "Fluid Emitter.h"

using namespace System;
UsingFrameworkNamespace

class NxFluid;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class FluidDescription;
		value class GroupsMask;
		ref class ParticleData;
		ref class ParticleUpdateData;
		ref class ParticleIdData;
		ref class FluidPacketData;
		ref class Compartment;
		
		public ref class Fluid : StillDesign::PhysX::IDisposable
		{
			public:
				ref class FluidEmitterCollection : ReadOnlyElementCollection<FluidEmitter^>
				{
					
				};
				
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
			
			private:
				NxFluid* _fluid;
				
				Scene^ _scene;
				
				ParticleData^ _particleWriteData;
				ParticleIdData^ _particleDeletionIdWriteData;
				ParticleIdData^ _particleCreationIdWriteData;
				FluidPacketData^ _fluidPacketData;
				
				StillDesign::PhysX::Compartment^ _compartment;
				
				ElementCollection<FluidEmitter^, FluidEmitterCollection^ >^ _fluidEmitters;
				
				Object^ _userData;
				
			internal:
				Fluid( NxFluid* fluid );
				Fluid( NxFluid* fluid, ParticleData^ particleWriteData, ParticleIdData^ particleDeletionIdWriteData, ParticleIdData^ particleCreationIdWriteData, StillDesign::PhysX::FluidPacketData^ fluidPacketData );
			public:
				~Fluid();
			protected:
				!Fluid();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
				/// <summary>Saves the fluid and emitter descriptors</summary>
				FluidDescription^ SaveToDescription();
				/// <summary>Saves the fluid and emitter descriptors</summary>
				/// <param name="saveEmitters">Save the emitters to the description also</param>
				FluidDescription^ SaveToDescription( bool saveEmitters );
				/// <summary>Loads the fluid descriptor</summary>
				void LoadFromDescription( FluidDescription^ description );
				
				/// <summary>Creates an emitter for this fluid</summary>
				/// <param name="description">The fluid emitter desciptor</param>
				FluidEmitter^ CreateFluidEmitter( FluidEmitterDescription^ description );
				/// <summary>Creates a surface mesh for this fluid relative to a given viewing matrix</summary>
				//ImplicitScreenMesh^ CreateImplicitScreenMesh( ImplicitScreenMeshDescription^ description );
				
				bool GetFlag( FluidFlag flag );
				void SetFlag( FluidFlag flag, bool value );
				
				/// <summary>Returns the minimal (exact) world space axis aligned bounding box (AABB) including all simulated particles</summary>
				Bounds3 GetWorldBounds();
				
				// Particle Manipulation
				/// <summary>Adds particles to the simulation specified with the user buffer wrapper</summary>
				/// <param name="particleData">Structure describing the particles to add</param>
				/// <returns>number of successfully created particles</returns>
				void AddParticles( ParticleData^ particleData );
				/// <summary>Adds particles to the simulation specified with the user buffer wrapper</summary>
				/// <param name="particleData">Structure describing the particles to add</param>
				/// <param name="appendIds">Particle appending or overwriting</param>
				/// <returns>number of successfully created particles</returns>
				void AddParticles( ParticleData^ particleData, bool appendIds );
				/// <summary>Removes all particles from the simulation</summary>
				void RemoveAllParticles();
				/// <summary>Updates particles for one simulation frame</summary>
				void UpdateParticles( ParticleUpdateData^ updateData );
				
				//
				
				/// <summary>Gets the collection of emitters</summary>
				property FluidEmitterCollection^ Emitters
				{
					FluidEmitterCollection^ get();
				}
				///// <summary>Gets the collection of screen meshes</summary>
				//property StillDesign::PhysX::Fluid::ImplicitScreenMeshCollection^ ImplicitScreenMeshes
				//{
				//	StillDesign::PhysX::Fluid::ImplicitScreenMeshCollection^ get();
				//}
				
				/// <summary>Gets the scene the fluid is created in</summary>
				property StillDesign::PhysX::Scene^ Scene
				{
					StillDesign::PhysX::Scene^ get();
				}
				
				/// <summary>Gets the fluid's simulation compartment, as specified by the user at creation time</summary>
				property StillDesign::PhysX::Compartment^ Compartment
				{
					StillDesign::PhysX::Compartment^ get();
				}
				
				/// <summary>Gets the Name of the Fluid</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				/// <summary>Gets the maximum number of particles for this fluid</summary>
				property int MaximumParticles
				{
					int get();
				}
				/// <summary>Gets or Sets the number of particles which are reserved for creation at runtime</summary>
				property int NumberOfReservedParticles
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the bound on the maximum number of particles currently allowed in the fluid</summary>
				property int CurrentParticleLimit
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets the number of particles per meter in the relaxed state of the fluid</summary>
				property float RestParticlesPerMeter
				{
					float get();
				}
				/// <summary>Gets the density in the relaxed state of the fluid</summary>
				property float RestDensity
				{
					float get();
				}
				/// <summary>Gets the kernel radius multiplier</summary>
				property float KernelRadiusMultiplier
				{
					float get();
				}
				/// <summary>Gets the the motion limit multiplier</summary>
				property float MotionLimitMultiplier
				{
					float get();
				}
				/// <summary>Gets the distance between particles and collision geometry, which is maintained during simulation</summary>
				property float CollisionDistanceMultiplier
				{
					float get();
				}
				/// <summary>Gets the fluid packet size used for parallelization of the fluid computations</summary>
				property int PacketSizeMultiplier
				{
					int get();
				}
				/// <summary>Gets or Sets the the fluid stiffness (must be positive)</summary>
				property float Stiffness
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the fluid viscosity (must be positive)</summary>
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
				/// <summary>Gets or Sets the fluid damping (must be positive)</summary>
				property float Damping
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property float FadeInTime
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the external acceleration applied to each particle at each time step</summary>
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
				
				/// <summary>Gets or Sets the fluid collision restitution used for collision with static actors</summary>
				property float RestitutionForStaticShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets fluid collision adhesion (friction) used for collision with static actors</summary>
				property float DynamicFrictionForStaticShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets Sets the static friction used for collision with static actors</summary>
				property float StaticFrictionForStaticShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets Sets the static friction used for collision with static actors</summary>
				property float StaticFrictionForDynamicShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the fluid collision attraction used for collision with static actors</summary>
				property float AttractionForStaticShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the fluid collision restitution used for collision with dynamic actors</summary>
				property float RestitutionForDynamicShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets fluid collision adhesion (friction) used for collision with dynamic actors</summary>
				property float DynamicFrictionForDynamicShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the fluid collision attraction used for collision with dynamic actors</summary>
				property float AttractionForDynamicShapes
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the collision response coefficient</summary>
				property float CollisionResponseCoefficient
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the simulation method of the fluid</summary>
				property FluidSimulationMethod SimulationMethod
				{
					FluidSimulationMethod get();
					void set( FluidSimulationMethod value );
				}
				/// <summary>Gets or Sets the collision method of the fluid</summary>
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
				
				/// <summary>Gets or Sets the wrapper for user buffers, which configure where particle data is written to</summary>
				property ParticleData^ ParticleWriteData
				{
					ParticleData^ get();
					void set( ParticleData^ value );
				}
				/// <summary>Sets the wrapper for user ID buffers, which configure where IDs of deleted particles are written to</summary>
				property ParticleIdData^ ParticleDeletionIdWriteData
				{
					ParticleIdData^ get();
					void set( ParticleIdData^ value );
				}
				/// <summary>Sets the wrapper for user ID buffers, which configure where IDs of created particles are written to</summary>
				property ParticleIdData^ ParticleCreationIdWriteData
				{
					ParticleIdData^ get();
					void set( ParticleIdData^ value );
				}
				/// <summary>Sets the wrapper for user buffers, which configure where fluid packet data is written to</summary>
				property StillDesign::PhysX::FluidPacketData^ FluidPacketData
				{
					StillDesign::PhysX::FluidPacketData^ get();
					void set( StillDesign::PhysX::FluidPacketData^ value );
				}
				
				/// <summary>Gets or Sets an arbitary 1:1 object</summary>
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
			
			internal:
				property NxFluid* UnmanagedPointer
				{
					NxFluid* get();
				}
		};
	};
};