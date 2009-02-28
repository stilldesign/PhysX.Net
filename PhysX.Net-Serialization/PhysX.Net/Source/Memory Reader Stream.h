#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		class UserMemoryReaderStream;
		ref class MemoryWriterStream;
		
		private ref class MemoryReaderStream
		{
			private:
				UserMemoryReaderStream* _reader;
				unsigned int _size;
				
			private:
				MemoryReaderStream()
				{
					
				}
			public:
				MemoryReaderStream( array<Byte>^ bytes );
				~MemoryReaderStream();
			protected:
				!MemoryReaderStream();
				
			public:
				static MemoryReaderStream^ FromMemoryWriterStream( MemoryWriterStream^ stream );
			internal:
				static MemoryReaderStream^ FromUnmanagedPointer( NxU8* memory, int length );
			public:
				static MemoryReaderStream^ FromStream( Stream^ stream );
				
				virtual Byte ReadByte();
				virtual UInt16 ReadShort();
				virtual UInt32 ReadInt();
				virtual Single ReadFloat();
				virtual Double ReadDouble();
				/// <summary>Copies the Contents of the Buffer Out to an Array</summary>
				virtual array<Byte>^ ToArray();
				
				void Reset();
			
				property NxStream* UnmanagedPointer
				{
					virtual NxStream* get();
				}
		};
	};
};