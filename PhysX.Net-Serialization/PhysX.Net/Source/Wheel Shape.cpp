#include "StdAfx.h"

#include "Wheel Shape.h"
#include "Scene.h"
#include "Actor.h"
#include "Spring Description.h"
#include "User Wheel Contact Modify.h"

#include <NxWheelShape.h> 
#include <NxWheelShapeDesc.h> 

using namespace StillDesign::PhysX;

WheelShape::WheelShape( NxWheelShape* wheelShape ) : Shape( wheelShape )
{
	
}

WheelShapeDescription^ WheelShape::SaveToDescription()
{
	WheelShapeDescription^ wheelShapeDesc = gcnew WheelShapeDescription();
		this->UnmanagedPointer->saveToDesc( *wheelShapeDesc->UnmanagedPointer );
		
	Shape::SaveToDescription( wheelShapeDesc );
	
	return wheelShapeDesc;
}

WheelContactData^ WheelShape::GetContactData()
{
	NxWheelContactData* contactData = (NxWheelContactData*)malloc( sizeof( NxWheelContactData ) );
	NxShape* shape = this->UnmanagedPointer->getContact( *contactData );
	
	if( shape == NULL ) // No contact occured
	{
		free( contactData );
		
		return WheelContactData::Empty;
	}else{
		Shape^ s = ObjectCache::GetObject<Shape^>( (intptr_t)shape );
		
		return gcnew WheelContactData( contactData, s );
	}
}

UserWheelContactModify^ WheelShape::WheelContactModify::get()
{
	return _wheelContactModify;
}
void WheelShape::WheelContactModify::set( UserWheelContactModify^ value )
{
	_wheelContactModify = value;
	
	if( value == nullptr )
		this->UnmanagedPointer->setUserWheelContactModify( NULL );
	else
		this->UnmanagedPointer->setUserWheelContactModify( value->UnmanagedPointer );
}

float WheelShape::Radius::get()
{
	return this->UnmanagedPointer->getRadius();
}
void WheelShape::Radius::set( float value )
{
	this->UnmanagedPointer->setRadius( value );
}

float WheelShape::SuspensionTravel::get()
{
	return this->UnmanagedPointer->getSuspensionTravel();
}
void WheelShape::SuspensionTravel::set( float value )
{
	this->UnmanagedPointer->setSuspensionTravel( value );
}

SpringDescription WheelShape::Suspension::get()
{
	return (SpringDescription)this->UnmanagedPointer->getSuspension();
}
void WheelShape::Suspension::set( SpringDescription value )
{
	this->UnmanagedPointer->setSuspension( (NxSpringDesc)value );
}

TireFunctionDescription WheelShape::LongitudalTireForceFunction::get()
{
	return (TireFunctionDescription)this->UnmanagedPointer->getLongitudalTireForceFunction();
}
void WheelShape::LongitudalTireForceFunction::set( TireFunctionDescription value )
{
	this->UnmanagedPointer->setLongitudalTireForceFunction( (NxTireFunctionDesc)value );
}

TireFunctionDescription WheelShape::LateralTireForceFunction::get()
{
	return (TireFunctionDescription)this->UnmanagedPointer->getLateralTireForceFunction();
}
void WheelShape::LateralTireForceFunction::set( TireFunctionDescription value )
{
	this->UnmanagedPointer->setLateralTireForceFunction( (NxTireFunctionDesc)value );
}

float WheelShape::InverseWheelMass::get()
{
	return this->UnmanagedPointer->getInverseWheelMass();
}
void WheelShape::InverseWheelMass::set( float value )
{
	this->UnmanagedPointer->setInverseWheelMass( value );
}

WheelShapeFlag WheelShape::Flags::get()
{
	return (WheelShapeFlag)this->UnmanagedPointer->getWheelFlags();
}
void WheelShape::Flags::set( WheelShapeFlag value )
{
	this->UnmanagedPointer->setWheelFlags( (NxWheelShapeFlags)value );
}

float WheelShape::MotorTorque::get()
{
	return this->UnmanagedPointer->getMotorTorque();
}
void WheelShape::MotorTorque::set( float value )
{
	this->UnmanagedPointer->setMotorTorque( value );
}

float WheelShape::BrakeTorque::get()
{
	return this->UnmanagedPointer->getBrakeTorque();
}
void WheelShape::BrakeTorque::set( float value )
{
	this->UnmanagedPointer->setBrakeTorque( value );
}

float WheelShape::SteeringAngle::get()
{
	return this->UnmanagedPointer->getSteerAngle();
}
void WheelShape::SteeringAngle::set( float value )
{
	this->UnmanagedPointer->setSteerAngle( value );
}

float WheelShape::AxleSpeed::get()
{
	return this->UnmanagedPointer->getAxleSpeed();
}
void WheelShape::AxleSpeed::set( float value )
{
	this->UnmanagedPointer->setAxleSpeed( value );
}

NxWheelShape* WheelShape::UnmanagedPointer::get()
{
	return (NxWheelShape*)Shape::UnmanagedPointer;
}