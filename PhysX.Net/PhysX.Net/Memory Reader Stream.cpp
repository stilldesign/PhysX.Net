#include "StdAfx.h"

#include "Memory Reader Stream.h"
#include "Memory Writer Stream.h"
#include "User Memory Reader Stream.h"

using namespace StillDesign::PhysX;

MemoryReaderStream::MemoryReaderStream( array< Byte >^ bytes )
{
	NxU8* buffer = new NxU8[ bytes->Length ];
	
	for( int x = 0; x < bytes->Length; x++ )
	{
		buffer[ x ] = bytes[ x ];
	}
	
	_reader = new UserMemoryReaderStream( buffer );
	
	_size = bytes->Length;
}
MemoryReaderStream::~MemoryReaderStream()
{
	this->!MemoryReaderStream();
}
MemoryReaderStream::!MemoryReaderStream()
{
	SAFE_DELETE( _reader );
}

MemoryReaderStream^ MemoryReaderStream::FromMemoryWriterStream( MemoryWriterStream^ stream )
{
	if( stream == nullptr || stream->UnmanagedPointer == NULL )
		throw gcnew ArgumentException( "Stream cannot be null or disposed" );
	
	array< Byte >^ buffer = stream->ToArray();
	
	return gcnew MemoryReaderStream( buffer );
}
MemoryReaderStream^ MemoryReaderStream::FromUnmanagedPointer( NxU8* memory, int length )
{
	MemoryReaderStream^ reader = gcnew MemoryReaderStream();
		reader->_reader = new UserMemoryReaderStream( memory );
		reader->_size = length;
		
	return reader;
}
MemoryReaderStream^ MemoryReaderStream::FromStream( Stream^ stream )
{
	array<Byte>^ data = gcnew array<Byte>( (int)stream->Length );
	stream->Read( data, 0, (int)stream->Length );
	
	return gcnew MemoryReaderStream( data );
}

Byte MemoryReaderStream::ReadByte()
{
	return _reader->readByte();
}
UInt16 MemoryReaderStream::ReadShort()
{
	return _reader->readWord();
}
UInt32 MemoryReaderStream::ReadInt()
{
	return _reader->readDword();
}
Single MemoryReaderStream::ReadFloat()
{
	return _reader->readFloat();
}
Double MemoryReaderStream::ReadDouble()
{
	return _reader->readDouble();
}
array< Byte >^ MemoryReaderStream::ToArray()
{
	array< Byte >^ buffer = gcnew array< Byte >( _size );
	
	for( unsigned int x = 0; x < _size; x++ )
	{
		buffer[ x ] = _reader->buffer[ x ];
	}
	
	return buffer;
}

void MemoryReaderStream::Reset()
{
	_reader->Reset();
}

NxStream* MemoryReaderStream::UnmanagedPointer::get()
{
	return _reader;
}