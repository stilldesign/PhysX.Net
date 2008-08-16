#pragma once

#include "Enums.h"
#include "IDisposable.h"

using namespace System;
UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Shape;
		ref class Fluid;
		ref class FluidEmitterDescription;
		
		public ref class FluidEmitter : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
			
			private:
				NxFluidEmitter* _fluidEmitter;
				
				Fluid^ _fluid;
				Shape^ _shape;
				
				Object^ _userData;
			
			internal:
				FluidEmitter( NxFluidEmitter* emitter );
			public:
				~FluidEmitter();
			protected:
				!FluidEmitter();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
			public:
				FluidEmitterDescription^ SaveToDescription();
				bool LoadFromDescription( FluidEmitterDescription^ description );
				
				/// <summary>Is the Emitter Flag Set</summary>
				bool GetFlag( FluidEmitterFlag flag );
				/// <summary>Sets an Emitter Flag</summary>
				void SetFlag( FluidEmitterFlag flag, bool value );
				bool GetShape( EmitterShape shape );
				bool GetType( EmitterType type );
				
				/// <summary>Resets the particle reservoir.</summary>
				void ResetEmission( int maximumParticles );
				
				//
				
				/// <summary>Gets the Fluid the emitter is owned by</summary>
				property StillDesign::PhysX::Fluid^ Fluid
				{
					StillDesign::PhysX::Fluid^ get();
				}
				
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Returns the number of particles that have been emitted already.</summary>
				property int NumberOfParticlesEmitted
				{
					int get();
				}
				
				/// <summary>Gets or Sets the pose of the emitter in world space.</summary>
				property Matrix GlobalPose
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary>Gets or Sets the position of the emitter in world space.</summary>
				property Vector3 GlobalPosition
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the orientation of the emitter in world space.</summary>
				property Matrix GlobalOrientation
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary>Gets or Sets the pose of the emitter relative to the frameShape.</summary>
				property Matrix LocalPose
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary>Gets or Sets the position of the emitter relative to the frameShape.</summary>
				property Vector3 LocalPosition
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the orientation of the emitter relative to the frameShape.</summary>
				property Matrix LocalOrientation
				{
					Matrix get();
					void set( Matrix value );
				}
				
				/// <summary>Gets or Sets the frame shape.</summary>
				property Shape^ FrameShape
				{
					Shape^ get();
					void set( Shape^ value );
				}
				/// <summary>Gets or Sets the maximal particle number to be emitted.</summary>
				property int MaximumParticles
				{
					int get();
				}
				/// <summary>Gets the radius of the emitter along the x axis.</summary>
				property float DimensionX
				{
					float get();
				}
				/// <summary>Gets the radius of the emitter along the y axis.</summary>
				property float DimensionY
				{
					float get();
				}
				/// <summary>Gets or Sets the maximal random displacement in every dimension.</summary>
				property Vector3 RandomPosition
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the maximal random angle offset (in radians).</summary>
				property float RandomAngle
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the velocity magnitude of the emitted particles.</summary>
				property float FluidVelocityMagnitude
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the emission rate (particles/second).</summary>
				property float Rate
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the particle lifetime.</summary>
				property float ParticleLifetime
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets repulsion coefficient.</summary>
				property float RepulsionCoefficient
				{
					float get();
					void set( float value );
				}
				
				/// <summary>Gets or Sets </summary>
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
			
			internal:
				property NxFluidEmitter* UnmanagedPointer
				{
					NxFluidEmitter* get();
				}
		};
	};
};