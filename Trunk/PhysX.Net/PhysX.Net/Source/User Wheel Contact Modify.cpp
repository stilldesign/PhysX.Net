#include "StdAfx.h"

#include "User Wheel Contact Modify.h"
#include "Scene.h"
#include "Material.h"

using namespace StillDesign::PhysX;

UserWheelContactModify::UserWheelContactModify()
{
	_internalWheelContactModify = new InternalWheelContactModify( this );
}

InternalWheelContactModify* UserWheelContactModify::UnmanagedPointer::get()
{
	return _internalWheelContactModify;
}

//

UserWheelContactModifyData::UserWheelContactModifyData( StillDesign::PhysX::WheelShape^ wheelShape, Shape^ otherShape )
{
	_wheelShape = wheelShape;
	_otherShape = otherShape;
}

StillDesign::PhysX::WheelShape^ UserWheelContactModifyData::WheelShape::get()
{
	return _wheelShape;
}
StillDesign::PhysX::Shape^ UserWheelContactModifyData::OtherShape::get()
{
	return _otherShape;
}

Vector3 UserWheelContactModifyData::ContactPoint::get()
{
	return _contactPoint;
}
void UserWheelContactModifyData::ContactPoint::set( Vector3 value )
{
	_contactPoint = value;
}

Vector3 UserWheelContactModifyData::ContactNormal::get()
{
	return _contactNormal;
}
void UserWheelContactModifyData::ContactNormal::set( Vector3 value )
{
	_contactNormal = value;
}

float UserWheelContactModifyData::ContactPosition::get()
{
	return _contactPosition;
}
void UserWheelContactModifyData::ContactPosition::set( float value )
{
	_contactPosition = value;
}

float UserWheelContactModifyData::NormalForce::get()
{
	return _normalForce;
}
void UserWheelContactModifyData::NormalForce::set( float value )
{
	_normalForce = value;
}

Material^ UserWheelContactModifyData::OtherShapeMaterial::get()
{
	return _otherShapeMaterial;
}
void UserWheelContactModifyData::OtherShapeMaterial::set( Material^ value )
{
	_otherShapeMaterial = value;
}

int UserWheelContactModifyData::OtherShapeFeatureIndex::get()
{
	return _otherShapeFeatureIndex;
}
void UserWheelContactModifyData::OtherShapeFeatureIndex::set( int value )
{
	_otherShapeFeatureIndex = value;
}

//

InternalWheelContactModify::InternalWheelContactModify( UserWheelContactModify^ wheelContactModify )
{
	_wheelContactModify = wheelContactModify;
}

bool InternalWheelContactModify::onWheelContact( NxWheelShape* wheelShape, NxVec3& contactPoint, NxVec3& contactNormal, NxReal& contactPosition, NxReal& normalForce, NxShape* otherShape, NxMaterialIndex& otherShapeMaterialIndex, NxU32 otherShapeFeatureIndex )
{
	WheelShape^ wheel = ObjectCache::GetObject<WheelShape^>( (intptr_t)wheelShape );
	Shape^ other = ObjectCache::GetObject<Shape^>( (intptr_t)otherShape );
	
	UserWheelContactModifyData^ data = gcnew UserWheelContactModifyData( wheel, other );
		data->ContactNormal = Math::NxVec3ToVector3( contactNormal );
		data->ContactPoint = Math::NxVec3ToVector3( contactPoint );
		data->ContactPosition = contactPosition;
		data->NormalForce = normalForce;
		data->OtherShapeFeatureIndex = otherShapeFeatureIndex;
		data->OtherShapeMaterial = ObjectCache::GetObject<Material^>( (intptr_t)otherShapeMaterialIndex );
	
	bool result = _wheelContactModify->OnWheelContact( data );
	
	if( result == true )
	{
		contactPoint = Math::Vector3ToNxVec3( data->ContactPoint );
		contactNormal = Math::Vector3ToNxVec3( data->ContactNormal );
		contactPosition = data->ContactPosition;
		normalForce = data->NormalForce;
		otherShapeMaterialIndex = data->OtherShapeMaterial->Index;
		otherShapeFeatureIndex = data->OtherShapeFeatureIndex;
	}
	
	return result;
}