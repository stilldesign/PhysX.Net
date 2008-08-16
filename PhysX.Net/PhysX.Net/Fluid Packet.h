#pragma once

#include "IDisposable.h"

namespace StillDesign
{
	namespace PhysX
	{
		value class Bounds3;
		
		public ref class FluidPacket : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
			
			private:
				NxFluidPacket* _fluidPacket;
			
			public:
				FluidPacket();
			internal:
				FluidPacket( NxFluidPacket* fluidPacket );
			public:
				~FluidPacket();
			protected:
				!FluidPacket();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				/// <summary>Gets or Sets the AABB of all particles which are inside the same packet</summary>
				property Bounds3 AxisAlignedBoundingBox
				{
					Bounds3 get();
					void set( Bounds3 value );
				}
				/// <summary>Gets or Sets the index of first particle for a given packet</summary>
				property int FirstParticleIndex
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the number of particles inside the packet</summary>
				property int NumberOfParticles
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the packet's Identifier</summary>
				property int PacketID
				{
					int get();
					void set( int value );
				}
		};
	};
};