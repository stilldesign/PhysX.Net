#include "StdAfx.h"

#include "Force Field Shape Group Description.h"
#include "Functions.h"
#include "Box Force Field Shape Description.h"
#include "Sphere Force Field Shape Description.h"
#include "Convex Force Field Shape Description.h"
#include "Capsule Force Field Shape Description.h"

#include <NxForceFieldShapeGroupDesc.h> 

using namespace StillDesign::PhysX;

ForceFieldShapeGroupDescription::ForceFieldShapeGroupDescription()
{
	_desc = new NxForceFieldShapeGroupDesc();
	
	_shapes = gcnew ForceFieldShapeDescriptionCollection();
}
ForceFieldShapeGroupDescription::ForceFieldShapeGroupDescription( NxForceFieldShapeGroupDesc* desc )
{
	Debug::Assert( desc != NULL );
	
	_desc = desc;
	
	for each( NxForceFieldShapeDesc* shapeDesc in desc->shapes )
	{
		ForceFieldShapeDescription^ s;
		
		switch( shapeDesc->getType() )
		{
			case NX_SHAPE_BOX:
			{
				s = gcnew BoxForceFieldShapeDescription( (NxBoxForceFieldShapeDesc*)shapeDesc );
			}
			break;
			case NX_SHAPE_SPHERE:
			{
				s = gcnew SphereForceFieldShapeDescription( (NxSphereForceFieldShapeDesc*)shapeDesc );
			}
			break;
			case NX_SHAPE_CONVEX:
			{
				s = gcnew ConvexForceFieldShapeDescription( (NxConvexForceFieldShapeDesc*)shapeDesc );
			}
			break;
			case NX_SHAPE_CAPSULE:
			{
				s = gcnew CapsuleForceFieldShapeDescription( (NxCapsuleForceFieldShapeDesc*)shapeDesc );
			}
			break;
			
			default: throw gcnew InvalidOperationException( "Invalid shape type" );
		}
		
		_shapes->Add( s );
	}
}
ForceFieldShapeGroupDescription::~ForceFieldShapeGroupDescription()
{
	this->!ForceFieldShapeGroupDescription();
}
ForceFieldShapeGroupDescription::!ForceFieldShapeGroupDescription()
{
	SAFE_DELETE( _desc );
	
	_shapes = nullptr;
	_userData = nullptr;
}

void ForceFieldShapeGroupDescription::SetToDefault()
{
	_desc->setToDefault();
	
	_shapes->Clear();
	
	_userData = nullptr;
}
bool ForceFieldShapeGroupDescription::IsValid()
{
	return _desc->isValid();
}

ForceFieldShapeGroupDescription::ForceFieldShapeDescriptionCollection^ ForceFieldShapeGroupDescription::Shapes::get()
{
	return _shapes;
}

String^ ForceFieldShapeGroupDescription::Name::get()
{
	return Functions::UnmanagedToManagedString( _desc->name );
}
void ForceFieldShapeGroupDescription::Name::set( String^ value )
{
	_desc->name = Functions::ManagedToUnmanagedString( value );
}

ForceFieldShapeGroupFlag ForceFieldShapeGroupDescription::Flags::get()
{
	return (ForceFieldShapeGroupFlag)_desc->flags;
}
void ForceFieldShapeGroupDescription::Flags::set( ForceFieldShapeGroupFlag value )
{
	_desc->flags = (NxU32)value;
}

Object^ ForceFieldShapeGroupDescription::UserData::get()
{
	return _userData;
}
void ForceFieldShapeGroupDescription::UserData::set( Object^ value )
{
	_userData = value;
}

NxForceFieldShapeGroupDesc* ForceFieldShapeGroupDescription::UnmanagedPointer::get()
{
	return _desc;
}