#include "StdAfx.h"

#include "Core.h"
#include "Core Description.h"
#include "User Output Stream.h"
#include "Scene Description.h"
#include "Scene.h"
#include "Convex Mesh.h"
#include "Convex Mesh Description.h"
#include "Height Field Description.h"
#include "CCD Skeleton.h"
#include "Simple Triangle Mesh.h"
#include "Foundation.h"
#include "Memory Reader Stream.h"
#include "Physics Parameters Wrapper.h"
#include "PhysX Initialization Exception.h"

using namespace StillDesign::PhysX;

static Core::Core()
{
	_checkPhysXRuntimeFiles = true;
	_isCoreCreated = false;
}
Core::Core()
{
	if( IsCoreCreated == true )
		throw gcnew PhysXException( "A core instance has already been created" );
		
	if( CheckPhysXRuntimeFiles == true )
		CheckAllPhysXRuntimeFiles( true );
	
	CreateCore( gcnew CoreDescription(), nullptr );
}
Core::Core( CoreDescription^ description, StillDesign::PhysX::UserOutputStream^ userOutputStream )
{
	if( IsCoreCreated == true )
		throw gcnew PhysXException( "A core instance has already been created" );
		
	if( CheckPhysXRuntimeFiles == true )
		CheckAllPhysXRuntimeFiles( true );
	
	CreateCore( description, userOutputStream );
}
Core::Core( NxPhysicsSDK* core )
{
	if( IsCoreCreated == true )
		throw gcnew PhysXException( "A core instance has already been created" );
		
	if( CheckPhysXRuntimeFiles == true )
		CheckAllPhysXRuntimeFiles( true );
	
	Debug::Assert( core != NULL );
	
	ObjectCache::Add( (intptr_t)core, this );
	
	_physicsSDK = core;
	
	for( unsigned int x = 0; x < core->getNbScenes(); x++ )
	{
		Scene^ scene = gcnew Scene( core->getScene( x ) );
		
		_sceneCollection->Add( scene );
	}
	//for( int x = 0; x < sdk->getNbTriangleMeshes(); x++ )
	//{
	//	TriangleMesh^ triangleMesh = TriangleMesh::FromUnmanagedPointer( this, sdk->get
	//}
	for( unsigned int x = 0; x < core->getNbCCDSkeletons(); x++ )
	{
		//CCDSkeleton* skeleton = CCDSkeleton::FromUnmanaged( sdk->getccd
	}
	
	CreateCommon();
}
Core::~Core()
{
	this->!Core();
}
Core::!Core()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	// Delete Children
	array<IDisposeOfChildren^>^ dispose =
	{
		_sceneCollection,
		_triangleMeshCollection,
		_convexMeshCollection,
		_clothMeshCollection,
		_heightFieldCollection,
		_CCDSkeletonCollection,
		_softBodyMeshCollection
	};
	
	for each( IDisposeOfChildren^ disposable in dispose )
	{
		disposable->DisposeOfAll();
	}
	
	//_sceneCollection->DisposeOfAll();
	//_triangleMeshCollection->DisposeOfAll();
	//_convexMeshCollection->DisposeOfAll();
	//_clothMeshCollection->DisposeOfAll();
	//_heightFieldCollection->DisposeOfAll();
	//_CCDSkeletonCollection->DisposeOfAll();
	//_softBodyMeshCollection->DisposeOfAll();
	
	_sceneCollection = nullptr;
	_triangleMeshCollection = nullptr;
	_convexMeshCollection = nullptr;
	_clothMeshCollection = nullptr;
	_heightFieldCollection = nullptr;
	_CCDSkeletonCollection = nullptr;
	
	_userOutputStream = nullptr;
	
	_foundation = nullptr;
	
	NxReleasePhysicsSDK( _physicsSDK );
	_physicsSDK = NULL;
	
	_isCoreCreated = false;
	
	if( ObjectCache::Count > 0 )
		Trace::WriteLine( "Warning: Objects still remain in the object cache. Count: " + ObjectCache::Count );
	
	ObjectCache::Clear();
	
	OnDisposed( this, nullptr );
}

bool Core::IsDisposed::get()
{
	return ( _physicsSDK == NULL );
}

void Core::CreateCore( CoreDescription^ desc, StillDesign::PhysX::UserOutputStream^ userOutputStream )
{
	_userOutputStream = userOutputStream;
	
	NxSDKCreateError error;
	NxUserOutputStream* out = ( userOutputStream == nullptr ? NULL : userOutputStream->UnmanagedPointer );
	
	_physicsSDK = NxCreatePhysicsSDK( NX_PHYSICS_SDK_VERSION, NULL, out, *desc->UnmanagedPointer, &error );
	
	if( _physicsSDK == NULL || error != 0 )
		throw gcnew PhysXInitializationException( (CoreCreationError)error );
	
	ObjectCache::Add( (intptr_t)_physicsSDK, this );
	CreateCommon();
}
void Core::CreateCommon()
{
	_sceneCollection = gcnew ElementCollection<Scene^>();
	_triangleMeshCollection = gcnew ElementCollection<TriangleMesh^>();
	_convexMeshCollection = gcnew ElementCollection<ConvexMesh^>();
	_clothMeshCollection = gcnew ElementCollection<ClothMesh^>();
	_heightFieldCollection = gcnew ElementCollection<HeightField^>();
	_CCDSkeletonCollection = gcnew ElementCollection<CCDSkeleton^>();
	_softBodyMeshCollection = gcnew ElementCollection<SoftBodyMesh^>();
	
	_foundation = gcnew StillDesign::PhysX::Foundation( &_physicsSDK->getFoundationSDK() );
	_physicsParametersWrapper = gcnew PhysicsParametersWrapper( this );

	_checkPhysXRuntimeFiles = true;
	_isCoreCreated = true;
}

bool Core::CheckAllPhysXRuntimeFiles()
{
	return CheckAllPhysXRuntimeFiles( false );
}
bool Core::CheckAllPhysXRuntimeFiles( bool throwOnError )
{
	if( throwOnError == false )
	{
		try
		{
			RuntimeFileChecks::Check();
		}catch ( DllNotFoundException^ ex ){
			System::Diagnostics::Debug::WriteLine( ex->Message );
			
			return false;
		}catch( Exception^ ex ){
			System::Diagnostics::Debug::WriteLine( ex->Message );
			
			return false;
		}
		
		return true;
	}else{
		RuntimeFileChecks::Check();
		
		return true;
	}
}

Scene^ Core::AddScene( NxScene* scene )
{
	Scene^ s = gcnew Scene( scene );
	
	_sceneCollection->Add( s );
	
	return s;
}
TriangleMesh^ Core::AddTriangleMesh( NxTriangleMesh* triangleMesh )
{
	TriangleMesh^ t = gcnew TriangleMesh( triangleMesh, this );
	
	_triangleMeshCollection->Add( t );
	
	return t;
}
ConvexMesh^ Core::AddConvexMesh( NxConvexMesh* convexMesh )
{
	ConvexMesh^ c = gcnew ConvexMesh( convexMesh, this );
	
	_convexMeshCollection->Add( c );
	
	return c;
}
ClothMesh^ Core::AddClothMesh( NxClothMesh* clothMesh )
{
	ClothMesh^ c = gcnew ClothMesh( clothMesh, this );
	
	_clothMeshCollection->Add( c );
	
	return c;
}
HeightField^ Core::AddHeightField( NxHeightField* heightField )
{
	HeightField^ h = gcnew HeightField( heightField, this );
	
	_heightFieldCollection->Add( h );
	
	return h;
}
CCDSkeleton^ Core::AddCCDSkeleton( NxCCDSkeleton* skeleton )
{
	CCDSkeleton^ s = gcnew CCDSkeleton( skeleton, this );
	
	_CCDSkeletonCollection->Add( s );
	
	return s;
}
SoftBodyMesh^ Core::AddSoftBodyMesh( NxSoftBodyMesh* mesh )
{
	SoftBodyMesh^ s = gcnew SoftBodyMesh( mesh, this );
	
	_softBodyMeshCollection->Add( s );
	
	return s;
}

//

Scene^ Core::CreateScene()
{
	return CreateScene( Vector3( 0.0f, -9.81f, 0.0f ), true );
}
Scene^ Core::CreateScene( Vector3 gravity, bool groundPlane )
{
	SceneDescription^ description = gcnew SceneDescription();
		description->Gravity = gravity;
		description->GroundPlaneEnabled = groundPlane;
	
	return CreateScene( description );
}
Scene^ Core::CreateScene( SceneDescription^ sceneDescription )
{
	ThrowIfDescriptionIsNullOrInvalid( sceneDescription, "sceneDescription" );
	
	NxSceneDesc* sceneDesc = sceneDescription->UnmanagedPointer;
	
	const NxSceneDesc desc = *sceneDesc;
	NxScene* scene = _physicsSDK->createScene( desc );
	
	Scene^ s = gcnew Scene( scene );
		s->UserNotify = sceneDescription->UserNotify;
		s->FluidUserNotify = sceneDescription->FluidUserNotify;
		s->UserContactModify = sceneDescription->UserContactModify;
		s->UserContactReport = sceneDescription->UserContactReport;
		s->UserTriggerReport = sceneDescription->UserTriggerReport;
		s->Name = sceneDescription->Name;
		s->UserData = sceneDescription->UserData;
	
	_sceneCollection->Add( s );
	
	return s;
}

TriangleMesh^ Core::CreateTriangleMesh( Stream^ stream )
{
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanRead == false )
		throw gcnew ArgumentException( "Cannot read from stream" );
	if( stream->Length == 0 )
		throw gcnew ArgumentException( "Stream is of length 0" );
	
	array<Byte>^ data = gcnew array<Byte>( (int)stream->Length );
	stream->Read( data, 0, (int)stream->Length );
	
	MemoryReaderStream^ reader = gcnew MemoryReaderStream( data );
	
	NxTriangleMesh* triangleMesh = _physicsSDK->createTriangleMesh( *reader->UnmanagedPointer );
	if( triangleMesh == NULL )
		throw gcnew PhysXException( "Failed to create triangle mesh" );
	
	TriangleMesh^ tm = gcnew TriangleMesh( triangleMesh, this );
	
	_triangleMeshCollection->Add( tm );
	
	return tm;
}
ConvexMesh^ Core::CreateConvexMesh( Stream^ stream )
{
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanRead == false )
		throw gcnew ArgumentException( "Cannot read from stream" );
	if( stream->Length == 0 )
		throw gcnew ArgumentException( "Stream is of length 0" );
	
	array<Byte>^ data = gcnew array<Byte>( (int)stream->Length );
	stream->Read( data, 0, (int)stream->Length );
	
	MemoryReaderStream^ reader = gcnew MemoryReaderStream( data );
	
	NxConvexMesh* convexMesh = _physicsSDK->createConvexMesh( *reader->UnmanagedPointer );
	if( convexMesh == NULL )
		throw gcnew PhysXException( "Failed to create convexMesh" );
	
	StillDesign::PhysX::ConvexMesh^ c = gcnew StillDesign::PhysX::ConvexMesh( convexMesh, this );
	
	_convexMeshCollection->Add( c );
	
	return c;
}
ClothMesh^ Core::CreateClothMesh( Stream^ stream )
{
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanRead == false )
		throw gcnew ArgumentException( "Cannot read from stream" );
	if( stream->Length == 0 )
		throw gcnew ArgumentException( "Stream is of length 0" );
	
	array<Byte>^ data = gcnew array<Byte>( (int)stream->Length );
	stream->Read( data, 0, (int)stream->Length );
	
	MemoryReaderStream^ reader = gcnew MemoryReaderStream( data );
		
	NxClothMesh* clothMesh = _physicsSDK->createClothMesh( *reader->UnmanagedPointer );
	if( clothMesh == NULL )
		throw gcnew PhysXException( "Failed to create cloth mesh" );
	
	ClothMesh^ cm = gcnew ClothMesh( clothMesh, this );
	
	_clothMeshCollection->Add( cm );
	
	return cm;
}
HeightField^ Core::CreateHeightField( HeightFieldDescription^ description )
{
	ThrowIfDescriptionIsNullOrInvalid( description, "description" );
	
	NxHeightField* hf = _physicsSDK->createHeightField( *description->UnmanagedPointer );
	if( hf == NULL )
		throw gcnew PhysXException( "Failed to create height field" );
	
	HeightField^ heightField = gcnew HeightField(  hf, this );
	
	_heightFieldCollection->Add( heightField );
	
	return heightField;
}
CCDSkeleton^ Core::CreateCCDSkeleton( SimpleTriangleMesh^ simpleTriangleMesh )
{
	ThrowIfNullOrDisposed( simpleTriangleMesh, "simpleTriangleMesh" );
	
	NxCCDSkeleton* s = _physicsSDK->createCCDSkeleton( *simpleTriangleMesh->UnmanagedPointer );
	
	if( s == NULL )
		throw gcnew PhysXException( "Failed to create CCD skeleton" );
	
	CCDSkeleton^ skeleton = gcnew CCDSkeleton( s, this );
	
	_CCDSkeletonCollection->Add( skeleton );
	
	return skeleton;
}
SoftBodyMesh^ Core::CreateSoftBodyMesh( Stream^ stream )
{
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanRead == false )
		throw gcnew ArgumentException( "Cannot read from stream" );
	if( stream->Length == 0 )
		throw gcnew ArgumentException( "Stream is of length 0" );
	
	array<Byte>^ data = gcnew array<Byte>( (int)stream->Length );
	stream->Read( data, 0, (int)stream->Length );
	
	MemoryReaderStream^ reader = gcnew MemoryReaderStream( data );
	
	NxSoftBodyMesh* softBodyMesh = _physicsSDK->createSoftBodyMesh( *reader->UnmanagedPointer );
	if( softBodyMesh == NULL )
		throw gcnew PhysXException( "Failed to create soft body mesh" );
	
	SoftBodyMesh^ s = gcnew SoftBodyMesh( softBodyMesh, this );
	
	_softBodyMeshCollection->Add( s );
	
	return s;
}

float Core::GetParameter( PhysicsParameter parameter )
{
	return _physicsSDK->getParameter( (NxParameter)parameter );
}
void Core::SetParameter( PhysicsParameter parameter, float value )
{
	_physicsSDK->setParameter( (NxParameter)parameter, value );
}
void Core::SetParameter( PhysicsParameter parameter, bool enabled )
{
	_physicsSDK->setParameter( (NxParameter)parameter, enabled ? 1.0f : 0.0f );
}

bool Core::IsCoreCreated::get()
{
	return _isCoreCreated;
}
ReadOnlyList< Scene^ >^ Core::Scenes::get()
{
	return _sceneCollection->ReadOnlyCollection;
}
ReadOnlyList< TriangleMesh^ >^ Core::TriangleMeshes::get()
{
	return _triangleMeshCollection->ReadOnlyCollection;
}
ReadOnlyList< ConvexMesh^ >^ Core::ConvexMeshes::get()
{
	return _convexMeshCollection->ReadOnlyCollection;
}
ReadOnlyList< ClothMesh^ >^ Core::ClothMeshes::get()
{
	return _clothMeshCollection->ReadOnlyCollection;
}
ReadOnlyList< HeightField^ >^ Core::HeightFields::get()
{
	return _heightFieldCollection->ReadOnlyCollection;
}
ReadOnlyList< CCDSkeleton^ >^ Core::CCDSkeletons::get()
{
	return _CCDSkeletonCollection->ReadOnlyCollection;
}
ReadOnlyList< SoftBodyMesh^ >^ Core::SoftBodyMeshes::get()
{
	return _softBodyMeshCollection->ReadOnlyCollection;
}

StillDesign::PhysX::Foundation^ Core::Foundation::get()
{
	return _foundation;
}


int Core::NumberOfPhysicsProcessingUnits::get()
{
	return _physicsSDK->getNbPPUs();
}

StillDesign::PhysX::HardwareVersion Core::HardwareVersion::get()
{
	return (StillDesign::PhysX::HardwareVersion)_physicsSDK->getHWVersion();
}
Version^ Core::InternalVersion::get()
{
	NxU32 apiRev, descRev, branchId;
	
	int v = _physicsSDK->getInternalVersion( apiRev, descRev, branchId );
	
	return gcnew Version( (int)apiRev, (int)descRev, (int)branchId );
}
Version^ Core::SDKVersion::get()
{
	return gcnew Version( NX_SDK_VERSION_MAJOR, NX_SDK_VERSION_MINOR, NX_SDK_VERSION_BUGFIX );
}

bool Core::CheckPhysXRuntimeFiles::get()
{
	return _checkPhysXRuntimeFiles;
}

StillDesign::PhysX::UserOutputStream^ Core::UserOutputStream::get()
{
	return _userOutputStream;
}

PhysicsParametersWrapper^ Core::Parameters::get()
{
	return _physicsParametersWrapper;
}

NxPhysicsSDK* Core::UnmanagedPointer::get()
{
	return _physicsSDK;
}