#pragma once

#include "BufferData.h"
#include "IDisposable.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class PhysicsStream;
		
		public ref class FluidPacketData : BufferData, IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;

			private:
				NxFluidPacketData* _fluidPacketData;
				
				PhysicsStream^ _packetsStream;
				
			public:
				FluidPacketData();
			internal:
				FluidPacketData( NxFluidPacketData* fluidPacketData, bool objectOwner, bool dataOwner );
			public:
				~FluidPacketData();
			protected:
				!FluidPacketData();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				static FluidPacketData^ Clone( FluidPacketData^ data );
				static NxFluidPacketData* Clone( NxFluidPacketData data );

				void SetToDefault();
				bool IsValid();
				
				PhysicsStream^ AllocateFluidPacketData( int numberOfFluidPackets );
				
				property PhysicsStream^ FluidPackets
				{
					PhysicsStream^ get();
				}
				property int NumberOfFluidPackets
				{
					int get();
				}
			
			internal:
				property NxFluidPacketData* UnmanagedPointer
				{
					NxFluidPacketData* get();
				}
		};
	};
};