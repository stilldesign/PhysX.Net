#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		ref class PhysicsStream;
		
		public ref class FluidPacketData
		{
			private:
				NxFluidPacketData* _fluidPacketData;
				
				PhysicsStream^ _packetsStream;
				
			public:
				FluidPacketData();
			internal:
				FluidPacketData( NxFluidPacketData* fluidPacketData );
			public:
				~FluidPacketData();
			protected:
				!FluidPacketData();
			
			public:
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