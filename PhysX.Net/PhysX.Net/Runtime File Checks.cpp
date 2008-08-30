#include "StdAfx.h"

#include "Runtime File Checks.h"

using namespace System;
using namespace System::IO;
using namespace System::Security::Cryptography;

using namespace StillDesign::PhysX;

bool RuntimeFileChecks::Check()
{
	if( CheckFile( "NxCharacter.dll", 0x36, 0x65, 0xD7, 0x68, 0x21, 0xE8, 0x3A, 0x91, 0x71, 0x8F, 0xE4, 0x6D, 0x6F, 0xCB, 0xDA, 0x79 ) == false )
		return false;
	
	if( CheckFile( "NxCooking.dll", 0x06, 0x84, 0xF8, 0x16, 0xBE, 0x2E, 0x7E, 0x7B, 0x8E, 0x06, 0x48, 0x94, 0x5A, 0xFE, 0x4B, 0x5A ) == false )
		return false;
	
	if( CheckFile( "PhysXLoader.dll", 0x20, 0xB1, 0x17, 0x14, 0xB0, 0xC6, 0x3F, 0x3F, 0x59, 0x4E, 0xC5, 0xDD, 0x6A, 0x00, 0xD7, 0xE6 ) == false )
		return false;
	
	return true;
}

bool RuntimeFileChecks::CheckFile( String^ filename, ... array<int>^ hash )
{
	MD5^ md5 = MD5::Create();
	
	FileStream^ stream = gcnew FileStream( filename, FileMode::Open );
	
	array<Byte>^ fileHash = md5->ComputeHash( stream );
	
	stream->Close();
	
	if( hash->Length != fileHash->Length )
		return false;
	
	for( int x = 0; x < hash->Length; x++ )
	{
		if( fileHash[ x ] != hash[ x ] )
			return false;
	}
	
	return true;
}