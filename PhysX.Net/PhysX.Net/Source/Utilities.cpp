#include "StdAfx.h"

#include "Utilities.h"
#include "Functions.h"
#include "Scene.h"
#include "Core.h"
#include "Error Report.h"

using namespace System::IO;
using namespace StillDesign::PhysX;
using namespace StillDesign::PhysX::Utilities;

bool StillDesign::PhysX::Utilities::Utilities::SaveCollection( PhysicsCollection^ physicsCollection, String^ path, UtilitiesFileType fileType )
{
	return SaveCollection( physicsCollection, path, fileType, true, false );
}
bool StillDesign::PhysX::Utilities::Utilities::SaveCollection( PhysicsCollection^ physicsCollection, String^ path, UtilitiesFileType fileType, bool saveDefaults, bool saveCookedData )
{
	if( physicsCollection == nullptr )
		throw gcnew ArgumentNullException( "physicsCollection" );
	if( String::IsNullOrEmpty( path ) == true )
		throw gcnew ArgumentException( "Invalid path", "path" );
	
	bool result = NXU::saveCollection( physicsCollection->UnmanagedPointer, Functions::ManagedToUnmanagedString( path ), (NXU::NXU_FileType)fileType, saveDefaults, saveCookedData );
	
	return result;
}

PhysicsCollection^ StillDesign::PhysX::Utilities::Utilities::LoadCollection( String^ file, UtilitiesFileType fileType )
{
	if( File::Exists( file ) == false )
		throw gcnew FileNotFoundException( "Could not find Physics Collection file", file );
	
	NXU::NxuPhysicsCollection* collection = NXU::loadCollection( Functions::ManagedToUnmanagedString( file ), (NXU::NXU_FileType)fileType );
	
	if( collection == NULL )
		throw gcnew PhysXException( "Failed to create a Physics Collection" );
	
	return gcnew PhysicsCollection( collection );
}

PhysicsCollection^ StillDesign::PhysX::Utilities::Utilities::ExtractCollectionFromScene( Scene^ scene )
{
	NXU::NxuPhysicsCollection* collection = NXU::extractCollectionScene( scene->UnmanagedPointer );
	
	return gcnew PhysicsCollection( collection );
}

bool StillDesign::PhysX::Utilities::Utilities::CoreDump( Core^ core, String^ file, UtilitiesFileType fileType )
{
	return coreDump( core->UnmanagedPointer, Functions::ManagedToUnmanagedString( file ), (NXU::NXU_FileType)fileType );
}

StillDesign::PhysX::Utilities::ErrorReport^ StillDesign::PhysX::Utilities::Utilities::ErrorReport::get()
{
	return _errorReport;
}
void StillDesign::PhysX::Utilities::Utilities::ErrorReport::set( StillDesign::PhysX::Utilities::ErrorReport^ value )
{
	_errorReport = value;
	
	if( value == nullptr )
		NXU::setErrorReport( NULL );
	else
		NXU::setErrorReport( value->UnmanagedPointer );
}