#include "StdAfx.h"

#include "Debug Renderable.h"

#include <NxDebugRenderable.h> 

using namespace StillDesign::PhysX;

DebugPoint::DebugPoint( Vector3 point, int color )
{
	_point = point;
	_color = color;
}
DebugLine::DebugLine( Vector3 point0, Vector3 point1, int color )
{
	_point0 = point0;
	_point1 = point1;
	_color = color;
}
DebugTriangle::DebugTriangle( Vector3 point0, Vector3 point1, Vector3 point2, int color )
{
	_point0 = point0;
	_point1 = point1;
	_point2 = point2;
	_color = color;
}

DebugRenderable::DebugRenderable( NxDebugRenderable* debugRenderable )
{
	Debug::Assert( debugRenderable != NULL );

	_debugRenderable = debugRenderable;
}
DebugRenderable::~DebugRenderable()
{
	this->!DebugRenderable();
}
DebugRenderable::!DebugRenderable()
{
	SAFE_DELETE( _debugRenderable );
}

array< DebugPoint >^ DebugRenderable::GetDebugPoints()
{
	array<DebugPoint>^ points = gcnew array<DebugPoint>( this->PointCount );
	
	const NxDebugPoint* j = _debugRenderable->getPoints();
	for( int x = 0; x < this->PointCount; x++ )
	{
		NxVec3 p = j->p;
		Vector3 point = Vector3( p.x, p.y, p.z );
		
		points[ x ] = DebugPoint( point, j->color );
		
		j++;
	}
	
	return points;
}
array< DebugLine >^ DebugRenderable::GetDebugLines()
{
	array<DebugLine>^ lines = gcnew array<DebugLine>( this->LineCount );
	
	const NxDebugLine* j = _debugRenderable->getLines();
	for( int x = 0; x < this->LineCount; x++ )
	{
		NxVec3 p0 = j->p0;
		NxVec3 p1 = j->p1;
		
		Vector3 point0 = Vector3( p0.x, p0.y, p0.z );
		Vector3 point1 = Vector3( p1.x, p1.y, p1.z );
		
		lines[ x ] = DebugLine( point0, point1, j->color );
		
		j++;
	}
	
	return lines;
}
array< DebugTriangle >^ DebugRenderable::GetDebugTriangles()
{
	array<DebugTriangle>^ triangles = gcnew array<DebugTriangle>( this->TriangleCount );
	
	const NxDebugTriangle* j = _debugRenderable->getTriangles();
	for( int x = 0; x < this->TriangleCount; x++ )
	{
		NxVec3 p0 = j->p0;
		NxVec3 p1 = j->p1;
		NxVec3 p2 = j->p2;
		
		Vector3 point0 = Vector3( p0.x, p0.y, p0.z );
		Vector3 point1 = Vector3( p1.x, p1.y, p1.z );
		Vector3 point2 = Vector3( p2.x, p2.y, p2.z );
		
		triangles[ x ] = DebugTriangle( point0, point1, point2, j->color );
		
		j++;
	}
	
	return triangles;
}

int DebugRenderable::PointCount::get()
{
	return _debugRenderable->getNbPoints();
}
int DebugRenderable::LineCount::get()
{
	return _debugRenderable->getNbLines();
}
int DebugRenderable::TriangleCount::get()
{
	return _debugRenderable->getNbTriangles();
}

// Point
Vector3 DebugPoint::Point::get()
{
	return _point;
}
int DebugPoint::Color::get()
{
	return _color;
}

// Line
Vector3 DebugLine::Point0::get()
{
	return _point0;
}
Vector3 DebugLine::Point1::get()
{
	return _point1;
}
int DebugLine::Color::get()
{
	return _color;
}

// Triangle
Vector3 DebugTriangle::Point0::get()
{
	return _point0;
}
Vector3 DebugTriangle::Point1::get()
{
	return _point1;
}
Vector3 DebugTriangle::Point2::get()
{
	return _point2;
}
int DebugTriangle::Color::get()
{
	return _color;
}