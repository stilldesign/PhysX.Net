#include "StdAfx.h"

#include "Capsule Shape.h"
#include "Capsule.h"
#include "Scene.h"
#include "Actor.h"
#include "Capsule Shape Description.h"

#include <NxCapsuleShape.h> 
#include <NxCapsuleShapeDesc.h> 

using namespace StillDesign::PhysX;

CapsuleShape::CapsuleShape( NxCapsuleShape* capsuleShape ) : Shape( capsuleShape )
{
	
}

CapsuleShapeDescription^ CapsuleShape::SaveToDescription()
{
	CapsuleShapeDescription^ capsuleShapeDesc = gcnew CapsuleShapeDescription();
		this->UnmanagedPointer->saveToDesc( *capsuleShapeDesc->UnmanagedPointer );
		
	Shape::SaveToDescription( capsuleShapeDesc );
	
	return capsuleShapeDesc;
}

void CapsuleShape::SetDimensions( float radius, float height )
{
	this->UnmanagedPointer->setDimensions( radius, height );
}
Capsule CapsuleShape::GetWorldSpaceCapsule()
{
	NxCapsule capsule;
	this->UnmanagedPointer->getWorldCapsule( capsule );
	
	return (Capsule)capsule;
}

float CapsuleShape::Radius::get()
{
	return this->UnmanagedPointer->getRadius();
}
void CapsuleShape::Radius::set( float value )
{
	this->UnmanagedPointer->setRadius( value );
}
float CapsuleShape::Height::get()
{
	return this->UnmanagedPointer->getHeight();
}
void CapsuleShape::Height::set( float value )
{
	this->UnmanagedPointer->setHeight( value );
}

NxCapsuleShape* CapsuleShape::UnmanagedPointer::get()
{
	return (NxCapsuleShape*)Shape::UnmanagedPointer;
}