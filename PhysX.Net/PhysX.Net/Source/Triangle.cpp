#include "StdAfx.h"

#include "Triangle.h"

using namespace StillDesign::PhysX;

Triangle::Triangle( Vector3 vertex0, Vector3 vertex1, Vector3 vertex2 )
{
	this->Vertex0 = vertex0;
	this->Vertex1 = vertex1;
	this->Vertex2 = vertex2;
}

Triangle::operator NxTriangle( Triangle triangle )
{
	NxTriangle t;
		t.verts[ 0 ] = Math::Vector3ToNxVec3( triangle.Vertex0 );
		t.verts[ 1 ] = Math::Vector3ToNxVec3( triangle.Vertex1 );
		t.verts[ 2 ] = Math::Vector3ToNxVec3( triangle.Vertex2 );
	
	return t;
}
Triangle::operator Triangle( NxTriangle triangle )
{
	Triangle t;
		t.Vertex0 = Math::NxVec3ToVector3( triangle.verts[ 0 ] );
		t.Vertex1 = Math::NxVec3ToVector3( triangle.verts[ 1 ] );
		t.Vertex2 = Math::NxVec3ToVector3( triangle.verts[ 2 ] );
	
	return t;
}

Vector3 Triangle::Normal()
{
	return Vector3::Normalize( Vector3::Cross( this->default[ 1 ]-this->default[ 0 ], this->default[ 2 ]-this->default[ 0 ] ) );
}
Vector3 Triangle::Center()
{
	return (this->Vertex0 + this->Vertex1 + this->Vertex2) * NX_INV3;
}
void Triangle::Inflate( float fatCoeff, bool constantBorder )
{
	// Compute triangle center
	Vector3 triangleCenter = Center();
	
	// Don't normalize?
	// Normalize => add a constant border, regardless of triangle size
	// Don't => add more to big triangles
	for( unsigned int i = 0; i < 3; i++ )
	{
		Vector3 v = this->default[ i ] - triangleCenter;
		
		if( constantBorder )
			v.Normalize();
	
		this->default[ i ] += v * fatCoeff;
	}
}

Vector3 Triangle::default::get( int index )
{
	switch( index )
	{
		case 0:
			return this->Vertex0;
		case 1:
			return this->Vertex1;
		case 2:
			return this->Vertex2;
		
		default: throw gcnew ArgumentException( "Invalid index" );
	}
}
void Triangle::default::set( int index, Vector3 value )
{
	switch( index )
	{
		case 0:
			this->Vertex0 = value;
		break;
		case 1:
			this->Vertex1 = value;
		break;
		case 2:
			this->Vertex2 = value;
		break;
		
		default: throw gcnew ArgumentException( "Invalid index" );
	}
}