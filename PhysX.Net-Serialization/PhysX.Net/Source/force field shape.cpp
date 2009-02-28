#include "StdAfx.h"

#include "Force Field Shape.h"
#include "Functions.h"
#include "Math.h"
#include "Force Field.h"
#include "Force Field Shape Group.h"

#include <NxForceFieldShape.h> 

using namespace StillDesign::PhysX;

ForceFieldShape::ForceFieldShape( NxForceFieldShape* forceFieldShape )
{
	Debug::Assert( forceFieldShape != NULL );
	
	ObjectCache::Add( (intptr_t)forceFieldShape, this );
	
	_forceFieldShape = forceFieldShape;
	
	_group = ObjectCache::GetObject<ForceFieldShapeGroup^>( (intptr_t)(&forceFieldShape->getShapeGroup() ) );
}
ForceFieldShape::~ForceFieldShape()
{
	this->!ForceFieldShape();
}
ForceFieldShape::!ForceFieldShape()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_group->UnmanagedPointer->releaseShape( *_forceFieldShape );
	
	_forceFieldShape = NULL;
	_group = nullptr;
	
	OnDisposed( this, nullptr );
}
bool ForceFieldShape::IsDisposed::get()
{
	return ( _forceFieldShape == NULL );
}

ForceFieldShapeGroup^ ForceFieldShape::ShapeGroup::get()
{
	return _group;
}

String^ ForceFieldShape::Name::get()
{
	return Functions::UnmanagedToManagedString( _forceFieldShape->getName() );
}
void ForceFieldShape::Name::set( String^ value )
{
	_forceFieldShape->setName( Functions::ManagedToUnmanagedString( value ) );
}
ShapeType ForceFieldShape::Type::get()
{
	return (ShapeType)_forceFieldShape->getType();
}

Matrix ForceFieldShape::Pose::get()
{
	return StillDesign::PhysX::Math::Mat34ToMatrix( &_forceFieldShape->getPose() );
}
void ForceFieldShape::Pose::set( Matrix value )
{
	_forceFieldShape->setPose( StillDesign::PhysX::Math::MatrixToMat34( value ) );
}

Object^ ForceFieldShape::UserData::get()
{
	return _userData;
}
void ForceFieldShape::UserData::set( Object^ value )
{
	_userData = value;
}

NxForceFieldShape* ForceFieldShape::UnmanagedPointer::get()
{
	return _forceFieldShape;
}