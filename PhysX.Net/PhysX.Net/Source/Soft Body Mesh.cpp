#include "StdAfx.h"

#include "Soft Body Mesh.h"
#include "Soft Body Mesh Description.h"
#include "Core.h"

#include <NxSoftBodyMesh.h> 

using namespace System;
using namespace StillDesign::PhysX;

SoftBodyMesh::SoftBodyMesh( NxSoftBodyMesh* softBodyMesh, StillDesign::PhysX::Core^ core )
{
	Debug::Assert( softBodyMesh != NULL );
	Debug::Assert( core != nullptr );
	
	ObjectCache::Add( (intptr_t)softBodyMesh, this );
	
	_softBodyMesh = softBodyMesh;
	
	_core = core;
}
SoftBodyMesh::~SoftBodyMesh()
{
	this->!SoftBodyMesh();
}
SoftBodyMesh::!SoftBodyMesh()
{
	if( this->IsDisposed == true )
		return;
	
	onDisposing( this, nullptr );
	
	_core->UnmanagedPointer->releaseSoftBodyMesh( *_softBodyMesh );
	
	_softBodyMesh = NULL;
	
	_core = nullptr;
	
	onDisposed( this, nullptr );
}
bool SoftBodyMesh::IsDisposed::get()
{
	return ( _softBodyMesh == NULL );
}

SoftBodyMeshDescription^ SoftBodyMesh::SaveToDescription()
{
	NxSoftBodyMeshDesc* d = new NxSoftBodyMeshDesc();
	
	if( _softBodyMesh->saveToDesc( *d ) == false )
	{
		delete d;
		return nullptr;
	}
	
	return gcnew SoftBodyMeshDescription( d );
}

StillDesign::PhysX::Core^ SoftBodyMesh::Core::get()
{
	return _core;
}

String^ SoftBodyMesh::Name::get()
{
	return _name;
}
void SoftBodyMesh::Name::set( String^ value )
{
	_name = value;
}

int SoftBodyMesh::ReferencedCount::get()
{
	return _softBodyMesh->getReferenceCount();
}

NxSoftBodyMesh* SoftBodyMesh::UnmanagedPointer::get()
{
	return _softBodyMesh;
}