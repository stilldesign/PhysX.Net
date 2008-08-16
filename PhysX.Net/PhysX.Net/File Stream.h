#pragma once

#include <NxStream.h> 

using namespace System;

namespace stillDesign
{
	namespace PhysX
	{
		class UserFileStream : public NxStream
		{
			private:
				FILE* _fp;
				
				__int64 _size;
			
			public:
				UserFileStream( const char* path, bool load );
				virtual ~UserFileStream();
				
				void Close();
				
				virtual NxU8 readByte() const;
				virtual NxU16 readWord() const;
				virtual NxU32 readDword() const;
				virtual float readFloat() const;
				virtual double readDouble() const;
				virtual void readBuffer( void* buffer, NxU32 size ) const;

				virtual NxStream& storeByte( NxU8 b );
				virtual NxStream& storeWord( NxU16 w );
				virtual NxStream& storeDword( NxU32 d );
				virtual NxStream& storeFloat( NxReal f );
				virtual NxStream& storeDouble( NxF64 f );
				virtual NxStream& storeBuffer( const void* buffer, NxU32 size );
				
				__int64 getSize();
		};
		
		public ref class FileStream : public IStream
		{
			private:
				UserFileStream* _fileStream;
			
			public:
				FileStream( String^ path, bool load );
				~FileStream();
				
				void Close();
				
				virtual Byte ReadByte();
				virtual UInt16 ReadShort();
				virtual UInt32 ReadInt();
				virtual Single ReadFloat();
				virtual Double ReadDouble();
				virtual array< Byte >^ ToArray();
				
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