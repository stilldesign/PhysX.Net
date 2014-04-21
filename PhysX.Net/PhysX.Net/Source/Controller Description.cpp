#include "StdAfx.h"

#include "Controller Description.h"
#include "User Controller Hit Report.h"

using namespace StillDesign::PhysX;

ControllerDescription::ControllerDescription( NxControllerDesc* controllerDesc )
{
	_desc = controllerDesc;
}
ControllerDescription::~ControllerDescription()
{
	this->!ControllerDescription();
}
ControllerDescription::!ControllerDescription()
{
	// ~NxControllerDesc is protected
	_desc = NULL;
	
	_hitReport = nullptr;
}

bool ControllerDescription::IsValid()
{
	return _desc->isValid();
}
int ControllerDescription::CheckValid()
{
	return _desc->checkValid();
}
void ControllerDescription::SetToDefault()
{
	_desc->setToDefault();
	
	_hitReport = nullptr;
}

ControllerType ControllerDescription::Type::get()
{
	return (ControllerType)_desc->getType();
}

Vector3 ControllerDescription::Position::get()
{
	NxExtendedVec3 pos = _desc->position;
	
	return Vector3( (float)pos.x, (float)pos.y, (float)pos.z );
}

void ControllerDescription::Position::set( Vector3 value )
{
	_desc->position = NxExtendedVec3( value.X, value.Y, value.Z );
}

float ControllerDescription::SlopeLimit::get()
{
	return _desc->slopeLimit;
}
void ControllerDescription::SlopeLimit::set( float value )
{
	_desc->slopeLimit = value;
}
float ControllerDescription::SkinWidth::get()
{
	return _desc->skinWidth;
}
void ControllerDescription::SkinWidth::set( float value )
{
	_desc->skinWidth = value;
}

float ControllerDescription::StepOffset::get()
{
	return _desc->stepOffset;
}
void ControllerDescription::StepOffset::set( float value )
{
	_desc->stepOffset = value;
}

CCTInteractionFlag ControllerDescription::InteractionFlag::get()
{
	return (CCTInteractionFlag)_desc->interactionFlag;
}
void ControllerDescription::InteractionFlag::set( CCTInteractionFlag value )
{
	_desc->interactionFlag = (NxCCTInteractionFlag)value;
}

Axis ControllerDescription::UpDirection::get()
{
	return (Axis)_desc->upDirection;
}
void ControllerDescription::UpDirection::set( Axis value )
{
	_desc->upDirection = (NxHeightFieldAxis)value;
}

UserControllerHitReport^ ControllerDescription::Callback::get()
{
	return _hitReport;
}
void ControllerDescription::Callback::set( UserControllerHitReport^ value )
{
	_hitReport = value;
	
	if( value == nullptr )
		_desc->callback = NULL;
	else
		_desc->callback = value->UnmanagedPointer;
}

NxControllerDesc* ControllerDescription::UnmanagedPointer::get()
{
	return _desc;
}