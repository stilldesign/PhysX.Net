#pragma once

#include "IDisposable.h"
#include "Enums.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class PhysicsStream;
		
		public ref class ParticleUpdateData : IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
			
			private:
				NxParticleUpdateData* _updateData;
				
				PhysicsStream^ _forceStream;
				PhysicsStream^ _flagsStream;
				PhysicsStream^ _idsStream;
			
			public:
				ParticleUpdateData();
				~ParticleUpdateData();
			protected:
				!ParticleUpdateData();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				void SetToDefault();
				bool IsValid();
				
				PhysicsStream^ AllocateForcesStream( int size, int strideSize );
				generic<typename T> where T : ValueType PhysicsStream^ AllocateForcesStream( int numberOfForces );
				
				PhysicsStream^ AllocateFlagsStream( int size, int strideSize );
				generic<typename T> where T : ValueType PhysicsStream^ AllocateFlagsStream( int numberOfFlags );
				
				PhysicsStream^ AllocateIdsStream( int size, int strideSize );
				generic<typename T> where T : ValueType PhysicsStream^ AllocateIdsStream( int numberOfIds );
				
				property StillDesign::PhysX::ForceMode ForceMode
				{
					StillDesign::PhysX::ForceMode get();
					void set( StillDesign::PhysX::ForceMode value );
				}
				property int NumberOfUpdates
				{
					int get();
					void set( int value );
				}
				
				property PhysicsStream^ ForceStream
				{
					PhysicsStream^ get();
				}
				property PhysicsStream^ FlagsStream
				{
					PhysicsStream^ get();
				}
				property PhysicsStream^ IdsStream
				{
					PhysicsStream^ get();
				}
			
			internal:
				property NxParticleUpdateData* UnmanagedPointer
				{
					NxParticleUpdateData* get();
				}
		};
	};
};