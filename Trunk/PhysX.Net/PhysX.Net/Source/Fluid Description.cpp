#include "StdAfx.h"

#include "Fluid Description.h"
#include "Fluid Emitter Description.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

FluidDescription::FluidDescription( NxFluidDesc* desc ) : FluidDescriptionBase( desc )
{
	CreateFluidDescription();
	
	for( unsigned int x = 0; x < desc->emitters.size(); x++ )
	{
		NxFluidEmitterDesc* emitterDesc = new NxFluidEmitterDesc();
			*emitterDesc = desc->emitters[ x ];
		
		FluidEmitterDescription^ e = gcnew FluidEmitterDescription( emitterDesc );
			e->UserData = this->UserData;
		
		_emitters->Add( e );
	}
}
FluidDescription::FluidDescription() : FluidDescriptionBase( new NxFluidDesc() )
{
	CreateFluidDescription();
}
FluidDescription::~FluidDescription()
{
	this->!FluidDescription();
}
FluidDescription::!FluidDescription()
{
	
}
void FluidDescription::CreateFluidDescription()
{
	_emitters = gcnew ListBase< FluidEmitterDescription^ >();
		_emitters->ItemAdded += gcnew EventHandlerItem<FluidEmitterDescription^>( this, &FluidDescription::FluidEmitterDescriptionAdded );
		_emitters->ItemRemoved += gcnew EventHandlerItem<FluidEmitterDescription^>( this, &FluidDescription::FluidEmitterDescriptionRemoved );
}

void FluidDescription::SetToDefault()
{
	this->UnmanagedPointer->setToDefault();
	
	_emitters->Clear();
}
bool FluidDescription::IsValid()
{
	return this->UnmanagedPointer->isValid();
}

ListBase< FluidEmitterDescription^ >^ FluidDescription::Emitters::get()
{
	return _emitters;
}

NxFluidDesc* FluidDescription::UnmanagedPointer::get()
{
	return (NxFluidDesc*)FluidDescriptionBase::UnmanagedPointer;
}

void FluidDescription::FluidEmitterDescriptionAdded( System::Object^ sender, FluidEmitterDescription^ e )
{
	NxFluidDesc* desc = this->UnmanagedPointer;
	
	desc->emitters.pushBack( *e->UnmanagedPointer );
}
void FluidDescription::FluidEmitterDescriptionRemoved( System::Object^ sender, FluidEmitterDescription^ e )
{
	//this->UnmanagedPointer->emitters.deleteEntry( *e->UnmanagedPointer );
	//
	for( unsigned int x = 0; x < this->UnmanagedPointer->emitters.size(); x++ )
	{
		if( &this->UnmanagedPointer->emitters[ x ] == e->UnmanagedPointer )
		{
			NxArray<NxFluidEmitterDesc, NxAllocatorDefault>::Iterator from = &this->UnmanagedPointer->emitters[ x ];
			
			if( x < this->UnmanagedPointer->emitters.size() - 1 )
			{
				NxArray<NxFluidEmitterDesc, NxAllocatorDefault>::Iterator to = &this->UnmanagedPointer->emitters[ x + 1 ];
				
				this->UnmanagedPointer->emitters.erase( from, to );
			}else{
				this->UnmanagedPointer->emitters.erase( from );
			}
			
			break;
		}
	}
}