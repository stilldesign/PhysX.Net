#include "StdAfx.h"

#include "Force Field Description.h"
#include "Groups Mask.h"
#include "Functions.h"
#include "Math.h"
#include "Actor.h"
#include "Force Field Kernel.h"

#include <NxForceFieldDesc.h> 

using namespace StillDesign::PhysX;

ForceFieldDescription::ForceFieldDescription()
{
	_forceFieldDesc = new NxForceFieldDesc();
	
	CreateAux();
}
ForceFieldDescription::ForceFieldDescription( NxForceFieldDesc* forceFieldDesc )
{
	Debug::Assert( forceFieldDesc != NULL );
	
	_forceFieldDesc = forceFieldDesc;
	
	CreateAux();
	
	if( forceFieldDesc->actor != NULL )
		_actor = ObjectCache::GetObject<StillDesign::PhysX::Actor^>( (intptr_t)forceFieldDesc->actor );
	if( forceFieldDesc->kernel != NULL )
		_kernel = ObjectCache::GetObject<ForceFieldKernel^>( (intptr_t)forceFieldDesc->kernel );
	
	for each( NxForceFieldShapeGroup* group in forceFieldDesc->shapeGroups )
	{
		_groups->Add( gcnew ForceFieldShapeGroup( group ) );
	}
}
ForceFieldDescription::~ForceFieldDescription()
{
	this->!ForceFieldDescription();
}
ForceFieldDescription::!ForceFieldDescription()
{
	if( this->IsDisposed == true )
		return;
	
	onDisposing( this, nullptr );
	
	SAFE_DELETE( _forceFieldDesc );
	
	_actor = nullptr;
	
	onDisposed( this, nullptr );
}
bool ForceFieldDescription::IsDisposed::get()
{
	return ( _forceFieldDesc == NULL );
}
void ForceFieldDescription::CreateAux()
{
	_groups = gcnew ForceFieldShapeGroupCollection();
		_groups->ItemAdded += gcnew EventHandlerItem<ForceFieldShapeGroup^>( this, &ForceFieldDescription::_group_onAdd );
		_groups->ItemRemoved += gcnew EventHandlerItem<ForceFieldShapeGroup^>( this, &ForceFieldDescription::_group_onRemove );
		
	_shapeDescriptions = gcnew ForceFieldShapeDescriptionCollection();
		_shapeDescriptions->ItemAdded += gcnew EventHandlerItem<ForceFieldShapeDescription^>( this, &ForceFieldDescription::_shapeDescriptions_onAdd );
		_shapeDescriptions->ItemRemoved += gcnew EventHandlerItem<ForceFieldShapeDescription^>( this, &ForceFieldDescription::_shapeDescriptions_onRemove );
}

void ForceFieldDescription::SetToDefault()
{
	_forceFieldDesc->setToDefault();
	
	_actor = nullptr;
	_kernel = nullptr;
	_groups->Clear();
	_shapeDescriptions->Clear();
	
	_userData = nullptr;
}
bool ForceFieldDescription::IsValid()
{
	return _forceFieldDesc->isValid();
}

void ForceFieldDescription::_group_onAdd( Object^ sender, ForceFieldShapeGroup^ e )
{
	if( e == nullptr )
		throw gcnew InvalidOperationException( "Cannot add a null force field shape group" );
	
	_forceFieldDesc->shapeGroups.push_back( e->UnmanagedPointer );
}
void ForceFieldDescription::_group_onRemove( Object^ sender, ForceFieldShapeGroup^ e )
{
	if( e == nullptr )
		throw gcnew InvalidOperationException( "Cannot remove a null force field shape group" );
	
	_forceFieldDesc->shapeGroups.deleteEntry( e->UnmanagedPointer );
}

void ForceFieldDescription::_shapeDescriptions_onAdd( Object^ sender, ForceFieldShapeDescription^ e )
{
	if( e == nullptr )
		throw gcnew InvalidOperationException( "Cannot add a null force field shape description" );
	
	_forceFieldDesc->includeGroupShapes.push_back( e->UnmanagedPointer );
}
void ForceFieldDescription::_shapeDescriptions_onRemove( Object^ sender, ForceFieldShapeDescription^ e )
{
	if( e == nullptr )
		throw gcnew InvalidOperationException( "Cannot remove a null force field shape description" );
	
	_forceFieldDesc->includeGroupShapes.deleteEntry( e->UnmanagedPointer );
}

ForceFieldKernel^ ForceFieldDescription::Kernel::get()
{
	return _kernel;
}
void ForceFieldDescription::Kernel::set( ForceFieldKernel^ value )
{
	_kernel = value;
	
	if( value == nullptr )
		_forceFieldDesc->kernel = NULL;
	else
		_forceFieldDesc->kernel = value->UnmanagedPointer;
}

ForceFieldDescription::ForceFieldShapeGroupCollection^ ForceFieldDescription::ShapeGroups::get()
{
	return _groups;
}
ForceFieldDescription::ForceFieldShapeDescriptionCollection^ ForceFieldDescription::IncludeGroupShapes::get()
{
	return _shapeDescriptions;
}

short ForceFieldDescription::ForceFieldVariety::get()
{
	return _forceFieldDesc->forceFieldVariety;
}
void ForceFieldDescription::ForceFieldVariety::set( short value )
{
	_forceFieldDesc->forceFieldVariety = value;
}

StillDesign::PhysX::Actor^ ForceFieldDescription::Actor::get()
{
	return _actor;
}
void ForceFieldDescription::Actor::set( StillDesign::PhysX::Actor^ value )
{
	_actor = value;
	
	if( value == nullptr )
		_forceFieldDesc->actor = NULL;
	else
		_forceFieldDesc->actor = value->UnmanagedPointer;
}

String^ ForceFieldDescription::Name::get()
{
	return StillDesign::PhysX::Functions::UnmanagedToManagedString( _forceFieldDesc->name );
}
void ForceFieldDescription::Name::set( String^ value )
{
	_forceFieldDesc->name = StillDesign::PhysX::Functions::ManagedToUnmanagedString( value );
}

Matrix ForceFieldDescription::Pose::get()
{
	return Math::Mat34ToMatrix( &_forceFieldDesc->pose );
}
void ForceFieldDescription::Pose::set( Matrix value )
{
	_forceFieldDesc->pose = Math::MatrixToMat34( value );
}

ForceFieldCoordinate ForceFieldDescription::Coordinates::get()
{
	return (ForceFieldCoordinate)_forceFieldDesc->coordinates;
}
void ForceFieldDescription::Coordinates::set( ForceFieldCoordinate value )
{
	_forceFieldDesc->coordinates = (NxForceFieldCoordinates)value;
}

short ForceFieldDescription::Group::get()
{
	return _forceFieldDesc->group;
}
void ForceFieldDescription::Group::set( short value )
{
	_forceFieldDesc->group = value;
}
StillDesign::PhysX::GroupsMask ForceFieldDescription::GroupsMask::get()
{
	return (StillDesign::PhysX::GroupsMask)_forceFieldDesc->groupsMask;
}
void ForceFieldDescription::GroupsMask::set( StillDesign::PhysX::GroupsMask value )
{
	_forceFieldDesc->groupsMask = (NxGroupsMask)value;
}

ForceFieldType ForceFieldDescription::FluidType::get()
{
	return (ForceFieldType)_forceFieldDesc->fluidType;
}
void ForceFieldDescription::FluidType::set( ForceFieldType value )
{
	_forceFieldDesc->fluidType = (NxForceFieldType)value;
}
ForceFieldType ForceFieldDescription::ClothType::get()
{
	return (ForceFieldType)_forceFieldDesc->clothType;
}
void ForceFieldDescription::ClothType::set( ForceFieldType value )
{
	_forceFieldDesc->clothType = (NxForceFieldType)value;
}
ForceFieldType ForceFieldDescription::SoftBodyType::get()
{
	return (ForceFieldType)_forceFieldDesc->softBodyType;
}
void ForceFieldDescription::SoftBodyType::set( ForceFieldType value )
{
	_forceFieldDesc->softBodyType = (NxForceFieldType)value;
}
ForceFieldType ForceFieldDescription::RigidBodyType::get()
{
	return (ForceFieldType)_forceFieldDesc->rigidBodyType;
}
void ForceFieldDescription::RigidBodyType::set( ForceFieldType value )
{
	_forceFieldDesc->rigidBodyType = (NxForceFieldType)value;
}

Object^ ForceFieldDescription::UserData::get()
{
	return _userData;
}
void ForceFieldDescription::UserData::set( Object^ value )
{
	_userData = value;
}

NxForceFieldDesc* ForceFieldDescription::UnmanagedPointer::get()
{
	return _forceFieldDesc;
}