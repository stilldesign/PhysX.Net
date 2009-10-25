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
	CheckFile( "NxCharacter.dll", gcnew array<Byte>( 16 ) NxCharacterDllMD5 );
	CheckFile( "PhysXCooking.dll", gcnew array<Byte>( 16 ) PhysXCookingDllMD5 );
	CheckFile( "PhysXLoader.dll", gcnew array<Byte>( 16 ) PhysXLoaderDllMD5 );
	CheckFile( "PhysXCore.dll", gcnew array<Byte>( 16 ) PhysXCoreDllMD5 );
	CheckFile( "PhysXDevice.dll", gcnew array<Byte>( 16 ) PhysXDeviceDllMD5 );
}

void RuntimeFileChecks::CheckFile( String^ filename, array<Byte>^ knownHash )
{
	FileStream^ stream;
	try
	{
		MD5^ md5 = MD5::Create();
		
		stream = gcnew FileStream( FindLibraryPath( filename ), FileMode::Open, FileAccess::Read );
		
		array<Byte>^ fileHash = md5->ComputeHash( stream );
		
		if( CompareHash( knownHash, fileHash ) == false )
			throw gcnew DllNotFoundException( String::Format( CultureInfo::CurrentCulture, "PhysX library \"{0}\" is missing, corrupt or has invalid version. The required version is: {1}", filename, RequiredPhysXVersion ) );
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
	}finally{
		if( stream != nullptr )
			stream->Close();
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