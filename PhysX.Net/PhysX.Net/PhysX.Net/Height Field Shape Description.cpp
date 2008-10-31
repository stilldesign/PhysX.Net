#include "StdAfx.h"

#include "Height Field Shape Description.h"
#include "Height Field.h"

using namespace StillDesign::PhysX;

UsingFrameworkNamespace

HeightFieldShapeDescription::HeightFieldShapeDescription() : ShapeDescription( new NxHeightFieldShapeDesc() )
{
	
}

StillDesign::PhysX::HeightField^ HeightFieldShapeDescription::HeightField::get()
{
	return _heightField;
}
void HeightFieldShapeDescription::HeightField::set( StillDesign::PhysX::HeightField^ value )
{
	_heightField = value;
	
	if( value == nullptr )
		this->UnmanagedPointer->heightField = NULL;
	else
		this->UnmanagedPointer->heightField = value->UnmanagedPointer;
}

float HeightFieldShapeDescription::HeightScale::get()
{
	return this->UnmanagedPointer->heightScale;
}
void HeightFieldShapeDescription::HeightScale::set( float value )
{
	this->UnmanagedPointer->heightScale = value;
}

float HeightFieldShapeDescription::RowScale::get()
{
	return this->UnmanagedPointer->rowScale;
}
void HeightFieldShapeDescription::RowScale::set( float value )
{
	this->UnmanagedPointer->rowScale = value;
}

float HeightFieldShapeDescription::ColumnScale::get()
{
	return this->UnmanagedPointer->columnScale;
}
void HeightFieldShapeDescription::ColumnScale::set( float value )
{
	this->UnmanagedPointer->columnScale = value;
}

short HeightFieldShapeDescription::MaterialIndexHighBits::get()
{
	return this->UnmanagedPointer->materialIndexHighBits;
}
void HeightFieldShapeDescription::MaterialIndexHighBits::set( short value )
{
	this->UnmanagedPointer->materialIndexHighBits = value;
}

short HeightFieldShapeDescription::HoleMaterial::get()
{
	return this->UnmanagedPointer->holeMaterial;
}
void HeightFieldShapeDescription::HoleMaterial::set( short value )
{
	this->UnmanagedPointer->holeMaterial = value;
}

MeshShapeFlag HeightFieldShapeDescription::Flags::get()
{
	return (MeshShapeFlag)this->UnmanagedPointer->meshFlags;
}
void HeightFieldShapeDescription::Flags::set( MeshShapeFlag value )
{
	this->UnmanagedPointer->meshFlags = (NxU32)value;
}

NxHeightFieldShapeDesc* HeightFieldShapeDescription::UnmanagedPointer::get()
{
	return (NxHeightFieldShapeDesc*)ShapeDescription::UnmanagedPointer;
}