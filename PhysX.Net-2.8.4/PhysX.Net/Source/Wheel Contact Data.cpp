#include "StdAfx.h"

#include "Shape.h"
#include "Wheel Contact Data.h"

#include <NxWheelShape.h> 

using namespace StillDesign::PhysX;

WheelContactData::WheelContactData()
{
	_contactData = (NxWheelContactData*)malloc( sizeof( NxWheelContactData ) );
	
	NxWheelContactData data;
		data.contactForce = 0;
		data.contactNormal.zero();
		data.contactPoint.zero();
		data.contactPosition = 0;
		data.lateralDirection.zero();
		data.lateralImpulse = 0;
		data.lateralSlip = 0;
		data.longitudalDirection.zero();
		data.longitudalImpulse = 0;
		data.longitudalSlip = 0;
		data.otherShapeMaterialIndex = 0;
	
	*_contactData = data;
	
	_shape = nullptr;
}
WheelContactData::WheelContactData( NxWheelContactData* contactData, Shape^ shape )
{
	if( contactData == NULL )
		throw gcnew ArgumentNullException( "contactData", "Contact data parameter is NULL" );
	
	_contactData = contactData;
	_shape = shape;
}
WheelContactData::~WheelContactData()
{
	this->!WheelContactData();
}
WheelContactData::!WheelContactData()
{
	//SAFE_DELETE( _contactData );
	if( _contactData != NULL )
	{
		free( _contactData );
		_contactData = NULL;
	}
	
	_shape = nullptr;
}

Shape^ WheelContactData::ContactShape::get()
{
	return _shape;
}

Vector3 WheelContactData::ContactPoint::get()
{
	return Math::NxVec3ToVector3( _contactData->contactPoint );
}

Vector3 WheelContactData::ContactNormal::get()
{
	return Math::NxVec3ToVector3( _contactData->contactNormal );
}

Vector3 WheelContactData::LongitudalDirection::get()
{
	return Math::NxVec3ToVector3( _contactData->longitudalDirection );
}

Vector3 WheelContactData::LateralDirection::get()
{
	return Math::NxVec3ToVector3( _contactData->lateralDirection );
}

float WheelContactData::ContactForce::get()
{
	return _contactData->contactForce;
}

float WheelContactData::LongitudalSlip::get()
{
	return _contactData->longitudalSlip;
}

float WheelContactData::LateralSlip::get()
{
	return _contactData->lateralSlip;
}

float WheelContactData::LongitudalImpulse::get()
{
	return _contactData->longitudalImpulse;
}

float WheelContactData::LateralImpulse::get()
{
	return _contactData->lateralImpulse;
}

unsigned int WheelContactData::OtherShapeMaterialIndex::get()
{
	return _contactData->otherShapeMaterialIndex;
}

float WheelContactData::ContactPosition::get()
{
	return _contactData->contactPosition;
}

WheelContactData^ WheelContactData::Empty::get()
{
	return gcnew WheelContactData();
}