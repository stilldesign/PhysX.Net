#include "StdAfx.h"

#include "Height Field Shape.h"
#include "Bounds.h"
#include "Actor.h"
#include "Core.h"
#include "Height Field Shape Description.h"
using namespace StillDesign::PhysX;

HeightFieldShape::HeightFieldShape( NxHeightFieldShape* heightFieldShape ) : Shape( heightFieldShape )
{
	_heightField = ObjectTable::GetObject<StillDesign::PhysX::HeightField^>( (intptr_t)(&heightFieldShape->getHeightField()) );
}

HeightFieldShapeDescription^ HeightFieldShape::SaveToDescription()
{
	HeightFieldShapeDescription^ desc = gcnew HeightFieldShapeDescription();
		this->UnmanagedPointer->saveToDesc( *desc->UnmanagedPointer );
		desc->HeightField = this->HeightField;
		
	return desc;
}

HeightFieldShape::GetTriangleResult^ HeightFieldShape::GetTriangle( int triangleIndex )
{
	return GetTriangle( triangleIndex, true, true );
}
HeightFieldShape::GetTriangleResult^ HeightFieldShape::GetTriangle( int triangleIndex, bool worldSpaceTranslation, bool worldSpaceRotation )
{
	NxTriangle triangle, edgeTriangle;
	NxU32 flags;
	this->UnmanagedPointer->getTriangle( triangle, &edgeTriangle, &flags, triangleIndex, worldSpaceTranslation, worldSpaceRotation );
	
	HeightFieldShape::GetTriangleResult^ result = gcnew HeightFieldShape::GetTriangleResult();
		result->WorldTriangle = (Triangle)triangle;
		result->EdgeTriangle = (Triangle)edgeTriangle;
		result->Flags = (TriangleFlag)flags;
	
	return result;
}

array<int>^ HeightFieldShape::GetOverlapAABBTriangles( Bounds3 bounds, QueryFlag flags )
{
	NxU32 count;
	const NxU32* indices;
	
	if( this->UnmanagedPointer->overlapAABBTriangles( (NxBounds3)bounds, (NxU32)flags, count, indices ) == false )
	{
		return nullptr;
	}else{
		array<int>^ i = gcnew array<int>( count );
		
		for( unsigned int x = 0; x < count; x++ )
		{
			i[ x ] = indices[ x ];
		}
		
		delete indices;
		indices = NULL;
		
		return i;
	}
}
//bool HeightFieldShape::GetOverlapAABBTriangles( Bounds3 bounds, QueryFlags flags, UserEntityReport<int>^ callback )
//{
//	return _heightFieldShape->overlapAABBTriangles( Bounds3::ToUnmanaged( bounds ), (NxU32)flags, callback->UnmanagedPointer );
//}
bool HeightFieldShape::IsShapePointOnHeightField( float x, float z )
{
	return this->UnmanagedPointer->isShapePointOnHeightField( x, z );
}
bool HeightFieldShape::GetMaterialAtShapePoint( float x, float z )
{
	return this->UnmanagedPointer->getMaterialAtShapePoint( x, z );
}
Vector3 HeightFieldShape::GetNormalAtShapePoint( float x, float z )
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getNormalAtShapePoint( x, z ) );
}
Vector3 HeightFieldShape::GetSmoothedNormalAtShapePoint( float x, float z )
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getSmoothNormalAtShapePoint( x, z ) );
}

HeightField^ HeightFieldShape::HeightField::get()
{
	return _heightField;
}
float HeightFieldShape::HeightScale::get()
{
	return this->UnmanagedPointer->getHeightScale();
}
void HeightFieldShape::HeightScale::set( float value )
{
	this->UnmanagedPointer->setHeightScale( value );
}

float HeightFieldShape::RowScale::get()
{
	return this->UnmanagedPointer->getRowScale();
}
void HeightFieldShape::RowScale::set( float value )
{
	this->UnmanagedPointer->setRowScale( value );
}
float HeightFieldShape::ColumnScale::get()
{
	return this->UnmanagedPointer->getColumnScale();
}
void HeightFieldShape::ColumnScale::set( float value )
{
	this->UnmanagedPointer->setColumnScale( value );
}

NxHeightFieldShape* HeightFieldShape::UnmanagedPointer::get()
{
	return (NxHeightFieldShape*)Shape::UnmanagedPointer;
}

//

Triangle HeightFieldShape::GetTriangleResult::WorldTriangle::get()
{
	return _worldTriangle;
}
void HeightFieldShape::GetTriangleResult::WorldTriangle::set( Triangle value )
{
	_worldTriangle = value;
}
Triangle HeightFieldShape::GetTriangleResult::EdgeTriangle::get()
{
	return _edgeTriangle;
}
void HeightFieldShape::GetTriangleResult::EdgeTriangle::set( Triangle value )
{
	_edgeTriangle = value;
}
TriangleFlag HeightFieldShape::GetTriangleResult::Flags::get()
{
	return _flags;
}
void HeightFieldShape::GetTriangleResult::Flags::set( TriangleFlag value )
{
	_flags = value;
}