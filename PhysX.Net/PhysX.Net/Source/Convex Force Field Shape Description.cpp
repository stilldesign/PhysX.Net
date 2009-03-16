#include "StdAfx.h"

#include "Convex Force Field Shape Description.h"
#include "Mesh Data.h"
#include "Core.h"
#include "Convex Mesh.h"

using namespace StillDesign::PhysX;

UsingFrameworkNamespace

ConvexForceFieldShapeDescription::ConvexForceFieldShapeDescription() : ForceFieldShapeDescription( new NxConvexForceFieldShapeDesc() )
{
	
}
ConvexForceFieldShapeDescription::ConvexForceFieldShapeDescription( NxConvexForceFieldShapeDesc* desc ) : ForceFieldShapeDescription( desc )
{
	if( desc->meshData != NULL )
		_convexMesh = ObjectTable::GetObject<StillDesign::PhysX::ConvexMesh^>( (intptr_t)desc->meshData );
}

void ConvexForceFieldShapeDescription::SetToDefault()
{
	this->UnmanagedPointer->setToDefault();
	
	_convexMesh = nullptr;
}
bool ConvexForceFieldShapeDescription::IsValid()
{
	return this->UnmanagedPointer->isValid();
}

StillDesign::PhysX::ConvexMesh^ ConvexForceFieldShapeDescription::ConvexMesh::get()
{
	return _convexMesh;
}
void ConvexForceFieldShapeDescription::ConvexMesh::set( StillDesign::PhysX::ConvexMesh^ value )
{
	_convexMesh = value;
	
	if( value == nullptr )
		this->UnmanagedPointer->meshData = NULL;
	else
		this->UnmanagedPointer->meshData = value->UnmanagedPointer;
}

NxConvexForceFieldShapeDesc* ConvexForceFieldShapeDescription::UnmanagedPointer::get()
{
	return (NxConvexForceFieldShapeDesc*)ForceFieldShapeDescription::UnmanagedPointer;
}