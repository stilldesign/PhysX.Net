#include "StdAfx.h"

#include "Height Field Description.h"
#include "Height Field.h"
#include "Core.h"
#include "Height Field Sample.h"

using namespace StillDesign::PhysX;

HeightFieldDescription::HeightFieldDescription()
{
	_heightFieldDesc = new NxHeightFieldDesc();
		_heightFieldDesc->sampleStride = sizeof( NxHeightFieldSample );
}
HeightFieldDescription::~HeightFieldDescription()
{
	this->!HeightFieldDescription();
}
HeightFieldDescription::!HeightFieldDescription()
{
	SAFE_DELETE( _heightFieldDesc );
}

void HeightFieldDescription::SetToDefault()
{
	_heightFieldDesc->setToDefault();
	
	_samples = nullptr;
}
bool HeightFieldDescription::IsValid()
{
	return _heightFieldDesc->isValid();
}

//

int HeightFieldDescription::NumberOfRows::get()
{
	return _heightFieldDesc->nbRows;
}
void HeightFieldDescription::NumberOfRows::set( int value )
{
	_heightFieldDesc->nbRows = value;
}

int HeightFieldDescription::NumberOfColumns::get()
{
	return _heightFieldDesc->nbColumns;
}
void HeightFieldDescription::NumberOfColumns::set( int value )
{
	_heightFieldDesc->nbColumns = value;
}

HeightFieldFormat HeightFieldDescription::Format::get()
{
	return (HeightFieldFormat)_heightFieldDesc->format;
}
void HeightFieldDescription::Format::set( HeightFieldFormat value )
{
	_heightFieldDesc->format = (NxHeightFieldFormat)value;
}

array<HeightFieldSample>^ HeightFieldDescription::Samples::get()
{
	return _samples;
}
void HeightFieldDescription::Samples::set( array<HeightFieldSample>^ value )
{
	SAFE_DELETE( _heightFieldDesc->samples );
	
	_samples = value;
	
	NxHeightFieldSample* samples;
	if( value != nullptr )
	{
		samples = new NxHeightFieldSample[ value->Length ];
		for( int x = 0; x < value->Length; x++ )
		{
			samples[ x ] = HeightFieldSample::ToUnmanaged( value[ x ] );
		}
	}else{
		samples = NULL;
	}
	
	_heightFieldDesc->samples = samples;
}

int HeightFieldDescription::SampleStrideSize::get()
{
	return _heightFieldDesc->sampleStride;
}

float HeightFieldDescription::Thickness::get()
{
	return _heightFieldDesc->thickness;
}
void HeightFieldDescription::Thickness::set( float value )
{
	_heightFieldDesc->thickness = value;
}

float HeightFieldDescription::ConvexEdgeThreshold::get()
{
	return _heightFieldDesc->convexEdgeThreshold;
}
void HeightFieldDescription::ConvexEdgeThreshold::set( float value )
{
	_heightFieldDesc->convexEdgeThreshold = value;
}

HeightFieldFlag HeightFieldDescription::Flags::get()
{
	return (HeightFieldFlag)_heightFieldDesc->flags;
}
void HeightFieldDescription::Flags::set( HeightFieldFlag value )
{
	_heightFieldDesc->flags = (NxHeightFieldFlags)value;
}

float HeightFieldDescription::VerticalExtent::get()
{
	return _heightFieldDesc->verticalExtent;
}
void HeightFieldDescription::VerticalExtent::set( float value )
{
	_heightFieldDesc->verticalExtent = value;
}

NxHeightFieldDesc* HeightFieldDescription::UnmanagedPointer::get()
{
	return _heightFieldDesc;
}