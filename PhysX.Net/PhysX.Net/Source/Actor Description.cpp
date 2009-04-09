#include "StdAfx.h"

#include "Actor Description.h"
#include "Actor.h"
#include "Shape.h"
#include "Capsule Shape.h"
#include "Plane Shape.h"
#include "Triangle Mesh Shape Description.h"
#include "Box Shape.h"
#include "Sphere Shape.h"
#include "Body Description.h"
#include "Math.h"
#include "Functions.h"
#include "Plane Shape Description.h"
#include "Sphere Shape Description.h"
#include "Box Shape Description.h"
#include "Capsule Shape Description.h"
#include "Triangle Mesh Shape.h"

using namespace StillDesign;
using namespace StillDesign::PhysX;

ActorDescription::ActorDescription()
{
	CreateActorDescription();
}
ActorDescription::ActorDescription( ... array<ShapeDescription^>^ shapeDescriptions )
{
	if( shapeDescriptions == nullptr )
		throw gcnew ArgumentNullException( "shapeDescriptions" );
	
	CreateActorDescription();
	
	for each( ShapeDescription^ desc in shapeDescriptions )
	{
		_shapes->Add( desc );
	}
}
ActorDescription::~ActorDescription()
{
	this->!ActorDescription();
}
ActorDescription::!ActorDescription()
{
	_shapes->ItemAdded -= gcnew EventHandlerItem<ShapeDescription^>( this, &ActorDescription::ShapeAdded );
	_shapes->ItemRemoved -= gcnew EventHandlerItem<ShapeDescription^>( this, &ActorDescription::ShapeRemoved );
	
	_shapes = nullptr;
}
void ActorDescription::CreateActorDescription()
{
	_shapes = gcnew ListBase<ShapeDescription^>();
	
	_shapes->ItemAdded += gcnew EventHandlerItem<ShapeDescription^>( this, &ActorDescription::ShapeAdded );
	_shapes->ItemRemoved += gcnew EventHandlerItem<ShapeDescription^>( this, &ActorDescription::ShapeRemoved );
}

bool ActorDescription::IsValid()
{
	return this->UnmanagedPointer->isValid() && IsMassDensityValid();
}
bool ActorDescription::IsMassDensityValid()
{
	NxActorDesc* desc = this->UnmanagedPointer;
	
	if( desc->body == NULL )
	{
		return true;
	}else{
		if( desc->density == 0.0f && desc->body->mass > 0.0f && desc->body->massSpaceInertia.magnitude() > 0.0f )
			return true;
		if( desc->density > 0.0f && desc->shapes.size() > 0 && desc->body->mass == 0.0f && desc->body->massSpaceInertia.magnitude() == 0.0f )
			return true;
		if( desc->density == 0.0f && desc->shapes.size() > 0 && desc->body->mass > 0.0f && desc->body->massSpaceInertia.magnitude() == 0.0f )
			return true;
	}
	
	return false;
}

void ActorDescription::ShapeAdded( Object^ sender, ShapeDescription^ e )
{
	if( e == nullptr )
		throw gcnew InvalidOperationException( "Cannot add a null shape description" );
	
	this->UnmanagedPointer->shapes.push_back( e->UnmanagedPointer );
}
void ActorDescription::ShapeRemoved( Object^ sender, ShapeDescription^ e )
{
	if( e == nullptr )
		throw gcnew InvalidOperationException( "Cannot remove a null shape description" );
	
	this->UnmanagedPointer->shapes.deleteEntry( e->UnmanagedPointer );
}


ListBase<ShapeDescription^>^ ActorDescription::Shapes::get()
{
	return _shapes;
}

NxActorDesc* ActorDescription::UnmanagedPointer::get()
{
	return (NxActorDesc*)ActorDescriptionBase::UnmanagedPointer::get();
}