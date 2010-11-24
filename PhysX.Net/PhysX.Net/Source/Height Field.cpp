#include "StdAfx.h"

#include "Height Field.h"
#include "Height Field Description.h"
#include "Core.h"
#include "Height Field Sample.h"

using namespace StillDesign::PhysX;

HeightField::HeightField( NxHeightField* heightField, StillDesign::PhysX::Core^ core )
{
	Debug::Assert( heightField != NULL );
	Debug::Assert( core != nullptr );
	
	ObjectTable::Add( (intptr_t)heightField, this );
	
	_heightField = heightField;
	
	_core = core;
}
HeightField::~HeightField()
{
	this->!HeightField();
}
HeightField::!HeightField()
{
	if( this->IsDisposed )
		return;
	
	OnDisposing( this, nullptr );
	
	_core->UnmanagedPointer->releaseHeightField( *_heightField );
	
	_heightField = NULL;
	_core = nullptr;
	
	OnDisposed( this, nullptr );
}

bool HeightField::IsDisposed::get()
{
	return ( _heightField == NULL );
}

HeightFieldDescription^ HeightField::SaveToDescription()
{
	HeightFieldDescription^ desc = gcnew HeightFieldDescription();
	
	if( _heightField->saveToDesc( *desc->UnmanagedPointer ) == false )
	{
		delete desc;
		return nullptr;
	}
	
	return desc;
}
bool HeightField::LoadFromDescription( HeightFieldDescription^ description )
{
	ThrowIfNull( description, "description" );
	
	return _heightField->loadFromDesc( *description->UnmanagedPointer );
}

array<HeightFieldSample>^ HeightField::SaveCells()
{
	int sampleCount = this->NumberOfRows * this->NumberOfColumns;
	
	if( sampleCount == 0 )
		return gcnew array<HeightFieldSample>( 0 );
	
	array<HeightFieldSample>^ samples = nullptr;
	
	NxHeightFieldSample* s = new NxHeightFieldSample[ sampleCount ];
	Debug::Assert( s != NULL );
	
	int byteSize = sizeof( NxHeightFieldSample ) * sampleCount;
	if( _heightField->saveCells( s, byteSize ) != byteSize )
		goto Finished;
	
	samples = gcnew array<HeightFieldSample>( sampleCount );
	
	for( int x = 0; x < sampleCount; x++ )
	{
		samples[ x ] = HeightFieldSample::FromUnmanaged( &s[ x ] );
	}
	
	Finished:
	delete[] s;
	s = NULL;
	
	return samples;
}

StillDesign::PhysX::Core^ HeightField::Core::get()
{
	return _core;
}

String^ HeightField::Name::get()
{
	return _name;
}
void HeightField::Name::set( String^ value )
{
	_name = value;
}

float HeightField::GetHeight( float x, float z )
{
	return _heightField->getHeight( x, z );
}

int HeightField::NumberOfRows::get()
{
	return _heightField->getNbRows();
}
int HeightField::NumberOfColumns::get()
{
	return _heightField->getNbColumns();
}
HeightFieldFormat HeightField::Format::get()
{
	return (HeightFieldFormat)_heightField->getFormat();
}

float HeightField::Thickness::get()
{
	return _heightField->getThickness();
}
float HeightField::ConvexEdgeThreshold::get()
{
	return _heightField->getConvexEdgeThreshold();
}
HeightFieldFlag HeightField::Flags::get()
{
	return (HeightFieldFlag)_heightField->getFlags();
}

int HeightField::ReferencedCount::get()
{
	return _heightField->getReferenceCount();
}

NxHeightField* HeightField::UnmanagedPointer::get()
{
	return _heightField;
}