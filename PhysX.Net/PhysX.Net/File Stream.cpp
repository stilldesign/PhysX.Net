#include "StdAfx.h"

#include "Functions.h"
#include "Stream.h"

using namespace stillDesign::PhysX;

// Native
UserFileStream::UserFileStream( const char* path, bool load ) : NxStream()
{
	errno_t error = fopen_s( &_fp, path, load == true ? "rb" : "wb" );
	
#if _DEBUG
	if( load == true )
	{
		String^ p = Functions::UnmanagedToManagedString( path );
		if( System::IO::File::Exists( p ) == false )
			throw gcnew System::IO::FileNotFoundException( "Could Not Open FileStream Path", p );
	}
#endif
	
	if( load == true )
	{
		System::IO::FileInfo^ fileInfo = gcnew System::IO::FileInfo( Functions::UnmanagedToManagedString( path ) );
		
		_size = fileInfo->Length;
	}else{
		_size = -1;
	}
	
	if( error != 0 )
		throw gcnew System::IO::IOException( String::Format( "Unable to process file. PhysX Error Code = {0}", error ), gcnew PhysicsException( String::Format( "Path: '{0}'", Functions::UnmanagedToManagedString( path ) ) ) );
}
UserFileStream::~UserFileStream()
{
	if( _fp != NULL )
		fclose( _fp );
}

void UserFileStream::Close()
{
	if( fclose( _fp ) != 0 )
		throw gcnew System::IO::IOException( "Unable to Close File" );
}

// Reading
NxU8 UserFileStream::readByte() const
{
	NxU8 b;
	size_t r = fread( &b, sizeof( NxU8 ), 1, _fp );
	
	return b;
}
NxU16 UserFileStream::readWord() const
{
	NxU16 s;
	size_t r = fread( &s, sizeof( NxU16 ), 1, _fp );
	
	return s;
}
NxU32 UserFileStream::readDword() const
{
	NxU32 i;
	size_t r = fread( &i, sizeof( NxU32 ), 1, _fp );
	
	return i;
}
NxF32 UserFileStream::readFloat() const
{
	NxF32 f;
	size_t r = fread( &f, sizeof( NxF32 ), 1, _fp );
	
	return f;
}
NxF64 UserFileStream::readDouble() const
{
	NxF64 d;
	size_t r = fread( &d, sizeof( NxF64 ), 1, _fp );
	
	return d;
}
void UserFileStream::readBuffer( void* buffer, NxU32 size ) const
{
	size_t w = fread( buffer, size, 1, _fp );
	NX_ASSERT( w );
}

// Writing
NxStream& UserFileStream::storeByte( NxU8 b )
{
	size_t w = fwrite( &b, sizeof( NxU8 ), 1, _fp );
	NX_ASSERT( w );
	
	return *this;
}
NxStream& UserFileStream::storeWord( NxU16 s )
{
	size_t w = fwrite( &s, sizeof( NxU16 ), 1, _fp );
	NX_ASSERT( w );
	
	return *this;
}
NxStream& UserFileStream::storeDword( NxU32 d )
{
	size_t w = fwrite( &d, sizeof( NxU32 ), 1, _fp );
	NX_ASSERT( w );
	
	return *this;
}
NxStream& UserFileStream::storeFloat( NxReal f )
{
	size_t w = fwrite( &f, sizeof( NxReal ), 1, _fp );
	NX_ASSERT( w );
	
	return *this;
}
NxStream& UserFileStream::storeDouble( NxF64 f )
{
	size_t w = fwrite( &f, sizeof( NxF64 ), 1, _fp );
	NX_ASSERT( w );
	
	return *this;
}
NxStream& UserFileStream::storeBuffer( const void* buffer, NxU32 size )
{
	size_t w = fwrite( buffer, size, 1, _fp );
	NX_ASSERT( w );
	
	return *this;
}
__int64 UserFileStream::getSize()
{
	return _size;
}

//

FileStream::FileStream( String^ path, bool load )
{
	_fileStream = new UserFileStream( Functions::ManagedToUnmanagedString( path ), load );
}
FileStream::~FileStream()
{
	delete _fileStream;
}

void FileStream::Close()
{
	_fileStream->Close();
}

// Reading
Byte FileStream::ReadByte()
{
	return _fileStream->readByte();
}
UInt16 FileStream::ReadShort()
{
	return _fileStream->readWord();
}
UInt32 FileStream::ReadInt()
{
	return _fileStream->readDword();
}
Single FileStream::ReadFloat()
{
	return _fileStream->readFloat();
}
Double FileStream::ReadDouble()
{
	return _fileStream->readDouble();
}
array< Byte >^ FileStream::ToArray()
{
	int s = (int)_fileStream->getSize();
	
	UINT8* data = new UINT8[ s ];
	_fileStream->readBuffer( data, s );
	
	array< Byte >^ buffer = gcnew array< Byte >( s );
	
	for( int x = 0; x < buffer->Length; x++ )
	{
		buffer[ x ] = data[ x ];
	}
	
	delete data;
	
	return buffer;
}

// Writing
void FileStream::Write( Byte value )
{
	_fileStream->storeByte( value );
}
void FileStream::Write( UInt16 value )
{
	_fileStream->storeWord( value );
}
void FileStream::Write( UInt32 value )
{
	_fileStream->storeDword( value );
}
void FileStream::Write( Single value )
{
	_fileStream->storeFloat( value );
}
void FileStream::Write( Double value )
{
	_fileStream->storeDouble( value );
}

NxStream* FileStream::UnmanagedPointer::get()
{
	return _fileStream;
}