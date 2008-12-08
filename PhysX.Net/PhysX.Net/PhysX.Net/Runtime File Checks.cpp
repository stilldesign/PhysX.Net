#include "StdAfx.h"

#include "Runtime File Checks.h"

using namespace System;
using namespace System::Globalization;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Security::Cryptography;

using namespace StillDesign::PhysX;

void RuntimeFileChecks::Check()
{
	CheckFile( "NxCharacter.dll", gcnew array<Byte>( 16 ) { 0x36, 0x65, 0xD7, 0x68, 0x21, 0xE8, 0x3A, 0x91, 0x71, 0x8F, 0xE4, 0x6D, 0x6F, 0xCB, 0xDA, 0x79 } );
	CheckFile( "NxCooking.dll", gcnew array<Byte>( 16 ) { 0x06, 0x84, 0xF8, 0x16, 0xBE, 0x2E, 0x7E, 0x7B, 0x8E, 0x06, 0x48, 0x94, 0x5A, 0xFE, 0x4B, 0x5A } );
	CheckFile( "PhysXLoader.dll", gcnew array<Byte>( 16 ) { 0x20, 0xB1, 0x17, 0x14, 0xB0, 0xC6, 0x3F, 0x3F, 0x59, 0x4E, 0xC5, 0xDD, 0x6A, 0x00, 0xD7, 0xE6 } );
}

void RuntimeFileChecks::CheckFile( String^ filename, array<Byte>^ knownHash )
{
	try
	{
		MD5^ md5 = MD5::Create();
		
		FileStream^ stream = gcnew FileStream( FindLibraryPath( filename ), FileMode::Open, FileAccess::Read );
		
		array<Byte>^ fileHash = md5->ComputeHash( stream );
		
		stream->Close();
		
		if( CompareHash( knownHash, fileHash ) == false )
			throw gcnew DllNotFoundException( String::Format( CultureInfo::CurrentCulture, "PhysX library \"{0}\" is missing, corrupt or has invalid version.", filename ) );
	}
	catch( FileNotFoundException^ exception )
	{
		throw gcnew DllNotFoundException( String::Format( CultureInfo::CurrentCulture, "PhysX library \"{0}\" is missing.", filename ), exception );
	}
	catch( DirectoryNotFoundException^ exception )
	{
		throw gcnew DllNotFoundException( String::Format( CultureInfo::CurrentCulture, "PhysX library \"{0}\" is missing.", filename ), exception );
	}
	catch( Exception^ ex )
	{
		throw ex;
	}
}

String^ RuntimeFileChecks::FindLibraryPath( System::String^ name )
{
	Assembly^ assembly = GetBestAssembly();
	
	String^ path;
	
	Uri^ executableUri = gcnew Uri( assembly->CodeBase );
	path = Path::Combine( Path::GetDirectoryName( executableUri->LocalPath ), name );
	if ( File::Exists( path ) )
		return path;

	path = Path::Combine( Environment::SystemDirectory, name );
	if ( File::Exists( path ) )
		return path;

	path = Path::Combine( GetEnvironmentPathVariable( "WINDIR" ), name );
	if ( File::Exists( path ) )
		return path;

	path = Path::Combine( Environment::CurrentDirectory, name );
	if ( File::Exists( path ) )
		return path;
	
	array<String^>^ environmentPaths = GetEnvironmentPathVariable( "PATH" )->Split( gcnew array<Char>( 1 ) { ';' }, StringSplitOptions::RemoveEmptyEntries );
	for each ( String^ envPath in environmentPaths )
	{
		path = Path::Combine( envPath, name );
		if ( File::Exists( path ) )
			return path;
	}

	throw gcnew FileNotFoundException();
}

Assembly^ RuntimeFileChecks::GetBestAssembly()
{
	if( Assembly::GetEntryAssembly() != nullptr )
		return Assembly::GetEntryAssembly();
	
	if( Assembly::GetExecutingAssembly() != nullptr )
		return Assembly::GetExecutingAssembly();
	
	throw gcnew PhysXException( "Could not find suitable assembly" );
}

#pragma push_macro( "GetEnvironmentVariable" )
#undef GetEnvironmentVariable

String^ RuntimeFileChecks::GetEnvironmentPathVariable( String^ name )
{
	if( String::IsNullOrEmpty( name ) == true )
		throw gcnew ArgumentNullException( "name" );
	
	String^ variable = Environment::GetEnvironmentVariable( name );
	
	variable = variable->Replace( "\"", String::Empty );
	variable = variable->Replace( "'", String::Empty );
	variable = variable->Trim();
	
	return variable;
}

#pragma pop_macro( "GetEnvironmentVariable" )

bool RuntimeFileChecks::CompareHash( array<Byte>^ a, array<Byte>^ b )
{
	if( a->Length != b->Length )
		return false;
	
	for( int x = 0; x < a->Length; x++ )
	{
		if( a[ x ] != b[ x ] )
			return false;
	}
	
	return true;
}