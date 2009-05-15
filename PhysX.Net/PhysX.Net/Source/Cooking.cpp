#include "StdAfx.h"

#include "Cooking.h"
#include "Cooking Parameters.h"
#include "Triangle Mesh Description.h"
#include "Convex Mesh Description.h"
#include "Cloth Mesh Description.h"
#include "User Output Stream.h"
#include "Soft Body Mesh Description.h"
#include "Memory Writer Stream.h"
#include "User Memory Writer Stream.h"
#include "PhysX Exception.h"

#include <NxCooking.h> 

using namespace StillDesign::PhysX;

static Cooking::Cooking()
{
	_cooking = NxGetCookingLib( NX_PHYSICS_SDK_VERSION );
	
	if( _cooking == NULL )
		throw gcnew PhysXException( "Cooking library unavailable" );

	CookingParameters parameters;
		parameters.Platform = Platform::PC;
		parameters.ResourceType = CookingResourceType::Performance;
		parameters.SkinWidth = 0.025f;
	
	Cooking::Parameters = parameters;
}
Cooking::~Cooking()
{
	this->!Cooking();
}
Cooking::!Cooking()
{
	_cooking->NxCloseCooking();
	
	_cooking = NULL;
	
	_userOutputStream = nullptr;
}

bool Cooking::IsPlatformMismatch()
{
	return _cooking->NxPlatformMismatch();
}
void Cooking::InitializeCooking()
{
	InitializeCooking( nullptr );
}
void Cooking::InitializeCooking( UserOutputStream^ outputStream )
{
	NxUserOutputStream* output = outputStream == nullptr ? NULL : outputStream->UnmanagedPointer;
	
	_userOutputStream = outputStream;
	
	if( _cooking->NxInitCooking( NULL, output ) == false )
		throw gcnew PhysXException( "Unable to initialize cooking" );
}
void Cooking::CloseCooking()
{
	_cooking->NxCloseCooking();
	
	_userOutputStream = nullptr;
}

bool Cooking::CookTriangleMesh( TriangleMeshDescription^ description, Stream^ stream )
{
	if( description == nullptr )
		throw gcnew ArgumentNullException( "description" );
	if( description->IsValid() == false )
		throw gcnew ArgumentException( "Description is invalid" );
	
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanWrite == false )
		throw gcnew ArgumentException( "Stream is not writable", "stream" );
	
	MemoryWriterStream^ ms = gcnew MemoryWriterStream();
	NxStream* s = ms->UnmanagedPointer;
	bool result = _cooking->NxCookTriangleMesh( *description->UnmanagedPointer, *s );
	
	if( result == false )
	{
		return false;
	}else{
		array<Byte>^ data = gcnew array<Byte>( ms->Length );
		pin_ptr<Byte> b = &data[ 0 ];
		memcpy_s( b, sizeof( Byte ) * ms->Length, ms->UnmanagedPointer2->data, ms->Length );
		
		stream->Write( data, 0, ms->Length );
		
		return true;
	}
}
bool Cooking::CookConvexMesh( ConvexMeshDescription^ description, Stream^ stream )
{
	if( description == nullptr )
		throw gcnew ArgumentNullException( "description" );
	if( description->IsValid() == false )
		throw gcnew ArgumentException( "Description is invalid" );
	
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanWrite == false )
		throw gcnew ArgumentException( "Stream is not writable", "stream" );
	
	MemoryWriterStream^ ms = gcnew MemoryWriterStream();
	NxStream* s = ms->UnmanagedPointer;
	bool result = _cooking->NxCookConvexMesh( *description->UnmanagedPointer, *s );
	
	if( result == false )
	{
		return false;
	}else{
		array<Byte>^ data = gcnew array<Byte>( ms->Length );
		pin_ptr<Byte> b = &data[ 0 ];
		memcpy_s( b, sizeof( Byte ) * ms->Length, ms->UnmanagedPointer2->data, ms->Length );
		
		stream->Write( data, 0, ms->Length );
		
		return true;
	}
}
bool Cooking::CookClothMesh( ClothMeshDescription^ description, Stream^ stream )
{
	if( description == nullptr )
		throw gcnew ArgumentNullException( "description" );
	if( description->IsValid() == false )
		throw gcnew ArgumentException( "Description is invalid" );
	
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanWrite == false )
		throw gcnew ArgumentException( "Stream is not writable", "stream" );
	
	MemoryWriterStream^ ms = gcnew MemoryWriterStream();
	NxStream* s = ms->UnmanagedPointer;
	bool result = _cooking->NxCookClothMesh( *description->UnmanagedPointer, *s );
	
	if( result == false )
	{
		return false;
	}else{
		array<Byte>^ data = gcnew array<Byte>( ms->Length );
		pin_ptr<Byte> b = &data[ 0 ];
		memcpy_s( b, sizeof( Byte ) * ms->Length, ms->UnmanagedPointer2->data, ms->Length );
		
		stream->Write( data, 0, ms->Length );
		
		return true;
	}
}

bool Cooking::CookSoftBodyMesh( SoftBodyMeshDescription^ description, Stream^ stream )
{
	if( description == nullptr )
		throw gcnew ArgumentNullException( "description" );
	if( description->IsValid() == false )
		throw gcnew ArgumentException( "Description is invalid" );
	
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanWrite == false )
		throw gcnew ArgumentException( "Stream is not writable", "stream" );
	
	MemoryWriterStream^ ms = gcnew MemoryWriterStream();
	NxStream* s = ms->UnmanagedPointer;
	bool result = _cooking->NxCookSoftBodyMesh( *description->UnmanagedPointer, *s );
	
	if( result == false )
	{
		return false;
	}else{
		array<Byte>^ data = gcnew array<Byte>( ms->Length );
		pin_ptr<Byte> b = &data[ 0 ];
		memcpy_s( b, sizeof( Byte ) * ms->Length, ms->UnmanagedPointer2->data, ms->Length );
		
		stream->Write( data, 0, ms->Length );
		
		return true;
	}
}

CookingParameters Cooking::Parameters::get()
{
	return (CookingParameters)_cooking->NxGetCookingParams();
}
void Cooking::Parameters::set( CookingParameters value )
{
	_cooking->NxSetCookingParams( (NxCookingParams)value );
}

NxCookingInterface* Cooking::UnmanagedPointer::get()
{
	return _cooking;
}