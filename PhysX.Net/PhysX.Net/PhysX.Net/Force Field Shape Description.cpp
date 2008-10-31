#include "StdAfx.h"

#include "Force Field Shape Description.h"
#include "Functions.h"
#include "Groups Mask.h"

#include <NxForceFieldShapeDesc.h>

using namespace StillDesign::PhysX;

ForceFieldShapeDescription::ForceFieldShapeDescription( NxForceFieldShapeDesc* forceFieldShapeDesc )
{
	Debug::Assert( forceFieldShapeDesc != NULL );
	
	_forceFieldShapeDesc = forceFieldShapeDesc;
}
ForceFieldShapeDescription::~ForceFieldShapeDescription()
{
	this->!ForceFieldShapeDescription();
}
ForceFieldShapeDescription::!ForceFieldShapeDescription()
{
	SAFE_DELETE( _forceFieldShapeDesc );
	
	_userData = nullptr;
}

void ForceFieldShapeDescription::SetToDefault()
{
	_forceFieldShapeDesc->setToDefault();
	
	_userData = nullptr;
}
bool ForceFieldShapeDescription::IsValid()
{
	return _forceFieldShapeDesc->isValid();
}

String^ ForceFieldShapeDescription::Name::get()
{
	return StillDesign::PhysX::Functions::UnmanagedToManagedString( _forceFieldShapeDesc->name );
}
void ForceFieldShapeDescription::Name::set( String^ value )
{
	_forceFieldShapeDesc->name = StillDesign::PhysX::Functions::ManagedToUnmanagedString( value );
}

ShapeType ForceFieldShapeDescription::Type::get()
{
	return (ShapeType)_forceFieldShapeDesc->getType();
}

Object^ ForceFieldShapeDescription::UserData::get()
{
	return _userData;
}
void ForceFieldShapeDescription::UserData::set( Object^ value )
{
	_userData = value;
}

NxForceFieldShapeDesc* ForceFieldShapeDescription::UnmanagedPointer::get()
{
	return _forceFieldShapeDesc;
}