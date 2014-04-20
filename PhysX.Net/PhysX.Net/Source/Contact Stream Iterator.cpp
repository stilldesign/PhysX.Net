#include "StdAfx.h"

#include "Contact Stream Iterator.h"
#include "Constant Contact Stream.h"

#include <NxContactStreamIterator.h> 

using namespace StillDesign::PhysX;

ContactStreamIterator::ContactStreamIterator( ConstantContactStream^ contactStream )
{
	if( contactStream == nullptr )
		throw gcnew ArgumentNullException( "contactStream" );
	
	_iter = new NxContactStreamIterator( *contactStream->UnmanagedPointer );
}
ContactStreamIterator::~ContactStreamIterator()
{
	this->!ContactStreamIterator();
}
ContactStreamIterator::!ContactStreamIterator()
{
	_iter = NULL;
}
bool ContactStreamIterator::IsDisposed::get()
{
	return _iter == NULL;
}

bool ContactStreamIterator::GoToNextPair()
{
	return _iter->goNextPair();
}
bool ContactStreamIterator::GoToNextPatch()
{
	return _iter->goNextPatch();
}
bool ContactStreamIterator::GoToNextPoint()
{
	return _iter->goNextPoint();
}

int ContactStreamIterator::GetNumberOfPairs()
{
	return _iter->getNumPairs();
}

Shape^ ContactStreamIterator::GetShapeA()
{
	return GetShape( 0 );
}
Shape^ ContactStreamIterator::GetShapeB()
{
	return GetShape( 1 );
}
Shape^ ContactStreamIterator::GetShape( int shapeIndex )
{
	if( shapeIndex != 0 && shapeIndex != 1 )
		throw gcnew ArgumentException( "Shape index must be either 0 or 1", "shapeIndex" );
	
	NxShape* shape = _iter->getShape( shapeIndex );
	
	bool isDeleted = _iter->isDeletedShape( shapeIndex );
	if( isDeleted )
		return nullptr;
	
	return ObjectTable::GetObject<Shape^>( (intptr_t)shape );
}

bool ContactStreamIterator::IsDeletedShapeA()
{
	return IsDeletedShape( 0 );
}
bool ContactStreamIterator::IsDeletedShapeB()
{
	return IsDeletedShape( 1 );
}
bool ContactStreamIterator::IsDeletedShape( int shapeIndex )
{
	if( shapeIndex != 0 && shapeIndex != 1 )
		throw gcnew ArgumentException( "Shape index must be either 0 or 1", "shapeIndex" );
	
	return _iter->isDeletedShape( shapeIndex );
}

ShapeFlag ContactStreamIterator::GetShapeFlags()
{
	return (ShapeFlag)_iter->getShapeFlags();
}

int ContactStreamIterator::GetNumberOfPatches()
{
	return _iter->getNumPatches();
}

int ContactStreamIterator::GetNumberOfPatchesRemaining()
{
	return _iter->getNumPatchesRemaining();
}

Vector3 ContactStreamIterator::GetPatchNormal()
{
	return Math::NxVec3ToVector3( _iter->getPatchNormal() );
}

int ContactStreamIterator::GetNumberOfPoints()
{
	return _iter->getNumPoints();
}

int ContactStreamIterator::GetNumberOfPointsRemaining()
{
	return _iter->getNumPointsRemaining();
}

Vector3 ContactStreamIterator::GetPoint()
{
	return Math::NxVec3ToVector3( _iter->getPoint() );
}

float ContactStreamIterator::GetSeperation()
{
	return _iter->getSeparation();
}

int ContactStreamIterator::GetFeatureIndex0()
{
	return _iter->getFeatureIndex0();
}
int ContactStreamIterator::GetFeatureIndex1()
{
	return _iter->getFeatureIndex1();
}

float ContactStreamIterator::GetPointNormalForce()
{
	return _iter->getPointNormalForce();
}