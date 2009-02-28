#include "StdAfx.h"

#include "Functions.h"
#include "Simple Triangle Mesh.h"
#include "Physics Stream.h"

using namespace StillDesign::PhysX;

SimpleTriangleMesh::SimpleTriangleMesh( NxSimpleTriangleMesh* simpleTriangleMesh )
{
	Debug::Assert( simpleTriangleMesh != NULL );
	
	_triMesh = simpleTriangleMesh;
	
	if( simpleTriangleMesh->points != NULL && simpleTriangleMesh->numVertices > 0 && simpleTriangleMesh->pointStrideBytes > 0 )
		_verticesStream = gcnew PhysicsStream( (BYTE*)simpleTriangleMesh->points, simpleTriangleMesh->pointStrideBytes * simpleTriangleMesh->numVertices );
		
	if( simpleTriangleMesh->triangles != NULL && simpleTriangleMesh->numTriangles > 0 && simpleTriangleMesh->triangleStrideBytes > 0 )
		_triangleStream = gcnew PhysicsStream( (BYTE*)simpleTriangleMesh->triangles, simpleTriangleMesh->triangleStrideBytes * simpleTriangleMesh->numTriangles );
}
SimpleTriangleMesh::~SimpleTriangleMesh()
{
	this->!SimpleTriangleMesh();
}
SimpleTriangleMesh::!SimpleTriangleMesh()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	if( _triMesh != NULL )
	{
		const void* buffers[] = 
		{
			_triMesh->points ,
			_triMesh->triangles
		};
		SAFE_FREE_MANY( buffers );
		
		SAFE_DELETE( _triMesh );
	}
	
	_verticesStream = nullptr;
	_triangleStream = nullptr;
	
	OnDisposed( this, nullptr );
}
bool SimpleTriangleMesh::IsDisposed::get()
{
	return ( _triMesh == NULL );
}

bool SimpleTriangleMesh::IsValid()
{
	return _triMesh->isValid();
}
void SimpleTriangleMesh::SetToDefault()
{
	_verticesStream = nullptr;
	_triangleStream = nullptr;
	
	const void* buffers[] = 
	{
		_triMesh->points ,
		_triMesh->triangles
	};
	SAFE_FREE_MANY( buffers );
	
	_triMesh->setToDefault();
}

generic<typename T> PhysicsStream^ SimpleTriangleMesh::AllocateVertices( int numberOfVertices )
{
	return AllocateVertices( sizeof( T ) * numberOfVertices, sizeof( T ) );
}
PhysicsStream^ SimpleTriangleMesh::AllocateVertices( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _verticesStream, _triMesh->points, _triMesh->pointStrideBytes );
}
generic<typename T> PhysicsStream^ SimpleTriangleMesh::AllocateTriangles( int numberOfTriangles )
{
	return AllocateTriangles( sizeof( T ) * numberOfTriangles * 3, sizeof( T ) * 3 );
}
PhysicsStream^ SimpleTriangleMesh::AllocateTriangles( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _triangleStream, _triMesh->triangles, _triMesh->triangleStrideBytes );
}

PhysicsStream^ SimpleTriangleMesh::VerticesStream::get()
{
	return _verticesStream;
}
PhysicsStream^ SimpleTriangleMesh::TriangleStream::get()
{
	return _triangleStream;
}

int SimpleTriangleMesh::VertexCount::get()
{
	return _triMesh->numVertices;
}
void SimpleTriangleMesh::VertexCount::set( int value )
{
	_triMesh->numVertices = value;
}
int SimpleTriangleMesh::TriangleCount::get()
{
	return _triMesh->numTriangles;
}
void SimpleTriangleMesh::TriangleCount::set( int value )
{
	_triMesh->numTriangles = value;
}
int SimpleTriangleMesh::IndexCount::get()
{
	return _triMesh->numTriangles * 3;
}

int SimpleTriangleMesh::VertexStrideSize::get()
{
	return _triMesh->pointStrideBytes;
}

int SimpleTriangleMesh::TriangleStrideSize::get()
{
	return _triMesh->triangleStrideBytes;
}

MeshFlag SimpleTriangleMesh::Flags::get()
{
	return (MeshFlag)_triMesh->flags;
}
void SimpleTriangleMesh::Flags::set( MeshFlag value )
{
	_triMesh->flags = (unsigned int)value;
}

NxSimpleTriangleMesh* SimpleTriangleMesh::UnmanagedPointer::get()
{
	return _triMesh;
}