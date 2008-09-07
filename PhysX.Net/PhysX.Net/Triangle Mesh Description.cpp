#include "StdAfx.h"

#include "Triangle Mesh Description.h"
#include "Physics Stream.h"

using namespace StillDesign::PhysX;

TriangleMeshDescription::TriangleMeshDescription( NxTriangleMeshDesc* triangleMeshDesc ) : SimpleTriangleMesh( triangleMeshDesc )
{
	if( triangleMeshDesc->materialIndices != NULL && triangleMeshDesc->materialIndexStride > 0 && triangleMeshDesc->numVertices > 0 )
		_materialIndicesStream = gcnew PhysicsStream( (BYTE*)triangleMeshDesc->materialIndices, triangleMeshDesc->materialIndexStride * triangleMeshDesc->numVertices );
}
TriangleMeshDescription::TriangleMeshDescription() : SimpleTriangleMesh( new NxTriangleMeshDesc() )
{
	
}
generic< class T, class V >
TriangleMeshDescription^ TriangleMeshDescription::Create( array<T>^ triangleIndices, array<V>^ vertices )
{
	if( triangleIndices != nullptr && triangleIndices->Length == 0 )
		throw gcnew ArgumentException( "Triangle indices length cannot be 0" );
	if( vertices != nullptr && vertices->Length == 0 )
		throw gcnew ArgumentException( "Vertices length cannot be 0" );
	
	TriangleMeshDescription^ desc = gcnew TriangleMeshDescription();
	
	if( triangleIndices != nullptr )
	{
		// T (triangle index type) must be either 32 or 16 bit
		if( sizeof( T ) != sizeof( int ) || sizeof( T ) != sizeof( short ) )
			throw gcnew ArgumentException( "Invalid generic parameter T. Size must be either 32 or 16 bit" );
		
		desc->TriangleCount = triangleIndices->Length / 3;
		
		desc->AllocateTriangles<T>( desc->TriangleCount );
		
		desc->TriangleStream->SetData( triangleIndices );
		
		if( sizeof( T ) == sizeof( int ) )
			desc->Flags &= ~MeshFlag::Indices16Bit;
		else
			desc->Flags |= MeshFlag::Indices16Bit;
	}
	
	if( vertices != nullptr )
	{
		desc->VertexCount = vertices->Length;
		
		desc->AllocateVertices<V>( desc->VertexCount );
		
		desc->VerticesStream->SetData( vertices );
	}
	
	return desc;
}

bool TriangleMeshDescription::IsValid()
{
	return this->UnmanagedPointer->isValid();
}
void TriangleMeshDescription::SetToDefault()
{
	const void* buffers[] =
	{
		this->UnmanagedPointer->materialIndices
	};
	
	SAFE_FREE_MANY( buffers );
	
	SimpleTriangleMesh::SetToDefault();
	
	_materialIndicesStream = nullptr;
}

generic<class T>
PhysicsStream^ TriangleMeshDescription::AllocateMaterialIndices( int numberOfMaterialIndices )
{
	return AllocateMaterialIndices( sizeof( T ) * numberOfMaterialIndices, sizeof( T ) );
}
PhysicsStream^ TriangleMeshDescription::AllocateMaterialIndices( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _materialIndicesStream, this->UnmanagedPointer->materialIndices, this->UnmanagedPointer->materialIndexStride );
}

PhysicsStream^ TriangleMeshDescription::MaterialIndicesStream::get()
{
	return _materialIndicesStream;
}

Axis TriangleMeshDescription::HeightFieldVerticalAxis::get()
{
	return (Axis)this->UnmanagedPointer->heightFieldVerticalAxis;
}
void TriangleMeshDescription::HeightFieldVerticalAxis::set( Axis value )
{
	this->UnmanagedPointer->heightFieldVerticalAxis = (NxHeightFieldAxis)value;
}

float TriangleMeshDescription::HeightFieldVerticalExtent::get()
{
	return this->UnmanagedPointer->heightFieldVerticalExtent;
}
void TriangleMeshDescription::HeightFieldVerticalExtent::set( float value )
{
	this->UnmanagedPointer->heightFieldVerticalExtent = value;
}

float TriangleMeshDescription::ConvexEdgeThreshold::get()
{
	return this->UnmanagedPointer->convexEdgeThreshold;
}
void TriangleMeshDescription::ConvexEdgeThreshold::set( float value )
{
	this->UnmanagedPointer->convexEdgeThreshold = value;
}

NxTriangleMeshDesc* TriangleMeshDescription::UnmanagedPointer::get()
{
	return (NxTriangleMeshDesc*)SimpleTriangleMesh::UnmanagedPointer;
}