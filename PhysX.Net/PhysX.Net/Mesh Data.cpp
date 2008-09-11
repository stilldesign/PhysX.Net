#include "StdAfx.h"

#include "Mesh Data.h"
#include "Functions.h"
#include "Physics Stream.h"

#include <NxMeshData.h>

using namespace System;
using namespace StillDesign::PhysX;

MeshData::MeshData()
{
	CreateMeshData();
}
//MeshData::MeshData( int vertexCount, int triangleCount, int parentIndicesCount, int positionStrideSize, int normalsStrideSize, int parentIndicesStrideSize, int indexStrideSize )
//{
//	if( vertexCount <= 0 )
//		throw gcnew ArgumentException( "Vertex count must be greater than 0", "vertexCount" );
//	if( triangleCount <= 0 )
//		throw gcnew ArgumentException( "'Triangle count must be greater than 0", "triangleCount" );
//	
//	CreateMeshData();
//	
//	int indexCount = triangleCount * 3;
//	
//	// Positions
//	if( positionStrideSize > 0 )
//		AllocatePositions( vertexCount * positionStrideSize, positionStrideSize );
//	
//	// Normals
//	if( normalsStrideSize > 0 )
//		AllocateNormals( vertexCount * normalsStrideSize, normalsStrideSize );
//	
//	// Parent Indices
//	if( parentIndicesStrideSize > 0 && parentIndicesCount > 0 )
//		AllocateParentIndices( vertexCount * parentIndicesStrideSize, parentIndicesStrideSize );
//	
//	// Indices
//	if( indexStrideSize > 0 )
//		AllocateIndices( indexCount * indexStrideSize, indexStrideSize );
//	
//	//
//	
//	_meshData->maxVertices = vertexCount;
//	_meshData->maxIndices = indexCount;
//	_meshData->maxParentIndices = parentIndicesCount;
//}
MeshData::MeshData( NxMeshData* meshData )
{
	CreateMeshData( meshData );
}
MeshData::MeshData( NxMeshData meshData )
{
	NxMeshData* data = new NxMeshData();
	*data = meshData;
	
	CreateMeshData( data );
}
MeshData::~MeshData()
{
	this->!MeshData();
}
MeshData::!MeshData()
{
	if( this->IsDisposed == true )
		return;
	
	onDisposing( this, nullptr );
	
	if( _meshData != NULL )
	{
		void* buffers[] = 
		{
			_meshData->verticesPosBegin,
			_meshData->verticesNormalBegin,
			_meshData->parentIndicesBegin,
			_meshData->indicesBegin,
			_meshData->numVerticesPtr,
			_meshData->numParentIndicesPtr,
			_meshData->numIndicesPtr
		};
		
		int count = sizeof( buffers ) / sizeof( void* );
		for( int x = 0; x < count; x++ )
		{
			if( buffers[ x ] != NULL )
				free( buffers[ x ] );
		}
		
		SAFE_DELETE( _meshData->numVerticesPtr );
		SAFE_DELETE( _meshData->numIndicesPtr );
		
		SAFE_DELETE( _meshData );
	}
	
	onDisposed( this, nullptr );
}

void MeshData::CreateMeshData()
{
	_meshData = new NxMeshData();
	
	_meshData->numVerticesPtr = new NxU32();
	_meshData->numIndicesPtr = new NxU32();
	
	(*_meshData->numVerticesPtr) = 0;
	(*_meshData->numIndicesPtr) = 0;
}
void MeshData::CreateMeshData( NxMeshData* meshData )
{
	Debug::Assert( meshData != NULL );
	
	_meshData = meshData;
	
	int maxVertices = meshData->maxVertices;
	int maxIndices = meshData->maxIndices;
	int maxParentIndices = meshData->maxParentIndices;
	
	int positionStrideSize = meshData->verticesPosByteStride;
	int normalsStrideSize = meshData->verticesNormalByteStride;
	int parentIndicesStrideSize = meshData->parentIndicesByteStride;
	
	int indexStrideSize = meshData->indicesByteStride;
	
	if( meshData->verticesPosBegin != NULL && maxVertices > 0 )
		_positionsStream = gcnew PhysicsStream( (BYTE*)meshData->verticesPosBegin, maxVertices * positionStrideSize );
		
	if( meshData->verticesNormalBegin != NULL && maxVertices > 0 )
		_normalsStream = gcnew PhysicsStream( (BYTE*)meshData->verticesNormalBegin, maxVertices * normalsStrideSize );
		
	if( meshData->parentIndicesBegin != NULL && maxParentIndices > 0 )
		_parentIndicesStream = gcnew PhysicsStream( (BYTE*)meshData->parentIndicesBegin, maxParentIndices * parentIndicesStrideSize );
		
	if( meshData->dirtyBufferFlagsPtr != NULL && maxVertices > 0 )
		_dirtyBufferFlagsStream = gcnew PhysicsStream( (BYTE*)meshData->dirtyBufferFlagsPtr, maxVertices * sizeof( NxU32 ) );
		
	if( meshData->indicesBegin != NULL && maxIndices > 0 )
		_indicesStream = gcnew PhysicsStream( (BYTE*)meshData->indicesBegin, maxIndices * indexStrideSize );
}
bool MeshData::IsDisposed::get()
{
	return ( _meshData == NULL );
}

NxMeshData* MeshData::Clone( NxMeshData meshData )
{
	Debug::Assert( meshData.numIndicesPtr != NULL );
	Debug::Assert( meshData.numParentIndicesPtr != NULL );
	Debug::Assert( meshData.numVerticesPtr != NULL );
	
	NxMeshData* d = new NxMeshData();
	if( d == NULL )
		throw gcnew PhysXException( "Could not allocate Mesh Data" );
	
	int maxVertices = meshData.maxVertices;
	int maxIndices = meshData.maxIndices;
	int maxParentIndices = meshData.maxParentIndices;
	
	int positionStrideSize = meshData.verticesPosByteStride;
	int normalsStrideSize = meshData.verticesNormalByteStride;
	int parentIndicesStrideSize = meshData.parentIndicesByteStride;
	
	//
	
	d->numIndicesPtr = new NxU32();
	d->numParentIndicesPtr = new NxU32();
	d->numVerticesPtr = new NxU32();
	
	if( meshData.dirtyBufferFlagsPtr != NULL )
		d->dirtyBufferFlagsPtr = (NxU32*)malloc( maxVertices * sizeof( NxU32 ) );
	
	if( meshData.indicesBegin != NULL )
		d->indicesBegin = malloc( maxIndices * meshData.indicesByteStride );
	
	if( meshData.parentIndicesBegin != NULL )
		d->parentIndicesBegin = malloc( maxParentIndices * parentIndicesStrideSize );
	
	if( meshData.verticesNormalBegin != NULL )
		d->verticesNormalBegin = malloc( maxVertices * normalsStrideSize );
	
	if( meshData.verticesPosBegin != NULL )
		d->verticesPosBegin = malloc( maxVertices * positionStrideSize );
	
	//
	
	*d->numIndicesPtr = *meshData.numIndicesPtr;
	*d->numParentIndicesPtr = *meshData.numParentIndicesPtr;
	*d->numVerticesPtr = *meshData.numVerticesPtr;
	
	if( meshData.dirtyBufferFlagsPtr != NULL )
		memcpy_s( d->dirtyBufferFlagsPtr, maxVertices * sizeof( NxU32 ), meshData.dirtyBufferFlagsPtr, maxVertices * sizeof( NxU32 ) );
	
	if( meshData.indicesBegin != NULL )
		memcpy_s( d->indicesBegin, maxIndices * meshData.indicesByteStride, meshData.indicesBegin, maxIndices * meshData.indicesByteStride );
	
	if( meshData.parentIndicesBegin != NULL )
		memcpy_s( d->parentIndicesBegin, maxParentIndices * parentIndicesStrideSize, meshData.parentIndicesBegin, maxParentIndices *parentIndicesStrideSize );
	
	if( meshData.verticesNormalBegin != NULL )
		memcpy_s( d->verticesNormalBegin, maxVertices * normalsStrideSize, meshData.verticesNormalBegin, maxVertices * normalsStrideSize );
	
	if( meshData.verticesPosBegin != NULL )
		memcpy_s( d->verticesPosBegin, maxVertices * positionStrideSize, meshData.verticesPosBegin, maxVertices * positionStrideSize );
	
	return d;
}

Object^ MeshData::Clone()
{
	NxMeshData* data = Clone( *_meshData );
	
	return gcnew MeshData( data );
}

bool MeshData::IsValid()
{
	return _meshData->isValid();
}
void MeshData::SetToDefault()
{
	const void* buffers[] = 
	{
		_meshData->dirtyBufferFlagsPtr,
		_meshData->indicesBegin,
		_meshData->parentIndicesBegin,
		_meshData->verticesNormalBegin,
		_meshData->verticesPosBegin
	};
	
	SAFE_FREE_MANY( buffers );
	
	SAFE_DELETE( _meshData->numIndicesPtr );
	SAFE_DELETE( _meshData->numParentIndicesPtr );
	SAFE_DELETE( _meshData->numVerticesPtr );
	
	_meshData->setToDefault();
}

generic<typename T> PhysicsStream^ MeshData::AllocatePositions( int numberOfPositions )
{
	return AllocatePositions( sizeof( T ) * numberOfPositions, sizeof( T ) );
}
PhysicsStream^ MeshData::AllocatePositions( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _positionsStream, _meshData->verticesPosBegin, _meshData->verticesPosByteStride );
}
generic<typename T> where T : ValueType PhysicsStream^ MeshData::AllocateNormals( int numberOfNormals )
{
	return AllocateNormals( sizeof( T ) * numberOfNormals, sizeof( T ) );
}
PhysicsStream^ MeshData::AllocateNormals( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _normalsStream, _meshData->verticesNormalBegin, _meshData->verticesNormalByteStride );
}
generic<typename T> PhysicsStream^ MeshData::AllocateParentIndices( int numberOfParentIndices )
{
	return AllocateParentIndices( sizeof( T ) * numberOfParentIndices, sizeof( T ) );
}
PhysicsStream^ MeshData::AllocateParentIndices( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _parentIndicesStream, _meshData->parentIndicesBegin, _meshData->parentIndicesByteStride );
}
generic<typename T> PhysicsStream^ MeshData::AllocateIndices( int numberOfIndices )
{
	return AllocateIndices( sizeof( T ) * numberOfIndices, sizeof( T ) );
}
PhysicsStream^ MeshData::AllocateIndices( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _indicesStream, _meshData->indicesBegin, _meshData->indicesByteStride );
}
PhysicsStream^ MeshData::AllocateDirtyBufferFlags( int numberOfDirtyBufferFlags )
{
	int size = sizeof( NxU32 ) * numberOfDirtyBufferFlags;
	int strideSize = sizeof( NxU32 );
	
	StdPhysicsStreamAlloc2( _dirtyBufferFlagsStream, _meshData->dirtyBufferFlagsPtr, strideSize, NxU32* );
}

MeshData^ MeshData::AllocateCommonMeshData( int numberOfPositions, int numberOfTriangles, Type types )
{
	MeshData^ data = gcnew MeshData();
		if( (unsigned int)(types & Type::Positions) != 0 )
			data->AllocatePositions<Vector3>( numberOfPositions );
		if( (unsigned int)(types & Type::Normals) != 0 )
			data->AllocateNormals<Vector3>( numberOfPositions );
		if( (unsigned int)(types & Type::ParticleIndices) != 0 )
			data->AllocateParentIndices<int>( numberOfPositions );
		if( (unsigned int)(types & Type::DirtyFlags) != 0 )
			data->AllocateDirtyBufferFlags( numberOfPositions );
		if( (unsigned int)(types & Type::Indices) != 0 )
			data->AllocateIndices<int>( numberOfTriangles * 3 );
	
	return data;
}

//

String^ MeshData::Name::get()
{
	return Functions::UnmanagedToManagedString( _meshData->name );
}
void MeshData::Name::set( String^ value )
{
	_meshData->name = Functions::ManagedToUnmanagedString( value );
}

PhysicsStream^ MeshData::PositionsStream::get()
{
	return _positionsStream;
}
PhysicsStream^ MeshData::NormalsStream::get()
{
	return _normalsStream;
}
PhysicsStream^ MeshData::ParentIndicesStream::get()
{
	return _parentIndicesStream;
}
PhysicsStream^ MeshData::IndicesStream::get()
{
	return _indicesStream;
}
PhysicsStream^ MeshData::DirtyBufferFlagsStream::get()
{
	return _dirtyBufferFlagsStream;
}

int MeshData::MaximumVertices::get()
{
	return _meshData->maxVertices;
}
void MeshData::MaximumVertices::set( int value )
{
	_meshData->maxVertices = value;
}
int MeshData::MaximumIndices::get()
{
	return _meshData->maxIndices;
}
void MeshData::MaximumIndices::set( int value )
{
	_meshData->maxIndices = value;
}
int MeshData::MaximumParentIndices::get()
{
	return _meshData->maxParentIndices;
}
void MeshData::MaximumParentIndices::set( int value )
{
	_meshData->maxParentIndices = value;
}

int MeshData::NumberOfVertices::get()
{
	if( _meshData->numVerticesPtr == NULL )
		throw gcnew InvalidOperationException( "NumberOfVertices is unallocated" );
	
	return *_meshData->numVerticesPtr;
}
int MeshData::NumberOfIndices::get()
{
	if( _meshData->numIndicesPtr == NULL )
		throw gcnew InvalidOperationException( "NumberOfIndices is unallocated" );
	
	return *_meshData->numIndicesPtr;
}
int MeshData::NumberOfParentIndices::get()
{
	if( _meshData->numParentIndicesPtr == NULL )
		throw gcnew InvalidOperationException( "NumberOfParentIndices is unallocated" );
	
	return *_meshData->numParentIndicesPtr;
}

int MeshData::PositionStrideSize::get()
{
	return _meshData->verticesPosByteStride;
}
int MeshData::IndexStrideSize::get()
{
	return _meshData->indicesByteStride;
}
int MeshData::NormalStrideSize::get()
{
	return _meshData->verticesNormalByteStride;
}
int MeshData::ParentIndicesStrideSize::get()
{
	return _meshData->parentIndicesByteStride;
}

MeshDataFlag MeshData::Flags::get()
{
	return (MeshDataFlag)_meshData->flags;
}
void MeshData::Flags::set( MeshDataFlag value )
{
	_meshData->flags = (unsigned int)value;
}

NxMeshData* MeshData::UnmanagedPointer::get()
{
	return _meshData;
}