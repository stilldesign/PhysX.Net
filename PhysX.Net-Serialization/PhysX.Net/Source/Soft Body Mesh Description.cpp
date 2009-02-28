#include "StdAfx.h"

#include "Soft Body Mesh Description.h"
#include "Physics Stream.h"

#include <NxSoftBodyMeshDesc.h> 

using namespace StillDesign::PhysX;

SoftBodyMeshDescription::SoftBodyMeshDescription()
{
	_desc = new NxSoftBodyMeshDesc();
}
SoftBodyMeshDescription::SoftBodyMeshDescription( NxSoftBodyMeshDesc* desc  )
{
	Debug::Assert( desc != NULL );
	
	_desc = desc;
	
	if( desc->numVertices > 0 )
	{
		if( desc->vertices != NULL && desc->vertexStrideBytes > 0 )
			_verticesStream = gcnew PhysicsStream( (BYTE*)desc->vertices, desc->numVertices * desc->vertexStrideBytes );
		
		if( desc->vertexMasses != NULL && desc->vertexMassStrideBytes > 0 )
			_vertexMassesStream = gcnew PhysicsStream( (BYTE*)desc->vertexMasses, desc->numVertices * desc->vertexMassStrideBytes );
		
		if( desc->vertexFlags != NULL && desc->vertexFlagStrideBytes > 0 )
			_vertexFlagsStream = gcnew PhysicsStream( (BYTE*)desc->vertexFlags, desc->numVertices * desc->vertexFlagStrideBytes );
	}
	
	if( desc->numTetrahedra > 0 && desc->tetrahedronStrideBytes > 0 )
	{
		if( desc->tetrahedra != NULL )
			_tetrahedraStream = gcnew PhysicsStream( (BYTE*)desc->tetrahedra, desc->numTetrahedra * desc->tetrahedronStrideBytes );
	}
}
SoftBodyMeshDescription::~SoftBodyMeshDescription()
{
	this->!SoftBodyMeshDescription();
}
SoftBodyMeshDescription::!SoftBodyMeshDescription()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	if( _desc != NULL )
	{
		const void* buffers[] = 
		{
			_desc->vertices,
			_desc->tetrahedra,
			_desc->vertexMasses,
			_desc->vertexFlags
		};
		SAFE_FREE_MANY( buffers );
		
		SAFE_DELETE( _desc );
	}
	
	_verticesStream = nullptr;
	_tetrahedraStream = nullptr;
	_vertexMassesStream = nullptr;
	_vertexFlagsStream = nullptr;
	
	OnDisposed( this, nullptr );
}
bool SoftBodyMeshDescription::IsDisposed::get()
{
	return ( _desc == NULL );
}

void SoftBodyMeshDescription::SetToDefault()
{
	_desc->setToDefault();
	
	_verticesStream = nullptr;
	_tetrahedraStream = nullptr;
	_vertexMassesStream = nullptr;
	_vertexFlagsStream = nullptr;
}
bool SoftBodyMeshDescription::IsValid()
{
	return _desc->isValid();
}

generic<typename T> PhysicsStream^ SoftBodyMeshDescription::AllocateVertices( int numberOfVertices )
{
	return AllocateVertices( sizeof( T ) * numberOfVertices, sizeof( T ) );
}
PhysicsStream^ SoftBodyMeshDescription::AllocateVertices( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _verticesStream, _desc->vertices, _desc->vertexStrideBytes );
}
generic<typename T> PhysicsStream^ SoftBodyMeshDescription::AllocateTetrahedra( int numberOfTetrahedra )
{
	return AllocateTetrahedra( sizeof( T ) * 4 * numberOfTetrahedra, sizeof( T ) * 4 );
}
PhysicsStream^ SoftBodyMeshDescription::AllocateTetrahedra( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _tetrahedraStream, _desc->tetrahedra, _desc->tetrahedronStrideBytes );
}
generic<typename T> PhysicsStream^ SoftBodyMeshDescription::AllocateVertexMasses( int numberOfVertices )
{
	return AllocateVertexMasses( sizeof( T ) * numberOfVertices, sizeof( T ) );
}
PhysicsStream^ SoftBodyMeshDescription::AllocateVertexMasses( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _vertexMassesStream, _desc->vertexMasses, _desc->vertexMassStrideBytes );
}
generic<typename T> PhysicsStream^ SoftBodyMeshDescription::AllocateVertexFlags( int numberOfVertices )
{
	return AllocateVertexFlags( sizeof( T ) * numberOfVertices, sizeof( T ) );
}
PhysicsStream^ SoftBodyMeshDescription::AllocateVertexFlags( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _vertexFlagsStream, _desc->vertexFlags, _desc->vertexFlagStrideBytes );
}

int SoftBodyMeshDescription::VertexCount::get()
{
	return _desc->numVertices;
}
void SoftBodyMeshDescription::VertexCount::set( int value )
{
	_desc->numVertices = value;
}
int SoftBodyMeshDescription::TetrahedraCount::get()
{
	return _desc->numTetrahedra;
}
void SoftBodyMeshDescription::TetrahedraCount::set( int value )
{
	_desc->numTetrahedra = value;
}

int SoftBodyMeshDescription::VertexStrideBytes::get()
{
	return _desc->vertexStrideBytes;
}
int SoftBodyMeshDescription::TetrahedraStrideBytes::get()
{
	return _desc->tetrahedronStrideBytes;
}
SoftBodyMeshFlag SoftBodyMeshDescription::Flags::get()
{
	return (SoftBodyMeshFlag)_desc->flags;
}
void SoftBodyMeshDescription::Flags::set( SoftBodyMeshFlag value )
{
	_desc->flags = (NxSoftBodyMeshFlags)value;
}
int SoftBodyMeshDescription::VertexMassStrideBytes::get()
{
	return _desc->vertexMassStrideBytes;
}
int SoftBodyMeshDescription::VertexFlagStrideBytes::get()
{
	return _desc->vertexFlagStrideBytes;
}

PhysicsStream^ SoftBodyMeshDescription::VertexStream::get()
{
	return _verticesStream;
}
PhysicsStream^ SoftBodyMeshDescription::TetrahedraStream::get()
{
	return _tetrahedraStream;
}
PhysicsStream^ SoftBodyMeshDescription::VertexMassesStream::get()
{
	return _vertexMassesStream;
}
PhysicsStream^ SoftBodyMeshDescription::VertexFlagsStream::get()
{
	return _vertexFlagsStream;
}

NxSoftBodyMeshDesc* SoftBodyMeshDescription::UnmanagedPointer::get()
{
	return _desc;
}