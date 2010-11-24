#include "StdAfx.h"

#include "Cloth Mesh Description.h"
#include "Physics Stream.h"

#include <NxClothMeshDesc.h> 

using namespace StillDesign::PhysX;

ClothMeshDescription::ClothMeshDescription() : SimpleTriangleMesh( new NxClothMeshDesc() )
{
	
}
ClothMeshDescription::ClothMeshDescription( NxClothMeshDesc* clothMeshDescription ) : SimpleTriangleMesh( clothMeshDescription )
{
	if( clothMeshDescription->vertexMasses != NULL && clothMeshDescription->numVertices > 0 && clothMeshDescription->vertexMassStrideBytes > 0 )
		_vertexMasses = gcnew PhysicsStream( (BYTE*)clothMeshDescription->vertexMasses, clothMeshDescription->vertexMassStrideBytes * clothMeshDescription->numVertices );
	
	if( clothMeshDescription->vertexFlags != NULL && clothMeshDescription->numVertices > 0 && clothMeshDescription->vertexFlagStrideBytes > 0 )
		_vertexFlags = gcnew PhysicsStream( (BYTE*)clothMeshDescription->vertexFlags, clothMeshDescription->vertexFlagStrideBytes * clothMeshDescription->numVertices );
}
ClothMeshDescription::~ClothMeshDescription()
{
	this->!ClothMeshDescription();
}
ClothMeshDescription::!ClothMeshDescription()
{
	if( this->IsDisposed )
		return;
	
	const void* buffers[] = 
	{
		this->UnmanagedPointer->vertexMasses,
		this->UnmanagedPointer->vertexFlags
	};
	SAFE_FREE_MANY( buffers );
	
	_vertexMasses = nullptr;
	_vertexFlags = nullptr;
}

void ClothMeshDescription::SetToDefault()
{
	const void* vertexMasses = this->UnmanagedPointer->vertexMasses;
	const void* vertexFlags = this->UnmanagedPointer->vertexFlags;
	
	SimpleTriangleMesh::SetToDefault();
	
	this->UnmanagedPointer->setToDefault();
	
	_vertexMasses = nullptr;
	_vertexFlags = nullptr;
	
	const void* buffers[] =
	{
		vertexMasses,
		vertexFlags
	};
	SAFE_FREE_MANY( buffers );
}
bool ClothMeshDescription::IsValid()
{
	return this->UnmanagedPointer->isValid();
}

generic<typename T> PhysicsStream^ ClothMeshDescription::AllocateVertexMasses( int numberOfVertices )
{
	return AllocateVertexMasses( sizeof( T ) * numberOfVertices, sizeof( T ) );
}
PhysicsStream^ ClothMeshDescription::AllocateVertexMasses( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _vertexMasses, this->UnmanagedPointer->vertexMasses, this->UnmanagedPointer->vertexMassStrideBytes );
}
generic<typename T> PhysicsStream^ ClothMeshDescription::AllocateVertexFlags( int numberOfVertices )
{
	return AllocateVertexFlags( sizeof( T ) * numberOfVertices, sizeof( T ) );
}
PhysicsStream^ ClothMeshDescription::AllocateVertexFlags( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _vertexFlags, this->UnmanagedPointer->vertexFlags, this->UnmanagedPointer->vertexFlagStrideBytes );
}

String^ ClothMeshDescription::Name::get()
{
	return _name;
}
void ClothMeshDescription::Name::set( String^ value )
{
	_name = value;
}

PhysicsStream^ ClothMeshDescription::VertexMassesStream::get()
{
	return _vertexMasses;
}
PhysicsStream^ ClothMeshDescription::VertexFlagsStream::get()
{
	return _vertexFlags;
}

float ClothMeshDescription::WeldingDistance::get()
{
	return this->UnmanagedPointer->weldingDistance;
}
void ClothMeshDescription::WeldingDistance::set( float value )
{
	this->UnmanagedPointer->weldingDistance = value;
}

int ClothMeshDescription::NumberOfHierarchyLevels::get()
{
	return this->UnmanagedPointer->numHierarchyLevels;
}
void ClothMeshDescription::NumberOfHierarchyLevels::set( int value )
{
	this->UnmanagedPointer->numHierarchyLevels = value;
}

NxClothMeshDesc* ClothMeshDescription::UnmanagedPointer::get()
{
	return (NxClothMeshDesc*)SimpleTriangleMesh::UnmanagedPointer;
}