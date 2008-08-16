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
	
	onDisposing( this, nullptr );
	
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
	
	onDisposed( this, nullptr );
}
bool ConvexMeshDescription::IsDisposed::get()
{
	return ( _desc == NULL );
}

DescriptorValidity^ ConvexMeshDescription::IsValid()
{
	// Check geometry
	if(_desc->numVertices < 3 ) //at least 1 trig's worth of points
		return DescriptorValidity::Invalid( "Must have at least 1 triangle" );
	
	if( (_desc->numVertices > 0xffff && _desc->flags & NX_CF_16_BIT_INDICES) )
		return DescriptorValidity::Invalid( "Number of vertices must be less than or equal to ushort.MaxValue because 16 bit indices flag is raised" );
	
	if(!_desc->points)
		return DescriptorValidity::Invalid( "Points not set" );
	
	if(_desc->pointStrideBytes < sizeof(NxPoint))	//should be at least one point's worth of data
		return DescriptorValidity::Invalid( "Point stride size is less than the size of a vector3" );

	// Check topology
	// The triangles pointer is not mandatory: the vertex cloud is enough to define the convex hull.
	if(_desc->triangles)
		{
		// Indexed mesh
		if(_desc->numTriangles < 2)	//some algos require at least 2 trigs
			return DescriptorValidity::Invalid( "Must have at least 2 triangles" );
		
		if(_desc->flags & NX_CF_16_BIT_INDICES)
			{
			if((_desc->triangleStrideBytes < sizeof(NxU16)*3))
				return DescriptorValidity::Invalid( "Triangle stride bytes is invalid. Check 16 bit flags values" );
			}
		else
			{
			if((_desc->triangleStrideBytes < sizeof(NxU32)*3))
				return DescriptorValidity::Invalid( "Triangle stride bytes is invalid" );
			}
		}
	else
		{
		// We can compute the hull from the vertices
		if(!(_desc->flags & NX_CF_COMPUTE_CONVEX))
			return DescriptorValidity::Invalid( "Triangles not supplied and compute convex flag not set" );
			// If the mesh is convex and we're not allowed to compute the hull,
							// you have to provide it completely (geometry & topology).
		}
	
	return _desc->isValid();
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