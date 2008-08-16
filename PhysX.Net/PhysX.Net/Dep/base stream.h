#pragma once

#include <NxStream.h> 

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		private interface class IStreamReader
		{
			virtual Byte ReadByte();
			virtual UInt16 ReadShort();
			virtual UInt32 ReadInt();
			virtual Single ReadFloat();
			virtual Double ReadDouble();
			virtual array<Byte>^ ToArray();
		
			property NxStream* UnmanagedPointer
			{
				virtual NxStream* get();
			}
		};
		private interface class IStreamWriter
		{
			virtual void Write( Byte value );
			virtual void Write( UInt16 value );
			virtual void Write( UInt32 value );
			virtual void Write( Single value );
			virtual void Write( Double value );
			
			property NxStream* UnmanagedPointer
			{
				virtual NxStream* get();
			}
		};
	};
};