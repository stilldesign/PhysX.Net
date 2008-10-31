#pragma once

#include "IDisposable.h"

using namespace System;

class NxParticleData;

namespace StillDesign
{
	namespace PhysX
	{
		ref class PhysicsStream;
		
		public ref class ParticleData : StillDesign::PhysX::IDisposable
		{
			public:
				[Flags]
				enum class Type
				{
					Position = (1 << 0),
					Density = (1 << 1),
					Velocity = (1 << 2),
					Life = (1 << 3),
					ID = (1 << 4),
					Flag = (1 << 5),
					CollisionNormal = (1 << 6)
				};
				
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
				
			private:
				NxParticleData* _data;
				
				PhysicsStream^ _positionBuffer;
				PhysicsStream^ _velocityBuffer;
				PhysicsStream^ _lifeBuffer;
				PhysicsStream^ _densityBuffer;
				PhysicsStream^ _idBuffer;
				PhysicsStream^ _flagBuffer;
				PhysicsStream^ _collisionNormalBuffer;
				
			public:
				ParticleData();
			internal:
				//ParticleData( NxParticleData data );
				ParticleData( NxParticleData* data );
			public:
				~ParticleData();
			protected:
				!ParticleData();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
			public:
				/// <summary>Sets the particle data to default</summary>
				void SetToDefault();
				/// <summary>Is the particle data valid</summary>
				bool IsValid();
				
			internal:
				static ParticleData^ FromUnmanagedPointer( NxParticleData* particleData );
				
			public:
				/// <summary>Allocates memory for the particle positions</summary>
				/// <param name="numberOfParticles">The number of particles to allocate</param>
				/// <typeparam name="T">The type of each position</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocatePositionBuffer( int numberOfParticles );
				/// <summary>Allocates memory for the particle positions</summary>
				/// <param name="size">The number of bytes to allocate</param>
				/// <param name="strideSize">The number of bytes between each particle position</param>
				PhysicsStream^ AllocatePositionBuffer( int size, int strideSize );
				
				/// <summary>Allocates memory for the particle velocities</summary>
				/// <param name="numberOfParticles">The number of particles to allocate</param>
				/// <typeparam name="T">The type of each velocity</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateVelocityBuffer( int numberOfParticles );
				/// <summary>Allocates memory for the particle velocities</summary>
				/// <param name="size">The number of bytes to allocate</param>
				/// <param name="strideSize">The number of bytes between each particle velocity</param>
				PhysicsStream^ AllocateVelocityBuffer( int size, int strideSize );
				
				/// <summary>Allocates memory for the particle life</summary>
				/// <param name="numberOfParticles">The number of particles to allocate</param>
				/// <typeparam name="T">The type of each life</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateLifeBuffer( int numberOfParticles );
				/// <summary>Allocates memory for the particle life times</summary>
				/// <param name="size">The number of bytes to allocate</param>
				/// <param name="strideSize">The number of bytes between each particle life</param>
				PhysicsStream^ AllocateLifeBuffer( int size, int strideSize );
				
				/// <summary>Allocates memory for the particle density</summary>
				/// <param name="numberOfParticles">The number of particles to allocate</param>
				/// <typeparam name="T">The type of each density</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateDensityBuffer( int numberOfParticles );
				/// <summary>Allocates memory for the particle densities</summary>
				/// <param name="size">The number of bytes to allocate</param>
				/// <param name="strideSize">The number of bytes between each particle density</param>
				PhysicsStream^ AllocateDensityBuffer( int size, int strideSize );
				
				/// <summary>Allocates memory for the particle ids</summary>
				/// <param name="numberOfParticles">The number of particles to allocate</param>
				/// <typeparam name="T">The type of each id</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateIdBuffer( int numberOfParticles );
				/// <summary>Allocates memory for the particle ids</summary>
				/// <param name="size">The number of bytes to allocate</param>
				/// <param name="strideSize">The number of bytes between each particle id</param>
				PhysicsStream^ AllocateIdBuffer( int size, int strideSize );
				
				generic<typename T> where T : ValueType PhysicsStream^ AllocateFlagBuffer( int numberOfParticles );
				/// <summary>Allocates memory for the particle flags</summary>
				/// <param name="size">The number of bytes to allocate</param>
				/// <param name="strideSize">The number of bytes between each particle flag</param>
				PhysicsStream^ AllocateFlagBuffer( int size, int strideSize );
				
				/// <summary>Allocates memory for the particle collision normals</summary>
				/// <param name="numberOfParticles">The number of particles to allocate</param>
				/// <typeparam name="T">The type of each collision normal</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateCollisionNormalBuffer( int numberOfParticles );
				/// <summary>Allocates memory for the particle collision normals</summary>
				/// <param name="size">The number of bytes to allocate</param>
				/// <param name="strideSize">The number of bytes between each collision normal</param>
				PhysicsStream^ AllocateCollisionNormalBuffer( int size, int strideSize );
				
				/// <summary>Allocate memory using common types</summary>
				/// <param name="numberOfParticles">The number of particles to allocate</param>
				/// <param name="types">A combination of Type to allocate</param>
				/// <remarks>Types: Position: Vector3, Velocity: Vector3, Life:float, Density:float, CollisionNormal:Vector3, Flag:unsigned int, ID:unsigned int</remarks>
				void AllocateCommonParticleData( int numberOfParticles, ParticleData::Type types );
				
				//
				
				/// <summary>Gets or Sets a name</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets or Sets the number of particles</summary>
				property Nullable<int> NumberOfParticles
				{
					Nullable<int> get();
					void set( Nullable<int> value );
				}
				/// <summary>Gets the stream to positions buffer</summary>
				property PhysicsStream^ PositionBuffer
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets the stream to velocity buffer</summary>
				property PhysicsStream^ VelocityBuffer
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets the stream to life buffer</summary>
				property PhysicsStream^ LifeBuffer
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets the stream to density buffer</summary>
				property PhysicsStream^ DensityBuffer
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets the stream to id buffer</summary>
				property PhysicsStream^ IDBuffer
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets the stream to flag buffer</summary>
				property PhysicsStream^ FlagBuffer
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets the stream to collision normal buffer</summary>
				property PhysicsStream^ CollisionNormalBuffer
				{
					PhysicsStream^ get();
				}
				
				/// <summary>Gets the number of bytes between each position</summary>
				property int PositionBufferStrideSize
				{
					int get();
				}
				/// <summary>Gets the number of bytes between each velocity</summary>
				property int VelocityBufferStrideSize
				{
					int get();
				}
				/// <summary>Gets the number of bytes between each life</summary>
				property int LifeBufferStrideSize
				{
					int get();
				}
				/// <summary>Gets the number of bytes between each density</summary>
				property int DensityBufferStrideSize
				{
					int get();
				}
				/// <summary>Gets the number of bytes between each id</summary>
				property int IDBufferStrideSize
				{
					int get();
				}
				/// <summary>Gets the number of bytes between each flag</summary>
				property int FlagBufferStrideSize
				{
					int get();
				}
				/// <summary>Gets the number of bytes between each collision normal</summary>
				property int CollisionNormalBufferStrideSize
				{
					int get();
				}
			
			internal:
				property NxParticleData* UnmanagedPointer
				{
					NxParticleData* get();
				}
		};
	};
};