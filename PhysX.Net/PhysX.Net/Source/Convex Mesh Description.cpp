#include "StdAfx.h"

#include "Convex Mesh Description.h"
#include "Convex Mesh.h"
#include "Scene.h"
#include "Physics Stream.h"

using namespace StillDesign::PhysX;

ConvexMeshDescription::ConvexMeshDescription()
{
	_desc = new NxConvexMeshDesc();
}
ConvexMeshDescription::ConvexMeshDescription( NxConvexMeshDesc* convexMeshDescription )
{
	Debug::Assert( convexMeshDescription != NULL );
	
	_desc = convexMeshDescription;
	
	if( convexMeshDescription->points != NULL && convexMeshDescription->pointStrideBytes > 0 && convexMeshDescription->numVertices > 0 )
		_pointsStream = gcnew PhysicsStream( (BYTE*)convexMeshDescription->points, convexMeshDescription->numVertices * convexMeshDescription->pointStrideBytes );
	
	if( convexMeshDescription->triangles != NULL && convexMeshDescription->triangleStrideBytes > 0 && convexMeshDescription->numTriangles > 0 )
		_trianglesStream = gcnew PhysicsStream( (BYTE*)convexMeshDescription->triangles, convexMeshDescription->numTriangles * convexMeshDescription->triangleStrideBytes );
}
ConvexMeshDescription::~ConvexMeshDescription()
{
	this->!ConvexMeshDescription();
}
ConvexMeshDescription::!ConvexMeshDescription()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	if( _desc != NULL )
	{
		const void* buffers[] = 
		{
			_desc->points,
			_desc->triangles
		};
		
		SAFE_FREE_MANY( buffers );
		
		SAFE_DELETE( _desc );
	}
	
	OnDisposed( this, nullptr );
}
bool ConvexMeshDescription::IsDisposed::get()
{
	return ( _desc == NULL );
}

bool ConvexMeshDescription::IsValid()
{
	return _desc->isValid();
}
int ConvexMeshDescription::CheckValid()
{
	return _desc->checkValid();
}
void ConvexMeshDescription::SetToDefault()
{
	_desc->setToDefault();
	
	const void* buffers[] = 
	{
		_desc->points,
		_desc->triangles
	};
	
	SAFE_FREE_MANY( buffers );
	
	_pointsStream = nullptr;
	_trianglesStream = nullptr;
}

PhysicsStream^ ConvexMeshDescription::AllocatePoints( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _pointsStream, _desc->points, _desc->pointStrideBytes );
}
generic<typename T> PhysicsStream^ ConvexMeshDescription::AllocatePoints( int numberOfPoints )
{
	return AllocatePoints( sizeof( T ) * numberOfPoints, sizeof( T ) );
}

PhysicsStream^ ConvexMeshDescription::AllocateTriangles( int size, int strideSize )
{
	StdPhysicsStreamAlloc( _trianglesStream, _desc->triangles, _desc->triangleStrideBytes );
}
generic<typename T> PhysicsStream^ ConvexMeshDescription::AllocateTriangles( int numberOfTriangles )
{
	return AllocateTriangles( sizeof( T ) * 3 * numberOfTriangles, sizeof( T ) * 3 );
}

//

int ConvexMeshDescription::PointCount::get()
{
	return _desc->numVertices;
}
void ConvexMeshDescription::PointCount::set( int value )
{
	_desc->numVertices = value;
}

int ConvexMeshDescription::TriangleCount::get()
{
	return _desc->numTriangles;
}
void ConvexMeshDescription::TriangleCount::set( int value )
{
	_desc->numTriangles = value;
}

int ConvexMeshDescription::PointStrideSize::get()
{
	return _desc->pointStrideBytes;
}

int ConvexMeshDescription::TriangleStrideSize::get()
{
	return _desc->triangleStrideBytes;
}

PhysicsStream^ ConvexMeshDescription::PointsStream::get()
{
	return _pointsStream;
}
PhysicsStream^ ConvexMeshDescription::TriangleStream::get()
{
	return _trianglesStream;
}

ConvexFlag ConvexMeshDescription::Flags::get()
{
	return (ConvexFlag)_desc->flags;
}
void ConvexMeshDescription::Flags::set( ConvexFlag value )
{
	_desc->flags = (unsigned int)value;
}

NxConvexMeshDesc* ConvexMeshDescription::UnmanagedPointer::get()
{
	return _desc;
}