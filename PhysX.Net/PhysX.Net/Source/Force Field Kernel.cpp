#include "StdAfx.h"

#include "Force Field Kernel.h"

using namespace StillDesign::PhysX;

ForceFieldKernel::ForceFieldKernel( NxForceFieldKernel* kernel )
{
	Debug::Assert( kernel != NULL );
	
	ObjectTable::Add( (intptr_t)kernel, this );
	
	_kernel = kernel;
}
ForceFieldKernel::~ForceFieldKernel()
{
	this->!ForceFieldKernel();
}
ForceFieldKernel::!ForceFieldKernel()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_kernel = NULL;
	
	_userData = nullptr;
	
	OnDisposed( this, nullptr );
}
bool ForceFieldKernel::IsDisposed::get()
{
	return ( _kernel == NULL );
}

Object^ ForceFieldKernel::UserData::get()
{
	return _userData;
}
void ForceFieldKernel::UserData::set( Object^ value )
{
	_userData = value;
}

NxForceFieldKernel* ForceFieldKernel::UnmanagedPointer::get()
{
	return _kernel;
}