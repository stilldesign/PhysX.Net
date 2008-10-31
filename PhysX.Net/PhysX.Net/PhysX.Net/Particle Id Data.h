#pragma once

#include "IDisposable.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class PhysicsStream;
		
		public ref class ParticleIdData : IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
			
			private:
				NxParticleIdData* _data;
				
				PhysicsStream^ _idsStream;
				
			public:
				ParticleIdData();
			internal:
				ParticleIdData( NxParticleIdData* data );
			public:
				~ParticleIdData();
			protected:
				!ParticleIdData();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				void SetToDefault();
				bool IsValid();
				
				PhysicsStream^ AllocateIds( int size, int strideSize );
				generic<typename T> where T : ValueType PhysicsStream^ AllocateIds( int numberOfIds );
				
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				property int NumberOfIds
				{
					int get();
					void set( int value );
				}
				property int StrideSize
				{
					int get();
				}
			
			internal:
				property NxParticleIdData* UnmanagedPointer
				{
					NxParticleIdData* get();
				}
		};
	};
};