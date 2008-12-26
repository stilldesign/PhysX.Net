#include "StdAfx.h"

#include "CCD Skeleton.h"
#include "Simple Triangle Mesh.h"
#include "Core.h"

#include <NxCCDSkeleton.h> 

using namespace System;
using namespace StillDesign::PhysX;

CCDSkeleton::CCDSkeleton( NxCCDSkeleton* skeleton, StillDesign::PhysX::Core^ core )
{
	Debug::Assert( skeleton != NULL );
	Debug::Assert( core != nullptr );
	
	ObjectCache::Add( (intptr_t)skeleton, this );
	
	_skeleton = skeleton;
	
	_core = core;
}
CCDSkeleton::~CCDSkeleton()
{
	this->!CCDSkeleton();
}
CCDSkeleton::!CCDSkeleton()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_core->UnmanagedPointer->releaseCCDSkeleton( *_skeleton );
	_skeleton = NULL;
	
	_core = nullptr;
	
	OnDisposed( this, nullptr );
}
bool CCDSkeleton::IsDisposed::get()
{
	return ( _skeleton == NULL );
}

array<Byte>^ CCDSkeleton::Save()
{
	int size = this->DataSize;
	
	if( size == 0 )
		return nullptr;
	
	array<Byte>^ buffer = gcnew array<Byte>( size );
	
	BYTE* b = new BYTE[ size ];
	if( b == NULL )
		return nullptr;
	
	int savedSize = _skeleton->save( b, size );
	
	if( savedSize != size )
		return nullptr;
	
	for( int x = 0; x < size; x++ )
	{
		buffer[ x ] = b[ x ];
	}
	
	delete[] b;
	b = NULL;
	
	return buffer;
}

StillDesign::PhysX::Core^ CCDSkeleton::Core::get()
{
	return _core;
}

String^ CCDSkeleton::Name::get()
{
	return _name;
}
void CCDSkeleton::Name::set( String^ value )
{
	_name = value;
}

int CCDSkeleton::ReferencedCount::get()
{
	return _skeleton->getReferenceCount();
}
int CCDSkeleton::DataSize::get()
{
	return _skeleton->getDataSize();
}

NxCCDSkeleton* CCDSkeleton::UnmanagedPointer::get()
{
	return _skeleton;
}