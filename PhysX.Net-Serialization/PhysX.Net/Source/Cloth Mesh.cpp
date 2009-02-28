#include "StdAfx.h"

#include "Cloth Mesh.h"
#include "Functions.h"
#include "Core.h"
#include "Cloth Mesh Description.h"
#include "PhysX Exception.h"

#include <NxClothMesh.h> 

using namespace System;
using namespace StillDesign::PhysX;

ClothMesh::ClothMesh( NxClothMesh* clothMesh, StillDesign::PhysX::Core^ core )
{
	Debug::Assert( clothMesh != NULL );
	Debug::Assert( core != nullptr );
	
	ObjectCache::Add( (intptr_t)clothMesh, this );
	
	_clothMesh = clothMesh;
	_core = core;
}
ClothMesh::~ClothMesh()
{
	this->!ClothMesh();
}
ClothMesh::!ClothMesh()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_core->UnmanagedPointer->releaseClothMesh( *_clothMesh );
	
	_clothMesh = NULL;
	_core = nullptr;
	
	OnDisposed( this, nullptr );
}
bool ClothMesh::IsDisposed::get()
{
	return ( _clothMesh == NULL );
}

ClothMeshDescription^ ClothMesh::SaveToDescription()
{
	NxClothMeshDesc* desc = new NxClothMeshDesc();
		if( _clothMesh->saveToDesc( *desc ) == false )
		{
			delete desc;
			throw gcnew PhysXException( "Could not save cloth mesh description" );
		}
		
		int trianglesSize = desc->triangleStrideBytes * desc->numTriangles;
		int pointsSize = desc->pointStrideBytes * desc->numVertices;
		
		void* t = malloc( trianglesSize );
		void* v = malloc( pointsSize );
		
		desc->triangles = memcpy( t, desc->triangles, trianglesSize );
		desc->points = memcpy( v, desc->points, pointsSize );
	
	ClothMeshDescription^ clothMeshDesc = gcnew ClothMeshDescription( desc );
		clothMeshDesc->Name = this->Name;
	
	return clothMeshDesc;
}

StillDesign::PhysX::Core^ ClothMesh::Core::get()
{
	return _core;
}

String^ ClothMesh::Name::get()
{
	return _name;
}
void ClothMesh::Name::set( String^ value )
{
	_name = value;
}

int ClothMesh::ReferencedCount::get()
{
	return _clothMesh->getReferenceCount();
}

NxClothMesh* ClothMesh::UnmanagedPointer::get()
{
	return _clothMesh;
}