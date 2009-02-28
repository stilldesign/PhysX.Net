#include "StdAfx.h"

#include "Force Field Kernel.h"

using namespace StillDesign::PhysX;

ForceFieldKernel::ForceFieldKernel( NxForceFieldKernel* kernel )
{
	Debug::Assert( kernel != NULL );
	
	ObjectCache::Add( (intptr_t)kernel, this );
	
	_kernel = kernel;
}
ForceFieldKernel::~ForceFieldKernel()
{
	this->!ForceFieldKernel();
}
ForceFieldKernel::!ForceFieldKernel()
{
	_kernel = NULL;
	
	_userData = nullptr;
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
	_userData = nullptr;
}

NxForceFieldKernel* ForceFieldKernel::UnmanagedPointer::get()
{
	return _kernel;
}