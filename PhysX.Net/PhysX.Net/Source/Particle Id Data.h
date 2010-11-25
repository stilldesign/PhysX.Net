#pragma once

#include "IDisposable.h"
#include "BufferData.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class PhysicsStream;
		
		public ref class ParticleIdData : BufferData, IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
			
			private:
				NxParticleIdData* _data;
				
				PhysicsStream^ _idsStream;
				
			public:
				ParticleIdData();
			internal:
				ParticleIdData( NxParticleIdData* data, bool objectOwner, bool dataOwner );
			public:
				~ParticleIdData();
			protected:
				!ParticleIdData();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
				void SetToDefault();
				bool IsValid();
				
				static ParticleIdData^ Clone( ParticleIdData^ data );
				static NxParticleIdData* Clone( NxParticleIdData data );

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