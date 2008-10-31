#include "StdAfx.h"

#include "Force Field Shape Group.h"
#include "Force Field.h"
#include "Functions.h"
#include "Force Field Shape Group Description.h"
#include "Force Field Shape Description.h"
#include "Box Force Field Shape.h"
#include "Sphere Force Field Shape.h"
#include "Capsule Force Field Shape.h"
#include "Convex Force Field Shape.h"
#include "Convex Force Field Shape Description.h"
#include "Scene.h"

using namespace System::Globalization;
using namespace StillDesign::PhysX;

ForceFieldShapeGroup::ForceFieldShapeGroup( NxForceFieldShapeGroup* group )
{
	Debug::Assert( group != NULL );
	
	ObjectCache::Add( (intptr_t)group, this );
	
	StillDesign::PhysX::Scene^ scene = ObjectCache::GetObject<StillDesign::PhysX::Scene^>( (intptr_t)(&group->getScene()) );
	
	_group = group;
	_forceField = nullptr;
	_scene = scene;
	
	_shapes = gcnew ElementCollection< ForceFieldShape^ >();
}
ForceFieldShapeGroup::~ForceFieldShapeGroup()
{
	this->!ForceFieldShapeGroup();
}
ForceFieldShapeGroup::!ForceFieldShapeGroup()
{
	if( this->IsDisposed == true )
		return;
	
	onDisposing( this, nullptr );
	
	_shapes->DiposeOfAll();
	
	_scene->UnmanagedPointer->releaseForceFieldShapeGroup( *_group );
	
	_group = NULL;
	
	_forceField = nullptr;
	_scene = nullptr;
	_shapes = nullptr;
	_userData = nullptr;
	
	onDisposed( this, nullptr );
}
bool ForceFieldShapeGroup::IsDisposed::get()
{
	return ( _group == NULL );
}

ForceFieldShapeGroupDescription^ ForceFieldShapeGroup::SaveToDescription()
{
	NxForceFieldShapeGroupDesc* desc = new NxForceFieldShapeGroupDesc();
	_group->saveToDesc( *desc );
	
	return gcnew ForceFieldShapeGroupDescription( desc );
}

ForceFieldShape^ ForceFieldShapeGroup::CreateShape( ForceFieldShapeDescription^ forceFieldShapeDescription )
{
	if( forceFieldShapeDescription == nullptr )
		throw gcnew ArgumentNullException( "forceFieldShapeDescription" );
	if( forceFieldShapeDescription->UnmanagedPointer == NULL )
		throw gcnew ArgumentException( "Description is disposed of" );
	if( forceFieldShapeDescription->IsValid() == false )
		throw gcnew ArgumentException( "Description is invalid" );
	
	NxForceFieldShape* shape = _group->createShape( *forceFieldShapeDescription->UnmanagedPointer );
	
	ForceFieldShape^ s;
	switch( shape->getType() )
	{
		case NX_SHAPE_BOX:
		{
			s = gcnew BoxForceFieldShape( shape->isBox() );
		}
		break;
		case NX_SHAPE_SPHERE:
		{
			s = gcnew SphereForceFieldShape( shape->isSphere() );
		}
		break;
		case NX_SHAPE_CAPSULE:
		{
			s = gcnew CapsuleForceFieldShape( shape->isCapsule() );
		}
		break;
		case NX_SHAPE_CONVEX:
		{
			ConvexMesh^ convexMesh = ((ConvexForceFieldShapeDescription^)forceFieldShapeDescription)->ConvexMesh;
			
			s = gcnew ConvexForceFieldShape( shape->isConvex(), convexMesh );
		}
		break;
		
		default:
			throw gcnew NotSupportedException( String::Format( CultureInfo::CurrentCulture, "Force field shape type not supported: '{0}'", forceFieldShapeDescription->Type ) );
	}
	
	_shapes->Add( s );
	
	return s;
}

StillDesign::PhysX::ForceField^ ForceFieldShapeGroup::ForceField::get()
{
	return _forceField;
}
void ForceFieldShapeGroup::ForceField::set( StillDesign::PhysX::ForceField^ value )
{
	_forceField = value;
}

StillDesign::PhysX::Scene^ ForceFieldShapeGroup::Scene::get()
{
	return _scene;
}

ReadOnlyList< ForceFieldShape^ >^ ForceFieldShapeGroup::Shapes::get()
{
	return _shapes->ReadOnlyCollection;
}

String^ ForceFieldShapeGroup::Name::get()
{
	return Functions::UnmanagedToManagedString( _group->getName() );
}
void ForceFieldShapeGroup::Name::set( String^ value )
{
	_group->setName( Functions::ManagedToUnmanagedString( value ) );
}

ForceFieldShapeGroupFlag ForceFieldShapeGroup::Flags::get()
{
	return (ForceFieldShapeGroupFlag)_group->getFlags();
}

Object^ ForceFieldShapeGroup::UserData::get()
{
	return _userData;
}
void ForceFieldShapeGroup::UserData::set( Object^ value )
{
	_userData = value;
}

NxForceFieldShapeGroup* ForceFieldShapeGroup::UnmanagedPointer::get()
{
	return _group;
}