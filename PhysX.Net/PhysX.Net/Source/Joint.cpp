#include "StdAfx.h"

#include "Joint.h"
#include "Actor.h"
#include "Joint Description.h"
#include "Scene.h"
#include "Enums.h"
#include "Functions.h"
#include "Joint Limit Plane.h"

#include <NxJointDesc.h> 

using namespace StillDesign::PhysX;

Joint::Joint( NxJoint* joint )
{
	Debug::Assert( joint != NULL );
	
	ObjectCache::Add( (intptr_t)joint, this );
	
	_joint = joint;
	
	_scene = ObjectCache::GetObject<StillDesign::PhysX::Scene^>( (intptr_t)(&joint->getScene()) );
	
	// Find Actors
	NxActor* actor1;
	NxActor* actor2;
	
	joint->getActors( &actor1, &actor2 );
	
	if( actor1 != NULL )
		_actor1 = ObjectCache::GetObject<Actor^>( (intptr_t)actor1 );
	if( actor2 != NULL )
		_actor2 = ObjectCache::GetObject<Actor^>( (intptr_t)actor2 );
	
	_limitPlanes = gcnew ListBase< LimitPlane >();
}
Joint::~Joint()
{
	this->!Joint();
}
Joint::!Joint()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_scene->UnmanagedPointer->releaseJoint( *_joint );
	
	_joint = NULL;
	
	_scene = nullptr;
	
	_actor1 = nullptr;
	_actor2 = nullptr;
	
	OnDisposed( this, nullptr );
}
bool Joint::IsDisposed::get()
{
	return ( _joint == NULL );
}

void Joint::SaveToDescription( JointDescription^ jointDescription )
{
	ThrowIfNull( jointDescription, "jointDescription" );
	
	jointDescription->Actor1 = this->Actor1;
	jointDescription->Actor2 = this->Actor2;
	
	jointDescription->Name = this->Name;
	jointDescription->UserData = this->UserData;
}
void Joint::LoadFromDescription( JointDescription^ jointDescription )
{
	ThrowIfNull( jointDescription, "jointDescription" );
	
	_actor1 = jointDescription->Actor1;
	_actor2 = jointDescription->Actor2;
	
	this->Name = jointDescription->Name;
	this->UserData = jointDescription->UserData;
}

void Joint::AddLimitPlane( LimitPlane limitPlane )
{
	NxVec3 normal = Math::Vector3ToNxVec3( limitPlane.Normal );
	NxVec3 pointInPlane = Math::Vector3ToNxVec3( limitPlane.PointInPlane() );
	float restitution = limitPlane.Resitution;
	
	_joint->addLimitPlane( normal, pointInPlane, restitution );
	
	_limitPlanes->Add( limitPlane );
}
bool Joint::RemoveLimitPlane( LimitPlane limitPlane )
{
	_joint->resetLimitPlaneIterator();
	
	NxVec3 planeNormal;
	float distance;
	float restitution;
	
	int i = 0;
	while( _joint->getNextLimitPlane( planeNormal, distance, &restitution ) )
	{
		NxVec3 n = Math::Vector3ToNxVec3( limitPlane.Normal );
		float d = limitPlane.Distance;
		float r = limitPlane.Resitution;
		
		if( planeNormal == n || distance == d || restitution == r )
		{
			RemoveLimitPlane( i );
			
			return true;
		}
		
		i++;
	}
	
	return false;
}
void Joint::RemoveLimitPlane( int index )
{
	_limitPlanes->RemoveAt( index );
	
	_joint->resetLimitPlaneIterator();
	_joint->purgeLimitPlanes();

	for each ( LimitPlane plane in _limitPlanes )
	{
		_joint->addLimitPlane(
				Math::Vector3ToNxVec3( plane.Normal ),
				Math::Vector3ToNxVec3( plane.PointInPlane() ),
				plane.Distance
			);
	}
	
	// Copy all limit planes
	//array<LimitPlane>^ planes = this->LimitPlanes->ToArray();
	
	// Remove all limit planes

	
	
	// Add limit planes in again, except the delete one
	//for( int x = 0; x < _limitPlanes->Length; x++ )
	//{
	//	if( x == index )
	//		continue;
		
		//AddLimitPlane( planes[ x ] );
	//}
}

void Joint::SetLimitPoint( Vector3 point )
{
	SetLimitPoint( point, true );
}
void Joint::SetLimitPoint( Vector3 point, bool isPointOnActor2 )
{
	_joint->setLimitPoint( Math::Vector3ToNxVec3( point ), isPointOnActor2 );
	
	// Setting the limit point also removes all the limit planes
	_limitPlanes->Clear();
}
Nullable<Vector3> Joint::GetLimitPoint()
{
	NxVec3 point;
	bool result = _joint->getLimitPoint( point );
	
	if( result == false )
		return Nullable<Vector3>();
	else
		return Math::NxVec3ToVector3( point );
}

// Name
String^ Joint::Name::get()
{
	return Functions::UnmanagedToManagedString( _joint->getName() );
}
void Joint::Name::set( String^ value )
{
	_joint->setName( Functions::ManagedToUnmanagedString( value ) );
}

// Actors
Actor^ Joint::Actor1::get()
{
	return _actor1;
}
Actor^ Joint::Actor2::get()
{
	return _actor2;
}

// Scene
StillDesign::PhysX::Scene^ Joint::Scene::get()
{
	return _scene;
}

// Global Anchor
Vector3 Joint::GlobalAnchor::get()
{
	return Math::NxVec3ToVector3( _joint->getGlobalAnchor() );
}
void Joint::GlobalAnchor::set( Vector3 value )
{
	_joint->setGlobalAnchor( Math::Vector3ToNxVec3( value ) );
}

// Global Axis
Vector3 Joint::GlobalAxis::get()
{
	return Math::NxVec3ToVector3( _joint->getGlobalAxis() );
}
void Joint::GlobalAxis::set( Vector3 value )
{
	_joint->setGlobalAxis( Math::Vector3ToNxVec3( value ) );
}

JointState Joint::State::get()
{
	return (JointState)_joint->getState();
}

// Max Force
float Joint::BreakableMaxForce::get()
{
	float maxForce, maxTorque;
	
	_joint->getBreakable( maxForce, maxTorque );
	
	return maxForce;
}
void Joint::BreakableMaxForce::set( float value )
{
	_joint->setBreakable( value, this->BreakableMaxTorque );
}

// Max Torque
float Joint::BreakableMaxTorque::get()
{
	float maxForce, maxTorque;
	
	_joint->getBreakable( maxForce, maxTorque );
	
	return maxTorque;
}
void Joint::BreakableMaxTorque::set( float value )
{
	_joint->setBreakable( this->BreakableMaxForce, value );
}

float Joint::SolverExtrapolationFactor::get()
{
	return _joint->getSolverExtrapolationFactor();
}
void Joint::SolverExtrapolationFactor::set( float value )
{
	_joint->setSolverExtrapolationFactor( value );
}
JointAccelerationSpringType Joint::AccelerationSpring::get()
{
	return (JointAccelerationSpringType)_joint->getUseAccelerationSpring();
}
void Joint::AccelerationSpring::set( JointAccelerationSpringType value )
{
	_joint->setUseAccelerationSpring( (NxU32)value );
}

JointType Joint::Type::get()
{
	return (JointType)_joint->getType();
}

ReadOnlyList< LimitPlane >^ Joint::LimitPlanes::get()
{
	return _limitPlanes->ReadOnlyCollection;
}

Object^ Joint::UserData::get()
{
	return _userData;
}
void Joint::UserData::set( Object^ value )
{
	_userData = value;
}

NxJoint* Joint::UnmanagedPointer::get()
{
	return _joint;
}