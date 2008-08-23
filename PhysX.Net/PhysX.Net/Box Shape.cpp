#include "StdAfx.h"

#include "Box Shape.h"
#include "Shape Description.h"
#include "Shape.h"
#include "Actor.h"
#include "Scene.h"
#include "Box.h"
#include "Box Shape Description.h"

#include <NxBoxShape.h>

using namespace StillDesign::PhysX;

BoxShape::BoxShape( NxBoxShape* boxShape ) : Shape( boxShape )
{
	
}

BoxShapeDescription^ BoxShape::SaveToDescription()
{
	BoxShapeDescription^ boxShapeDesc = gcnew BoxShapeDescription();
		this->UnmanagedPointer->saveToDesc( *boxShapeDesc->UnmanagedPointer );
		
	Shape::SaveToDescription( boxShapeDesc );
	
	return boxShapeDesc;
}

Box BoxShape::GetWorldSpaceOBB()
{
	NxBox worldOBB;
	this->UnmanagedPointer->getWorldOBB( worldOBB );
	
	return (Box)worldOBB;
}

Vector3 BoxShape::Dimensions::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getDimensions() );
}
void BoxShape::Dimensions::set( Vector3 value )
{
	this->UnmanagedPointer->setDimensions( Math::Vector3ToNxVec3( value ) );
}
Vector3 BoxShape::Size::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getDimensions() ) * 2.0f;
}
void BoxShape::Size::set( Vector3 value )
{
	this->UnmanagedPointer->setDimensions( Math::Vector3ToNxVec3( value ) * 0.5f );
}

NxBoxShape* BoxShape::UnmanagedPointer::get()
{
	return (NxBoxShape*)Shape::UnmanagedPointer;
}