#include "StdAfx.h"

#include "Actor Description Base.h"

#include "Actor.h"
#include "Shape.h"
#include "Capsule Shape.h"
#include "Plane Shape.h"
#include "Triangle Mesh Shape Description.h"
#include "Box Shape.h"
#include "Sphere Shape.h"
#include "Body Description.h"
#include "Math.h"
#include "Functions.h"
#include "Compartment.h"

using namespace StillDesign;
using namespace StillDesign::PhysX;

ActorDescriptionBase::ActorDescriptionBase()
{
	_desc = new NxActorDesc();
}
ActorDescriptionBase::~ActorDescriptionBase()
{
	this->!ActorDescriptionBase();
}
ActorDescriptionBase::!ActorDescriptionBase()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	SAFE_DELETE( _desc );
	
	_body = nullptr;
	
	OnDisposed( this, nullptr );
}
bool ActorDescriptionBase::IsDisposed::get()
{
	return ( _desc == NULL );
}

bool ActorDescriptionBase::IsValid()
{
	return _desc->isValid() && IsMassDensityValid();
}
void ActorDescriptionBase::SetToDefault()
{
	_desc->setToDefault();
	
	_body = nullptr;
	_compartment = nullptr;
	
	_userData = nullptr;
}

bool ActorDescriptionBase::IsMassDensityValid()
{
	if( _desc->body == NULL )
	{
		return true;
	}else{
		if( _desc->density == 0.0f && _desc->body->mass > 0.0f && _desc->body->massSpaceInertia.magnitude() > 0.0f )
			return true;
		if( _desc->density > 0.0f && _desc->shapes.size() > 0 && _desc->body->mass == 0.0f && _desc->body->massSpaceInertia.magnitude() == 0.0f )
			return true;
		if( _desc->density == 0.0f && _desc->shapes.size() > 0 && _desc->body->mass > 0.0f && _desc->body->massSpaceInertia.magnitude() == 0.0f )
			return true;
	}
	
	return false;
}

String^ ActorDescriptionBase::Name::get()
{
	return Functions::UnmanagedToManagedString( _desc->name );
}
void ActorDescriptionBase::Name::set( String^ value )
{
	_desc->name = Functions::ManagedToUnmanagedString( value );
}
ActorDescriptionType ActorDescriptionBase::Type::get()
{
	return (ActorDescriptionType)_desc->getType();
}

StillDesign::PhysX::BodyDescription^ ActorDescriptionBase::BodyDescription::get()
{
	return _body;
}
void ActorDescriptionBase::BodyDescription::set( StillDesign::PhysX::BodyDescription^ value )
{
	_body = value;
	
	if( value == nullptr )
		_desc->body = NULL;
	else
		_desc->body = value->UnmanagedPointer;
}

StillDesign::PhysX::Compartment^ ActorDescriptionBase::Compartment::get()
{
	return _compartment;
}
void ActorDescriptionBase::Compartment::set( StillDesign::PhysX::Compartment^ value )
{
	_compartment = value;
	
	if( value != nullptr )
		_desc->compartment = value->UnmanagedPointer;
	else
		_desc->compartment = NULL;
}

float ActorDescriptionBase::Density::get()
{
	return _desc->density;
}
void ActorDescriptionBase::Density::set( float value )
{
	if( value < 0 )
		throw gcnew ArgumentOutOfRangeException( "value", value, "Value must be greater than or equal to 0" );
	
	_desc->density = value;
}

ActorFlag ActorDescriptionBase::Flags::get()
{
	return (ActorFlag)_desc->flags;
}
void ActorDescriptionBase::Flags::set( ActorFlag value )
{
	_desc->flags = (NxActorFlag)value;
}

short ActorDescriptionBase::Group::get()
{
	return _desc->group;
}
void ActorDescriptionBase::Group::set( short value )
{
	_desc->group = value;
}

short ActorDescriptionBase::DominanceGroup::get()
{
	return _desc->dominanceGroup;
}
void ActorDescriptionBase::DominanceGroup::set( short value )
{
	_desc->dominanceGroup = value;
}

ContactPairFlag ActorDescriptionBase::ContactReportFlags::get()
{
	return (ContactPairFlag)_desc->contactReportFlags;
}
void ActorDescriptionBase::ContactReportFlags::set( ContactPairFlag value )
{
	_desc->contactReportFlags = (NxU32)value;
}

ContactPairFlag ActorDescriptionBase::ContactPairFlags::get()
{
	return (ContactPairFlag)_desc->contactReportFlags;
}
void ActorDescriptionBase::ContactPairFlags::set( ContactPairFlag value )
{
	_desc->contactReportFlags = (NxU32)value;
}

short ActorDescriptionBase::ForceFieldMaterial::get()
{
	return _desc->forceFieldMaterial;
}
void ActorDescriptionBase::ForceFieldMaterial::set( short value )
{
	_desc->forceFieldMaterial = value;
}

Matrix ActorDescriptionBase::GlobalPose::get()
{
	return StillDesign::PhysX::Math::Mat34ToMatrix( &_desc->globalPose );
}
void ActorDescriptionBase::GlobalPose::set( Matrix value )
{
	_desc->globalPose = StillDesign::PhysX::Math::MatrixToMat34( value );
}

Object^ ActorDescriptionBase::UserData::get()
{
	return _userData;
}
void ActorDescriptionBase::UserData::set( Object^ value )
{
	_userData = value;
}

NxActorDesc* ActorDescriptionBase::UnmanagedPointer::get()
{
	return _desc;
}