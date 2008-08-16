#include "StdAfx.h"

#include "Actor Description.h"
#include "Actor.h"
#include "Base Shape.h"
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
	CreateActorDescription();
	
	_shapes->AddRange( shapeDescriptions );
}
ActorDescription::~ActorDescription()
{
	this->!ActorDescription();
}
ActorDescription::!ActorDescription()
{
	_shapes->onAdd -= gcnew EventHandlerItem< ShapeDescription^ >( this, &ActorDescription::ShapeAdded );
	_shapes-> onRemove -= gcnew EventHandlerItem< ShapeDescription^ >( this, &ActorDescription::ShapeRemoved );
	
	_shapes = nullptr;
}
void ActorDescription::CreateActorDescription()
{
	_shapes = gcnew ShapeDescription::ShapeDescriptionCollection();
	
	_shapes->onAdd += gcnew EventHandlerItem< ShapeDescription^ >( this, &ActorDescription::ShapeAdded );
	_shapes-> onRemove += gcnew EventHandlerItem< ShapeDescription^ >( this, &ActorDescription::ShapeRemoved );
}

DescriptorValidity^ ActorDescription::IsValid()
{
	NxActorDesc* desc = this->UnmanagedPointer;
	
	if( ActorDescriptionBase::IsValid() == false )
		return ActorDescriptionBase::IsValid();
	
	unsigned int nNonTriggerShapes = 0;
	
	// Static actors need nothing but a shape
	if (!desc->body && desc->shapes.size() > 0)
		return true;
	
	for (unsigned i = 0; i < desc->shapes.size(); i++)
	{
		if (!desc->shapes[i]->isValid())
			return false;
		if ((desc->shapes[i]->shapeFlags & NX_TRIGGER_ENABLE) == 0)
			nNonTriggerShapes++;
	}
	
	// If Actor is dynamic (body && !(body->flags & NX_BF_KINEMATIC) but has no solid shapes,
	// it has to have mass and massSpaceInertia, otherwise NxScene::createActor returns 0
	if (nNonTriggerShapes == 0 && desc->body && (!(desc->body->flags & NX_BF_KINEMATIC)) && (desc->body->mass < 0 || desc->body->massSpaceInertia.isZero()))
		return false;
	
	return desc->isValid();
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


ShapeDescription::ShapeDescriptionCollection^ ActorDescription::Shapes::get()
{
	return _shapes;
}