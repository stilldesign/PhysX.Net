#include "StdAfx.h"

#include "Convex Mesh.h"
#include "Core.h"
#include "Scene.h"
#include "Convex Mesh Description.h"
#include "Memory Reader Stream.h"

using namespace StillDesign::PhysX;

ConvexMesh::ConvexMesh( NxConvexMesh* convexMesh, StillDesign::PhysX::Core^ core )
{
	Debug::Assert( convexMesh != NULL );
	Debug::Assert( core != nullptr );
	
	ObjectTable::Add( (intptr_t)convexMesh, this );
	
	_convexMesh = convexMesh;
	_core = core;
}
ConvexMesh::~ConvexMesh()
{
	this->!ConvexMesh();
}
ConvexMesh::!ConvexMesh()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_core->UnmanagedPointer->releaseConvexMesh( *_convexMesh );
	
	_convexMesh = NULL;
	_core = nullptr;
	
	OnDisposed( this, nullptr );
}
bool ConvexMesh::IsDisposed::get()
{
	return ( _convexMesh == NULL );
}

ConvexMeshDescription^ ConvexMesh::SaveToDescription()
{
	NxConvexMeshDesc* desc = new NxConvexMeshDesc();
		if( _convexMesh->saveToDesc( *desc ) == false )
		{
			delete desc;
			return nullptr;
		}
		
		int trianglesSize = desc->triangleStrideBytes * desc->numTriangles;
		int pointsSize = desc->pointStrideBytes * desc->numVertices;
		
		void* triangles = malloc( trianglesSize );
		void* points = malloc( pointsSize );
		
		memcpy_s( triangles, trianglesSize, desc->triangles, trianglesSize );
		memcpy_s( points, pointsSize, desc->points, pointsSize );
		
		desc->triangles = triangles;
		desc->points = points;
	
	return gcnew ConvexMeshDescription( desc );
}
void ConvexMesh::LoadFromStream( Stream^ stream )
{
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanRead == false )
		throw gcnew ArgumentException( "Cannot read from stream", "stream" );
	if( stream->Length == 0 )
		throw gcnew ArgumentException( "Stream length is 0", "stream" );
	
	_convexMesh->load( *(MemoryReaderStream::FromStream( stream )->UnmanagedPointer) );
}

int ConvexMesh::InternalArrayCount( int submeshIndex, InternalArray interalArray )
{
	return _convexMesh->getCount( submeshIndex, (NxInternalArray)interalArray );
}
InternalFormat ConvexMesh::InternalArrayFormat( int submeshIndex, InternalArray interalArray )
{
	return (InternalFormat)_convexMesh->getFormat( submeshIndex, (NxInternalArray)interalArray );
}

StillDesign::PhysX::Core^ ConvexMesh::Core::get()
{
	return _core;
}

String^ ConvexMesh::Name::get()
{
	return _name;
}
void ConvexMesh::Name::set( String^ value )
{
	_name = value;
}

int ConvexMesh::ReferencedCount::get()
{
	return _convexMesh->getReferenceCount();
}
ConvexMeshMassInformation ConvexMesh::MassInformation::get()
{
	float mass;
	NxMat33 localInertia;
	NxVec3 com;
	
	_convexMesh->getMassInformation( mass, localInertia, com );
	
	ConvexMeshMassInformation info;
		info.Mass = mass;
		info.LocalInertia = Math::Mat33ToMatrix( &localInertia );
		info.LocalCenterOfMass = Math::NxVec3ToVector3( com );
	
	return info;
}

NxConvexMesh* ConvexMesh::UnmanagedPointer::get()
{
	return _convexMesh;
}

//

float ConvexMeshMassInformation::Mass::get()
{
	return _mass;
}
void ConvexMeshMassInformation::Mass::set( float value )
{
	_mass = value;
}

Matrix ConvexMeshMassInformation::LocalInertia::get()
{
	return _localInertia;
}
void ConvexMeshMassInformation::LocalInertia::set( Matrix value )
{
	_localInertia = value;
}

Vector3 ConvexMeshMassInformation::LocalCenterOfMass::get()
{
	return _localCenterOfMass;
}
void ConvexMeshMassInformation::LocalCenterOfMass::set( Vector3 value )
{
	_localCenterOfMass = value;
}