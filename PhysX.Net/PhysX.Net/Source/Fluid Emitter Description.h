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
		ref class Scene;
		
		public ref class FluidEmitterDescription : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
			
			private:
				NxFluidEmitterDesc* _fluidEmitterDesc;
				
				Shape^ _shape;
				
				Object^ _userData;
			
			public:
				FluidEmitterDescription();
			internal:
				FluidEmitterDescription( NxFluidEmitterDesc* emitterDesc );
			public:
				~FluidEmitterDescription();
			protected:
				!FluidEmitterDescription();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
			public:
				void SetToDefault();
				bool IsValid();
				
				/// <summary>Gets or Sets the name of the emitter</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets or Sets the emitter's pose relative to the frameShape</summary>
				property Matrix RelativePose
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary>Gets or Sets the shape the emitter is attached to</summary>
				property StillDesign::PhysX::Shape^ FrameShape
				{
					StillDesign::PhysX::Shape^ get();
					void set( StillDesign::PhysX::Shape^ value );
				}
				/// <summary>Gets or Sets the emitter's mode of operation</summary>
				property EmitterType Type
				{
					EmitterType get();
					void set( EmitterType value );
				}
				/// <summary>Gets or Sets the maximum number of particles which are emitted from this emitter</summary>
				property int MaximumParticles
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the emitter's shape can either be rectangular or elliptical</summary>
				property EmitterShape Shape
				{
					EmitterShape get();
					void set( EmitterShape value );
				}
				/// <summary>Gets or Sets the sizes of the emitter in the directions of the first and the second axis of its orientation frame (relPose)</summary>
				property float DimensionX
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the sizes of the emitter in the directions of the first and the second axis of its orientation frame (relPose)</summary>
				property float DimensionY
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the random vector with values for each axis direction of the emitter orientation</summary>
				property Vector3 RandomPosition
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the random angle deviation from emission direction</summary>
				property float RandomAngle
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the velocity magnitude of the emitted fluid particles</summary>
				property float FluidVelocityMagnitude
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the rate specifies how many particles are emitted per second</summary>
				property float Rate
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the specifies the time in seconds an emitted particle lives</summary>
				property float ParticleLifetime
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the a factor for the impulse transfer from attached emitter to body</summary>
				property float RepulsionCoefficient
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the combination of FluidEmitterFlags</summary>
				property FluidEmitterFlag Flags
				{
					FluidEmitterFlag get();
					void set( FluidEmitterFlag value );
				}
				
				/// <summary>Gets or Sets an arbitary 1:1 object</summary>
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
			
			internal:
				property NxFluidEmitterDesc* UnmanagedPointer
				{
					NxFluidEmitterDesc* get();
				}
		};
	};
};