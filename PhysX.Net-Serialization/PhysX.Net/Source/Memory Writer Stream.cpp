#include "StdAfx.h"

#include "User Memory Writer Stream.h"
#include "Memory Writer Stream.h"

using namespace StillDesign::PhysX;

MemoryWriterStream::MemoryWriterStream()
{
	_writer = new UserMemoryWriterStream();
}
MemoryWriterStream::~MemoryWriterStream()
{
	this->!MemoryWriterStream();
}
MemoryWriterStream::!MemoryWriterStream()
{
	SAFE_DELETE( _writer );
}

//MemoryWriterStream^ MemoryWriterStream::FromStream( Stream^ stream )
//{
//	if( stream == nullptr )
//		throw gcnew ArgumentNullException( "stream" );
//	
//	
//}

void MemoryWriterStream::Write( Byte value )
{
	_writer->storeByte( value );
}
void MemoryWriterStream::Write( UInt16 value )
{
	_writer->storeWord( value );
}
void MemoryWriterStream::Write( UInt32 value )
{
	_writer->storeDword( value );
}
void MemoryWriterStream::Write( Single value )
{
	_writer->storeFloat( value );
}
void MemoryWriterStream::Write( Double value )
{
	_writer->storeDouble( value );
}

array< Byte >^ MemoryWriterStream::ToArray()
{
	array<Byte>^ buffer = gcnew array<Byte>( _writer->currentSize );
	
	for( unsigned int x = 0; x < _writer->currentSize; x++ )
	{
		buffer[ x ] = _writer->data[ x ];
	}
	
	return buffer;
}

String^ MemoryWriterStream::ToString()
{
	return String::Format( "Memory Writer Stream. Length: {0}", this->Length );
}

//

int MemoryWriterStream::Length::get()
{
	return _writer->currentSize;
}

NxStream* MemoryWriterStream::UnmanagedPointer::get()
{
	return _writer;
}
UserMemoryWriterStream* MemoryWriterStream::UnmanagedPointer2::get()
{
	return _writer;
}