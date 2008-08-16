#include "StdAfx.h"

#include "Joint Description.h"
#include "Actor.h"

#include "Cylindrical Joint Description.h"
#include "D6 Joint Description.h"
#include "Prismatic Joint Description.h"
#include "Revolute Joint Description.h"
#include "Spherical Joint Description.h"
#include "Point On Line Joint Description.h"
#include "Point In Plane Joint Description.h"
#include "Distance Joint Description.h"
#include "Pulley Joint Description.h"
#include "Fixed Joint Description.h"

using namespace StillDesign::PhysX;

JointDescription::JointDescription( NxJointDesc* jointDesc )
{
	Debug::Assert( jointDesc != NULL );
	
	_desc = jointDesc;
	
	if( jointDesc->actor[ 0 ] != NULL )
		_actor1 = ObjectCache::GetObject<Actor^>( (intptr_t)jointDesc->actor[ 0 ] );
	if( jointDesc->actor[ 1 ] != NULL )
		_actor2 = ObjectCache::GetObject<Actor^>( (intptr_t)jointDesc->actor[ 1 ] );
}
JointDescription::~JointDescription()
{
	this->!JointDescription();
}
JointDescription::!JointDescription()
{
	SAFE_DELETE( _desc );
	
	_actor1 = nullptr;
	_actor2 = nullptr;
	
	_userData = nullptr;
}

DescriptorValidity^ JointDescription::IsValid()
{
	NxJointDesc* desc = this->UnmanagedPointer;
	
	if (desc->actor[0] == desc->actor[1])
		return DescriptorValidity::Invalid( "Actor1 cannot equal Actor2" );
	
	if (!(desc->actor[0] || desc->actor[1]))
		return DescriptorValidity::Invalid( "Actor1 and Actor2 are not set" );
	
	//non-null pointers must be dynamic:
	if (desc->actor[0] && ! desc->actor[0]->isDynamic())
		return DescriptorValidity::Invalid( "Actor1 is not dynamic" );
	if (desc->actor[1] && ! desc->actor[1]->isDynamic())
		return DescriptorValidity::Invalid( "Actor2 is not dynamic" );
	
	if (desc->getType() >= NX_JOINT_COUNT)
		return DescriptorValidity::Invalid( "Invalid Type" );
	
	for (int i=0; i<2; i++)
	{
		if (fabsf(desc->localAxis[i].magnitudeSquared() - 1.0f) > 0.1f)
			return DescriptorValidity::Invalid( "Local axis length(s) are invalid" );
		
		if (fabsf(desc->localNormal[i].magnitudeSquared() - 1.0f) > 0.1f)
			return DescriptorValidity::Invalid( "Local normal length(s) are invalid" );
			
		//check orthogonal pairs
		if (fabsf(desc->localAxis[i].dot(desc->localNormal[i])) > 0.1f)
			return DescriptorValidity::Invalid( "Local axis and local normals are not orthogonal" );
	}
	if (desc->maxForce <= 0)
		return DescriptorValidity::Invalid( "Maximum force must be greater than 0" );
	if (desc->maxTorque <= 0)
		return DescriptorValidity::Invalid( "Maximum torque must be greater than 0" );
	
	return desc->isValid();
}
void JointDescription::SetToDefault()
{
	_desc->setToDefault();
	
	_actor1 = nullptr;
	_actor2 = nullptr;
	
	_name = nullptr;
	
	_userData = nullptr;
}

void JointDescription::SetGlobalAnchor( Vector3 anchor )
{
	_desc->setGlobalAnchor( Math::Vector3ToNxVec3( anchor ) );
}
void JointDescription::SetGlobalAxis( Vector3 axis )
{
	_desc->setGlobalAxis( Math::Vector3ToNxVec3( axis ) );
}

void JointDescription::_actor1_onDisposed( System::Object^ sender, EventArgs^ e )
{
	_actor1 = nullptr;
}
void JointDescription::_actor2_onDisposed( System::Object^ sender, EventArgs^ e )
{
	_actor2 = nullptr;
}

NxJointDesc* JointDescription::CopyToUnmanagedPointer( NxJointDesc* desc )
{
	NxJointDesc* d;
	
	switch( desc->getType() )
	{
		case NX_JOINT_CYLINDRICAL:
			d = new NxCylindricalJointDesc();
			*(NxCylindricalJointDesc*)d = *(NxCylindricalJointDesc*)desc;
		break;
		case NX_JOINT_D6:
			d = new NxD6JointDesc();
			*(NxD6JointDesc*)d = *(NxD6JointDesc*)desc;
		break;
		case NX_JOINT_PRISMATIC:
			d = new NxPrismaticJointDesc();
			*(NxPrismaticJointDesc*)d = *(NxPrismaticJointDesc*)desc;
		break;
		case NX_JOINT_REVOLUTE:
			d = new NxRevoluteJointDesc();
			*(NxRevoluteJointDesc*)d = *(NxRevoluteJointDesc*)desc;
		break;
		case NX_JOINT_SPHERICAL:
			d = new NxSphericalJointDesc();
			*(NxSphericalJointDesc*)d = *(NxSphericalJointDesc*)desc;
		break;
		case NX_JOINT_POINT_ON_LINE:
			d = new NxPointOnLineJointDesc();
			*(NxPointOnLineJointDesc*)d = *(NxPointOnLineJointDesc*)desc;
		break;
		case NX_JOINT_POINT_IN_PLANE:
			d = new NxPointInPlaneJointDesc();
			*(NxPointInPlaneJointDesc*)d = *(NxPointInPlaneJointDesc*)desc;
		break;
		case NX_JOINT_DISTANCE:
			d = new NxDistanceJointDesc();
			*(NxDistanceJointDesc*)d = *(NxDistanceJointDesc*)desc;
		break;
		case NX_JOINT_PULLEY:
			d = new NxPulleyJointDesc();
			*(NxPulleyJointDesc*)d = *(NxPulleyJointDesc*)desc;
		break;
		case NX_JOINT_FIXED:
			d = new NxFixedJointDesc();
			*(NxFixedJointDesc*)d = *(NxFixedJointDesc*)desc;
		break;
		
		default: throw gcnew ApplicationException( "Invalid joint type" );
	}
	
	return d;
}
JointDescription^ JointDescription::CopyToManagedReference( NxJointDesc* desc )
{
	NxJointDesc* d = CopyToUnmanagedPointer( desc );
	
	switch( desc->getType() )
	{
		case NX_JOINT_CYLINDRICAL:
			return gcnew CylindricalJointDescription( (NxCylindricalJointDesc*)d );
		break;
		case NX_JOINT_D6:
			return gcnew D6JointDescription( (NxD6JointDesc*)d );
		break;
		case NX_JOINT_PRISMATIC:
			return gcnew PrismaticJointDescription( (NxPrismaticJointDesc*)d );
		break;
		case NX_JOINT_REVOLUTE:
			return gcnew RevoluteJointDescription( (NxRevoluteJointDesc*)d );
		break;
		case NX_JOINT_SPHERICAL:
			return gcnew SphericalJointDescription( (NxSphericalJointDesc*)d );
		break;
		case NX_JOINT_POINT_ON_LINE:
			return gcnew PointOnLineJointDescription( (NxPointOnLineJointDesc*)d );
		break;
		case NX_JOINT_POINT_IN_PLANE:
			return gcnew PointInPlaneJointDescription( (NxPointInPlaneJointDesc*)d );
		break;
		case NX_JOINT_DISTANCE:
			return gcnew DistanceJointDescription( (NxDistanceJointDesc*)d );
		break;
		case NX_JOINT_PULLEY:
			return gcnew PulleyJointDescription( (NxPulleyJointDesc*)d );
		break;
		case NX_JOINT_FIXED:
			return gcnew FixedJointDescription( (NxFixedJointDesc*)d );
		break;
		
		default: throw gcnew ApplicationException( "Invalid joint type" );
	}
}

JointType JointDescription::Type::get()
{
	return (JointType)_desc->getType();
}

Actor^ JointDescription::Actor1::get()
{
	return _actor1;
}
void JointDescription::Actor1::set( Actor^ value )
{
	if( _actor1 != nullptr )
	{
		_actor1->onDisposing -= gcnew EventHandler( this, &JointDescription::_actor1_onDisposed );
	}
	
	_actor1 = value;
	
	if( value == nullptr )
	{
		_desc->actor[ 0 ] = NULL;
	}else{
		_desc->actor[ 0 ] = value->UnmanagedPointer;
		
		_actor1->onDisposing += gcnew EventHandler( this, &JointDescription::_actor1_onDisposed );
	}
}
Actor^ JointDescription::Actor2::get()
{
	return _actor2;
}
void JointDescription::Actor2::set( Actor^ value )
{
	if( _actor2 != nullptr )
	{
		_actor2->onDisposing -= gcnew EventHandler( this, &JointDescription::_actor2_onDisposed );
	}
	
	_actor2 = value;
	
	if( value == nullptr )
	{
		_desc->actor[ 1 ] = NULL;
	}else{
		_desc->actor[ 1 ] = value->UnmanagedPointer;
		
		_actor2->onDisposing += gcnew EventHandler( this, &JointDescription::_actor2_onDisposed );
	}
}

String^ JointDescription::Name::get()
{
	return _name;
}
void JointDescription::Name::set( String^ value )
{
	_name = value;
}

Vector3 JointDescription::LocalNormal1::get()
{
	return Math::NxVec3ToVector3( _desc->localNormal[ 0 ] );
}
void JointDescription::LocalNormal1::set( Vector3 value )
{
	_desc->localNormal[ 0 ] = Math::Vector3ToNxVec3( value );
}

Vector3 JointDescription::LocalNormal2::get()
{
	return Math::NxVec3ToVector3( _desc->localNormal[ 1 ] );
}
void JointDescription::LocalNormal2::set( Vector3 value )
{
	_desc->localNormal[ 1 ] = Math::Vector3ToNxVec3( value );
}

Vector3 JointDescription::LocalAxis1::get()
{
	return Math::NxVec3ToVector3( _desc->localAxis[ 0 ] );
}
void JointDescription::LocalAxis1::set( Vector3 value )
{
	_desc->localAxis[ 0 ] = Math::Vector3ToNxVec3( value );
}
Vector3 JointDescription::LocalAxis2::get()
{
	return Math::NxVec3ToVector3( _desc->localAxis[ 1 ] );
}
void JointDescription::LocalAxis2::set( Vector3 value )
{
	_desc->localAxis[ 1 ] = Math::Vector3ToNxVec3( value );
}

Vector3 JointDescription::LocalAnchor1::get()
{
	return Math::NxVec3ToVector3( _desc->localAnchor[ 0 ] );
}
void JointDescription::LocalAnchor1::set( Vector3 value )
{
	_desc->localAnchor[ 0 ] = Math::Vector3ToNxVec3( value );
}
Vector3 JointDescription::LocalAnchor2::get()
{
	return Math::NxVec3ToVector3( _desc->localAnchor[ 1 ] );
}
void JointDescription::LocalAnchor2::set( Vector3 value )
{
	_desc->localAnchor[ 1 ] = Math::Vector3ToNxVec3( value );
}

float JointDescription::MaxForce::get()
{
	return _desc->maxForce;
}
void JointDescription::MaxForce::set( float value )
{
	_desc->maxForce = value;
}
float JointDescription::MaxTorque::get()
{
	return _desc->maxTorque;
}
void JointDescription::MaxTorque::set( float value )
{
	_desc->maxTorque = value;
}
float JointDescription::SolverExtrapolationFactor::get()
{
	return _desc->solverExtrapolationFactor;
}
void JointDescription::SolverExtrapolationFactor::set( float value )
{
	_desc->solverExtrapolationFactor = value;
}
JointAccelerationSpringType JointDescription::AccelerationSpring::get()
{
	return (JointAccelerationSpringType)_desc->useAccelerationSpring;
}
void JointDescription::AccelerationSpring::set( JointAccelerationSpringType value )
{
	_desc->useAccelerationSpring = (NxU32)value;
}

JointFlag JointDescription::JointFlags::get()
{
	return (JointFlag)_desc->jointFlags;
}
void JointDescription::JointFlags::set( JointFlag value )
{
	_desc->jointFlags = (NxJointFlag)value;
}

Object^ JointDescription::UserData::get()
{
	return _userData;
}
void JointDescription::UserData::set( Object^ value )
{
	_userData = value;
}

NxJointDesc* JointDescription::UnmanagedPointer::get()
{
	return _desc;
}