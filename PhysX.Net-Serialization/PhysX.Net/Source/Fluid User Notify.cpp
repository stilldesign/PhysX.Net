#include "StdAfx.h"

#include "Fluid User Notify.h"
#include "Scene.h"
#include "Fluid.h"
#include "Fluid Emitter.h"

using namespace StillDesign::PhysX;

FluidUserNotify::FluidUserNotify( )
{
	_fluidUserNotify = new InternalFluidUserNotify( this );
}
FluidUserNotify::~FluidUserNotify()
{
	this->!FluidUserNotify();
}
FluidUserNotify::!FluidUserNotify()
{
	SAFE_DELETE( _fluidUserNotify );
}

InternalFluidUserNotify* FluidUserNotify::UnmanagedPointer::get()
{
	return _fluidUserNotify;
}

//

InternalFluidUserNotify::InternalFluidUserNotify( gcroot<FluidUserNotify^> fluidUserNotify )
{
	_fluidUserNotify = fluidUserNotify;
}

bool InternalFluidUserNotify::onEmitterEvent( NxFluidEmitter &emitter, NxFluidEmitterEventType eventType )
{
	Fluid^ fluid = ObjectCache::GetObject<Fluid^>( (intptr_t)(&emitter.getFluid()) );
	
	FluidEmitter^ fluidEmitter = ObjectCache::GetObject<FluidEmitter^>( (intptr_t)(&emitter) );
	
	return _fluidUserNotify->OnEmitterEvent( fluidEmitter, (FluidEmitterEventType)eventType );
}
bool InternalFluidUserNotify::onEvent( NxFluid &fluid, NxFluidEventType eventType )
{
	Fluid^ f = ObjectCache::GetObject<Fluid^>( (intptr_t)(&fluid) );
	
	return _fluidUserNotify->OnEvent( f, (FluidEventType)eventType );
}