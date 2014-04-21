#pragma once

#include <NxStream.h> 

namespace StillDesign
{
	namespace PhysX
	{
		class UserMemoryWriterStream;
		
		private ref class MemoryWriterStream
		{
			private:
				UserMemoryWriterStream* _writer;
			
			public:
				MemoryWriterStream();
				~MemoryWriterStream();
			protected:
				!MemoryWriterStream();
			
			public:
				//static MemoryWriterStream^ FromStream( Stream^ stream );
				
				virtual void Write( Byte value );
				virtual void Write( UInt16 value );
				virtual void Write( UInt32 value );
				virtual void Write( float value );
				virtual void Write( double value );
				
				array<Byte>^ ToArray();
				
				virtual String^ ToString() override;
				
				property int Length
				{
					int get();
				}
				
				// VS2005 C++ Bug
				//property NxStream* UnmanagedPointer
				//{
				//	virtual NxStream* get() = StillDesign::PhysX::IStreamWriter::UnmanagedPointer::get
				//	{
				//		return _writer;
				//	}
				//}
				
				property NxStream* UnmanagedPointer
				{
					virtual NxStream* get();
				}
			internal:
				property UserMemoryWriterStream* UnmanagedPointer2
				{
					UserMemoryWriterStream* get();
				}
		};
	};
};