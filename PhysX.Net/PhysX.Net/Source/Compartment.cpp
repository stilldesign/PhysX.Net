#include "StdAfx.h"

#include "Compartment.h"
#include "Scene.h"
#include "Compartment Description.h"
#include "Scene Timing Information.h"

#include <NxCompartment.h> 

using namespace StillDesign::PhysX;

Compartment::Compartment( NxCompartment* compartment, StillDesign::PhysX::Scene^ scene )
{
	Debug::Assert( compartment != NULL );
	Debug::Assert( scene != nullptr );
	
	_compartment = compartment;
	
	_scene = scene;
	
	ObjectTable::Add( (intptr_t)_compartment, this );
}
Compartment::~Compartment()
{
	this->!Compartment();
}
Compartment::!Compartment()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_compartment = NULL;
	_scene = nullptr;
	
	OnDisposed( this, nullptr );
}

bool Compartment::IsDisposed::get()
{
	return ( _compartment == NULL );
}

CompartmentDescription^ Compartment::SaveToDescription()
{
	CompartmentDescription^ desc = gcnew CompartmentDescription();

	if( _compartment->saveToDesc( *desc->UnmanagedPointer ) == true )
		return desc;
	else
		return nullptr;
}

bool Compartment::CheckResults()
{
	return _compartment->checkResults();
}
bool Compartment::CheckResults( bool block )
{
	return _compartment->checkResults( block );
}

bool Compartment::FetchResults()
{
	return _compartment->fetchResults();
}
bool Compartment::FetchResults( bool block )
{
	return _compartment->fetchResults( block );
}

StillDesign::PhysX::Scene^ Compartment::Scene::get()
{
	return _scene;
}

CompartmentType Compartment::Type::get()
{
	return (CompartmentType)_compartment->getType();
}

StillDesign::PhysX::DeviceCode Compartment::DeviceCode::get()
{
	return (StillDesign::PhysX::DeviceCode)_compartment->getDeviceCode();
}

float Compartment::GridHashCellSize::get()
{
	return _compartment->getGridHashCellSize();
}

CompartmentFlag Compartment::Flags::get()
{
	return (CompartmentFlag)_compartment->getFlags();
}
void Compartment::Flags::set( CompartmentFlag value )
{
	_compartment->setFlags( (NxCompartmentFlag)value );
}

float Compartment::Timescale::get()
{
	return _compartment->getTimeScale();
}
void Compartment::Timescale::set( float value )
{
	_compartment->setTimeScale( value );
}

SceneTimingInformation Compartment::Timing::get()
{
	float maxTimestep;
	unsigned int maxIterations;
	NxTimeStepMethod timestepMethod;
	unsigned int subSteps;
	
	_compartment->getTiming( maxTimestep, maxIterations, timestepMethod, &subSteps );
	
	SceneTimingInformation timingInformation = SceneTimingInformation();
		timingInformation.MaximumTimestep = maxTimestep;
		timingInformation.MaximumIterations = (int)maxIterations;
		timingInformation.TimestepMethod = (TimestepMethod)timestepMethod;
		timingInformation.NumberOfSubSteps = (int)subSteps;
	
	return timingInformation;
}
void Compartment::Timing::set( SceneTimingInformation value )
{
	_compartment->setTiming( value.MaximumTimestep, value.MaximumIterations, (NxTimeStepMethod)value.TimestepMethod );
}

NxCompartment* Compartment::UnmanagedPointer::get()
{
	return _compartment;
}