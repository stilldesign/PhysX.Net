#include "StdAfx.h"

#include "Triangle Mesh.h"
#include "Scene.h"
#include "Core.h"
#include "Triangle Mesh Description.h"
#include "Memory Reader Stream.h"

#include <NxTriangleMesh.h> 

using namespace StillDesign::PhysX;

TriangleMesh::TriangleMesh( NxTriangleMesh* triangleMesh, StillDesign::PhysX::Core^ core )
{
	Debug::Assert( triangleMesh != NULL );
	Debug::Assert( core != nullptr );
	
	ObjectCache::Add( (intptr_t)triangleMesh, this );
	
	_triangleMesh = triangleMesh;
	
	_core = core;
}
TriangleMesh::~TriangleMesh()
{
	this->!TriangleMesh();
}
TriangleMesh::!TriangleMesh()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_core->UnmanagedPointer->releaseTriangleMesh( *_triangleMesh );
	
	_triangleMesh = NULL;
	_core = nullptr;
	
	OnDisposed( this, nullptr );
}
bool TriangleMesh::IsDisposed::get()
{
	return ( _triangleMesh == NULL );
}

TriangleMeshDescription^ TriangleMesh::SaveToDescription()
{
	NxTriangleMeshDesc* desc = new NxTriangleMeshDesc();
		if( _triangleMesh->saveToDesc( *desc ) == false )
		{
			delete desc;
			return nullptr;
		}
		
		int trianglesSize = desc->triangleStrideBytes * desc->numTriangles;
		int pointsSize = desc->pointStrideBytes * desc->numVertices;
		
		void* t = malloc( trianglesSize );
		void* v = malloc( pointsSize );
		
		desc->triangles = memcpy( t, desc->triangles, trianglesSize );
		desc->points = memcpy( v, desc->points, pointsSize );
	
	return gcnew TriangleMeshDescription( desc );
}

unsigned int TriangleMesh::ElementCount( unsigned int submeshIndex, InternalArray internalArray )
{
	return _triangleMesh->getCount( submeshIndex, (NxInternalArray)internalArray );
}
InternalFormat TriangleMesh::ElementFormat( unsigned int submeshIndex, InternalArray internalArray )
{
	return (InternalFormat)_triangleMesh->getFormat( submeshIndex, (NxInternalArray)internalArray );
}

unsigned int TriangleMesh::StrideSize( unsigned int submeshIndex, InternalArray internalArray )
{
	return _triangleMesh->getStride( submeshIndex, (NxInternalArray)internalArray );
}

unsigned int TriangleMesh::PageCount()
{
	return _triangleMesh->getPageCount();
}
Bounds3 TriangleMesh::PageBoundingBox( unsigned int pageIndex )
{
	NxBounds3 bounds = _triangleMesh->getPageBBox( pageIndex );
	
	return (Bounds3)bounds;
}

bool TriangleMesh::LoadFromStream( Stream^ stream )
{
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanRead == false )
		throw gcnew ArgumentException( "Cannot read from stream", "stream" );
	
	return _triangleMesh->load( *(MemoryReaderStream::FromStream( stream )->UnmanagedPointer) );
}

unsigned short TriangleMesh::GetTriangleMaterialIndex( unsigned int triangleID )
{
	return _triangleMesh->getTriangleMaterial( triangleID );
}

String^ TriangleMesh::Name::get()
{
	return _name;
}
void TriangleMesh::Name::set( String^ value )
{
	_name = value;
}

StillDesign::PhysX::Core^ TriangleMesh::Core::get()
{
	return _core;
}

int TriangleMesh::ReferencedCount::get()
{
	return _triangleMesh->getReferenceCount();
}

NxTriangleMesh* TriangleMesh::UnmanagedPointer::get()
{
	return _triangleMesh;
}