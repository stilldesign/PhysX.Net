#include "StdAfx.h"

#include "Actor.h"
#include "Actor Description.h"

#include "Scene.h"
#include "Shape.h"
#include "Shape Description.h"
#include "Box Shape.h"
#include "Sphere Shape.h"
#include "Capsule Shape.h"
#include "Plane Shape.h"
#include "Triangle Mesh Shape.h"
#include "Convex Shape.h"
#include "Body Description.h"
#include "Functions.h"
#include "Math.h"
#include "Cooking.h"
#include "User Memory Writer Stream.h"
#include "User Memory Reader Stream.h"
#include "Material.h"
#include "Box Shape Description.h"
#include "Sphere Shape Description.h"
#include "Capsule Shape Description.h"
#include "Plane Shape Description.h"
#include "Triangle Mesh Shape Description.h"
#include "Wheel Shape.h"
#include "Wheel Shape Description.h"
#include "User Entity Report.h"
#include "Sweep Query Hit.h"
#include "Sweep Cache.h"
#include "Height Field Shape.h"
#include "Compartment.h"
#include "User Entity Report.h"

using namespace StillDesign;
using namespace StillDesign::PhysX;

Actor::Actor( NxActor* actor )
{
	Debug::Assert( actor != NULL );
	
	ObjectCache::Add( (intptr_t)actor, this );
	
	_actor = actor;
	_scene = ObjectCache::GetObject<StillDesign::PhysX::Scene^>( (intptr_t)(&actor->getScene()) );
	if( actor->getCompartment() != NULL )
		_compartment = ObjectCache::GetObject<StillDesign::PhysX::Compartment^>( (intptr_t)actor->getCompartment() );
	
	_shapes = gcnew ElementCollection< Shape^, ShapeCollection^ >();
	CreateShapes();
	
	//_disposing = false;
}
Actor::~Actor()
{
	this->!Actor();
}
Actor::!Actor()
{
	if( this->IsDisposed == true )
		return;
	
	//_disposing = true;
	
	onDisposing( this, nullptr );
	
	_shapes->DiposeOfAll();
	_shapes->Clear();
	_shapes = nullptr;
	
	_scene->UnmanagedPointer->releaseActor( *_actor );
	
	_actor = NULL;
	_scene = nullptr;
	_userData = nullptr;
	
	onDisposed( this, nullptr );
	
	//_disposing = false;
}
bool Actor::IsDisposed::get()
{
	return ( _actor == NULL );
}
//bool Actor::IsDisposing::get()
//{
//	return _disposing;
//}

ActorDescription^ Actor::SaveToActorDescription()
{
	return SaveToActorDescription( false, false );
}
ActorDescription^ Actor::SaveToActorDescription( bool retrieveBody, bool retrieveShapes )
{
	ActorDescription^ desc = gcnew ActorDescription();
	
	// Actor Desc
	_actor->saveToDesc( *desc->UnmanagedPointer );
	
	if( retrieveBody == true )
	{
		if( _actor->isDynamic() == true )
			desc->BodyDescription = this->SaveBodyToDescription();
	}
	
	if( retrieveShapes == true )
	{
		for each( Shape^ shape in this->Shapes )
		{
			ShapeDescription^ shapeDesc;
			switch( shape->Type )
			{
				case ShapeType::Box:
					shapeDesc = ((BoxShape^)shape)->SaveToDescription();
				break;
				case ShapeType::Sphere:
					shapeDesc = ((SphereShape^)shape)->SaveToDescription();
				break;
				case ShapeType::Capsule:
					shapeDesc = ((CapsuleShape^)shape)->SaveToDescription();
				break;
				case ShapeType::Plane:
					shapeDesc = ((PlaneShape^)shape)->SaveToDescription();
				break;
				case ShapeType::Mesh:
					shapeDesc = ((TriangleMeshShape^)shape)->SaveToDescription();
				break;
				case ShapeType::Convex:
					shapeDesc = ((ConvexShape^)shape)->SaveToDescription();
				break;
				case ShapeType::Wheel:
					shapeDesc = ((WheelShape^)shape)->SaveToDescription();
				break;
				
				default: throw gcnew ApplicationException( String::Format( "Cannot Save {0} Shape Descriptions", shape->Type ) );
			}
			
			desc->Shapes->Add( shapeDesc );
		}
	}
	
	desc->UserData = this->UserData;
	
	return desc;
}
BodyDescription^ Actor::SaveBodyToDescription()
{
	if( _actor->isDynamic() == false )
	{
		return nullptr;
	}else{
		NxBodyDesc* desc = new NxBodyDesc();
		_actor->saveBodyToDesc( *desc );
		
		return gcnew BodyDescription( desc );
	}
}

void Actor::CreateShapes()
{
	// Populate the Collection with the Shapes the Actor Already Has
	NxShape* const* shapes = _actor->getShapes();
	for( unsigned int x = 0; x < _actor->getNbShapes(); x++ )
	{
		Shape^ shape;
		
		switch( shapes[ x ]->getType() )
		{
			case NX_SHAPE_BOX:
				shape = gcnew BoxShape( shapes[ x ]->isBox() );
			break;
			case NX_SHAPE_SPHERE:
				shape = gcnew SphereShape( shapes[ x ]->isSphere() );
			break;
			case NX_SHAPE_CAPSULE:
				shape = gcnew CapsuleShape( shapes[ x ]->isCapsule() );
			break;
			case NX_SHAPE_PLANE:
				shape = gcnew PlaneShape( shapes[ x ]->isPlane() );
			break;
			case NX_SHAPE_MESH:
				shape = gcnew TriangleMeshShape( shapes[ x ]->isTriangleMesh() );
			break;
			case NX_SHAPE_HEIGHTFIELD:
				shape = gcnew HeightFieldShape( shapes[ x ]->isHeightField() );
			break;
			case NX_SHAPE_CONVEX:
				shape = gcnew ConvexShape( shapes[ x ]->isConvexMesh() );
			break;
			case NX_SHAPE_WHEEL:
				shape = gcnew WheelShape( shapes[ x ]->isWheel() );
			break;
			
			default: throw gcnew NotImplementedException( "Shape Type Unhandled" );
		}
		
		//shape->Material = this->Scene->Materials->GetMaterialByIndex( shapes[ x ]->getMaterial() );
		
		_shapes->Add( shape );
	}
}


Shape^ Actor::CreateShape( ShapeDescription^ shapeDescription )
{
	if( shapeDescription == nullptr )
		throw gcnew ArgumentNullException( "shapeDescription" );
	
	NxShapeType shapeType = shapeDescription->UnmanagedPointer->getType();
	
	Shape^ shape;
	switch( shapeType )
	{
		case NX_SHAPE_BOX:
		{
			NxBoxShapeDesc* desc = (NxBoxShapeDesc*)(shapeDescription->UnmanagedPointer);
			
			NxShape* actorShape = _actor->createShape( *desc );
			
			shape = gcnew BoxShape( actorShape->isBox() );
		}
		break;
		case NX_SHAPE_SPHERE:
		{
			NxSphereShapeDesc* desc = (NxSphereShapeDesc*)(shapeDescription->UnmanagedPointer);
			
			NxShape* actorShape = _actor->createShape( *desc );
			
			shape = gcnew SphereShape( actorShape->isSphere() );
		}
		break;
		case NX_SHAPE_PLANE:
		{
			NxPlaneShapeDesc* desc = (NxPlaneShapeDesc*)(shapeDescription->UnmanagedPointer);
			
			NxShape* actorShape = _actor->createShape( *desc );
			
			shape = gcnew PlaneShape( actorShape->isPlane() );
		}
		break;
		case NX_SHAPE_MESH:
		{
			NxTriangleMeshShapeDesc* desc = (NxTriangleMeshShapeDesc*)(shapeDescription->UnmanagedPointer);
			
			NxShape* actorShape = _actor->createShape( *desc );
			
			shape = gcnew TriangleMeshShape( actorShape->isTriangleMesh() );
		}
		break;
		case NX_SHAPE_CONVEX:
		{
			NxConvexShapeDesc* desc = (NxConvexShapeDesc*)(shapeDescription->UnmanagedPointer);
			
			NxShape* actorShape = _actor->createShape( *desc );
			
			shape = gcnew ConvexShape( actorShape->isConvexMesh() );
		}
		break;
		case NX_SHAPE_WHEEL:
		{
			NxWheelShapeDesc* desc = (NxWheelShapeDesc*)(shapeDescription->UnmanagedPointer);
			
			NxShape* actorShape = _actor->createShape( *desc );
			
			shape = gcnew WheelShape( actorShape->isWheel() );
		}
		break;
		
		default: throw gcnew NotImplementedException( "Shape type is invalid" );
	}
	
	_shapes->Add( shape );
	
	return shape;
}

void Actor::WakeUp()
{
	_actor->wakeUp();
}
void Actor::WakeUp( float sleepFrames )
{
	_actor->wakeUp( sleepFrames );
}
void Actor::Sleep()
{
	_actor->putToSleep();
}

// Forces
void Actor::AddForceAtPosition( Vector3 force, Vector3 position, ForceMode forceMode )
{
	_actor->addForceAtPos( Math::Vector3ToNxVec3( force ), Math::Vector3ToNxVec3( position ), (NxForceMode)forceMode );
}
void Actor::AddForceAtLocalPosition( Vector3 force, Vector3 position )
{
	_actor->addForceAtLocalPos( Math::Vector3ToNxVec3( force ), Math::Vector3ToNxVec3( position ) );
}
void Actor::AddForceAtLocalPosition( Vector3 force, Vector3 position, ForceMode forceMode, bool wakeup )
{
	_actor->addForceAtLocalPos( Math::Vector3ToNxVec3( force ), Math::Vector3ToNxVec3( position ), (NxForceMode)forceMode, wakeup );
}
void Actor::AddLocalForceAtPosition( Vector3 force, Vector3 position, ForceMode forceMode )
{
	_actor->addLocalForceAtPos( Math::Vector3ToNxVec3( force ), Math::Vector3ToNxVec3( position ), (NxForceMode)forceMode );
}
void Actor::AddLocalForceAtLocalPosition( Vector3 force, Vector3 position, ForceMode forceMode )
{
	_actor->addLocalForceAtLocalPos( Math::Vector3ToNxVec3( force ), Math::Vector3ToNxVec3( position ), (NxForceMode)forceMode );
}

void Actor::AddForce( Vector3 force, ForceMode forceMode )
{
	_actor->addForce( Math::Vector3ToNxVec3( force ), (NxForceMode)forceMode );
}
void Actor::AddLocalForce( Vector3 force, ForceMode forceMode )
{
	_actor->addLocalForce( Math::Vector3ToNxVec3( force ), (NxForceMode)forceMode );
}

void Actor::AddTorque( Vector3 torque, ForceMode forceMode )
{
	_actor->addTorque( Math::Vector3ToNxVec3( torque ), (NxForceMode)forceMode );
}
void Actor::AddLocalTorque( Vector3 torque, ForceMode forceMode )
{
	_actor->addLocalTorque( Math::Vector3ToNxVec3( torque ), (NxForceMode)forceMode );
}

bool Actor::UpdateMassFromShapes( float density, float totalMass )
{
	return _actor->updateMassFromShapes( density, totalMass );
}

// Move
void Actor::MoveGlobalPoseTo( Matrix globalTransform )
{
	_actor->moveGlobalPose( Math::MatrixToMat34( globalTransform ) );
}
void Actor::MoveGlobalPositionTo( Vector3 globalPosition )
{
	_actor->moveGlobalPosition( Math::Vector3ToNxVec3( globalPosition ) );
}
void Actor::MoveGlobalOrientationTo( Matrix globalRotation )
{
	_actor->moveGlobalOrientation( Math::MatrixToMat33( globalRotation ) );
}
void Actor::MoveGlobalOrientationTo( Quaternion globalRotation )
{
	_actor->moveGlobalOrientationQuat( Math::QuaternionNxQuat( globalRotation ) );
}

float Actor::ComputeKineticEnergy()
{
	return _actor->computeKineticEnergy();
}
Vector3 Actor::ComputePointVelocity( Vector3 point )
{
	NxVec3 velocity = _actor->getPointVelocity( Math::Vector3ToNxVec3( point ) );
	
	return Vector3( velocity.x, velocity.y, velocity.z );
}
Vector3 Actor::ComputeLocalPointVelocity( Vector3 point )
{
	return Math::NxVec3ToVector3( _actor->getLocalPointVelocity( Math::Vector3ToNxVec3( point ) ) );
}

bool Actor::ReadActorFlag( ActorFlag flag )
{
	return _actor->readActorFlag( (NxActorFlag)flag );
}
void Actor::RaiseActorFlag( ActorFlag flag )
{
	_actor->raiseActorFlag( (NxActorFlag)flag );
}
void Actor::ClearActorFlag( ActorFlag flag )
{
	_actor->clearActorFlag( (NxActorFlag)flag );
}

bool Actor::ReadBodyFlag( BodyFlag flag )
{
	return _actor->readBodyFlag( (NxBodyFlag)flag );
}
void Actor::RaiseBodyFlag( BodyFlag flag )
{
	_actor->raiseBodyFlag( (NxBodyFlag)flag );
}
void Actor::ClearBodyFlag( BodyFlag flag )
{
	_actor->clearBodyFlag( (NxBodyFlag)flag );
}

void Actor::ResetUserActorPairFiltering()
{
	_actor->resetUserActorPairFiltering();
}

void Actor::SetCenterOfMassOffsetLocalPose( Matrix localPose )
{
	_actor->setCMassOffsetLocalPose( Math::MatrixToMat34( localPose ) );
}
void Actor::SetCenterOfMassOffsetLocalPosition( Vector3 localPosition )
{
	_actor->setCMassOffsetLocalPosition( Math::Vector3ToNxVec3( localPosition ) );
}
void Actor::SetCenterOfMassOffsetLocalOrientation( Matrix localOrientation )
{
	_actor->setCMassOffsetLocalOrientation( Math::MatrixToMat33( localOrientation ) );
}
void Actor::SetCenterOfMassOffsetGlobalPose( Matrix globalPose )
{
	_actor->setCMassOffsetGlobalPose( Math::MatrixToMat34( globalPose ) );
}
void Actor::SetCenterOfMassOffsetGlobalPosition( Vector3 globalPosition )
{
	_actor->setCMassOffsetGlobalPosition( Math::Vector3ToNxVec3( globalPosition ) );
}
void Actor::SetCenterOfMassOffsetGlobalOrientation( Matrix globalOrientation )
{
	_actor->setCMassOffsetGlobalOrientation( Math::MatrixToMat33( globalOrientation ) );
}

Vector3 Actor::GetPointVelocity( Vector3 point )
{
	return Math::NxVec3ToVector3( _actor->getPointVelocity( Math::Vector3ToNxVec3( point ) ) );
}
Vector3 Actor::GetLocalPointVelocity( Vector3 point )
{
	return Math::NxVec3ToVector3( _actor->getLocalPointVelocity( Math::Vector3ToNxVec3( point ) ) );
}

int Actor::LinearSweep( Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback )
{
	return LinearSweep( motion, flags, userData, callback, nullptr );
}
int Actor::LinearSweep( Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback, SweepCache^ cache )
{
	if( callback == nullptr )
		throw gcnew ArgumentNullException( "callback" );
	
	int result = _actor->linearSweep( 
										Math::Vector3ToNxVec3( motion ),
										(NxU32)flags,
										NULL,
										NX_MAX_U32,
										NULL,
										callback->UnmanagedPointer,
										cache == nullptr ? NULL : cache->UnmanagedPointer
										);
	
	return result;
}

//

//// Properties ////
StillDesign::PhysX::Scene^ Actor::Scene::get()
{
	return _scene;
}

String^ Actor::Name::get()
{
	return Functions::UnmanagedToManagedString( _actor->getName() );
}
void Actor::Name::set( String^ value )
{
	_actor->setName( Functions::ManagedToUnmanagedString( value ) );
}

bool Actor::IsDynamic::get()
{
	return _actor->isDynamic();
}

// Shapes
Actor::ShapeCollection^ Actor::Shapes::get()
{
	return _shapes->ReadOnlyCollection;
}

StillDesign::PhysX::Compartment^ Actor::Compartment::get()
{
	return _compartment;
}

// Orientation
Vector3 Actor::GlobalPosition::get()
{
	NxVec3 pos = _actor->getGlobalPosition();
	
	return Math::NxVec3ToVector3( pos );
}
void Actor::GlobalPosition::set( Vector3 value )
{
	_actor->setGlobalPosition( Math::Vector3ToNxVec3( value ) );
}

Matrix Actor::GlobalPose::get()
{
	return Math::Mat34ToMatrix( &_actor->getGlobalPose() );
}
void Actor::GlobalPose::set( Matrix value )
{
	_actor->setGlobalPose( Math::MatrixToMat34( value ) );
}

Matrix Actor::GlobalOrientation::get()
{
	return Math::Mat33ToMatrix( &_actor->getGlobalOrientation() );
}
void Actor::GlobalOrientation::set( Matrix value )
{
	_actor->setGlobalOrientation( Math::MatrixToMat33( value ) );
}

Quaternion Actor::GlobalOrientationQuat::get()
{
	return Math::NxQuatToQuaternion( _actor->getGlobalOrientationQuat() );
}
void Actor::GlobalOrientationQuat::set( Quaternion value )
{
	_actor->setGlobalOrientationQuat( Math::QuaternionNxQuat( value ) );
}

//
// Sleeping
//

bool Actor::IsGroupSleeping::get()
{
	return _actor->isGroupSleeping();
}
bool Actor::IsSleeping::get()
{
	return _actor->isSleeping();
}

float Actor::SleepLinearVelocity::	get()
{
	return _actor->getSleepLinearVelocity();
}
void Actor::SleepLinearVelocity::set( float value )
{
	_actor->setSleepLinearVelocity( value );
}

float Actor::SleepAngularVelocity::get()
{
	return _actor->getSleepAngularVelocity();
}
void Actor::SleepAngularVelocity::set( float value )
{
	_actor->setSleepAngularVelocity( value );
}

float Actor::SleepEnergyThreshold::get()
{
	return _actor->getSleepEnergyThreshold();
}
void Actor::SleepEnergyThreshold::set( float value )
{
	_actor->setSleepEnergyThreshold( value );
}

// Center of Mass
Matrix Actor::CenterOfMassLocalPose::get()
{
	NxMat34 pose = _actor->getCMassLocalPose();	
		
	return PhysX::Math::Mat34ToMatrix( &pose );
}
Matrix Actor::CenterOfMassLocalOrientation::get()
{
	NxMat33 orientation = _actor->getCMassLocalOrientation();
	
	return PhysX::Math::Mat33ToMatrix( &orientation );
}
Matrix Actor::CenterOfMassGlobalPose::get()
{
	NxMat34 pose = _actor->getCMassGlobalPose();
	
	return PhysX::Math::Mat34ToMatrix( &pose );
}
Matrix Actor::CenterOfMassGlobalOrientation::get()
{
	NxMat33 orientation = _actor->getCMassGlobalOrientation();
	
	return PhysX::Math::Mat33ToMatrix( &orientation );
}
Matrix Actor::GlobalInertiaTensor::get()
{
	NxMat33 globalInertiaTensor = _actor->getGlobalInertiaTensor();
	
	return Math::Mat33ToMatrix( &globalInertiaTensor );
}

Matrix Actor::GlobalInertiaTensorInverse::get()
{
	NxMat33 globalInertiaTensorInverse = _actor->getGlobalInertiaTensorInverse();
	
	return Math::Mat33ToMatrix( &globalInertiaTensorInverse );
}

// Velocity
Vector3 Actor::LinearVelocity::get()
{
	return Math::NxVec3ToVector3( _actor->getLinearVelocity() );
}
void Actor::LinearVelocity::set( Vector3 value )
{
	_actor->setLinearVelocity( Math::Vector3ToNxVec3( value ) );
}

Vector3 Actor::AngularVelocity::get()
{
	return Math::NxVec3ToVector3( _actor->getAngularVelocity() );
}
void Actor::AngularVelocity::set( Vector3 value )
{
	_actor->setAngularVelocity( Math::Vector3ToNxVec3( value ) );
}

float Actor::MaximumAngularVelocity::get()
{
	return _actor->getMaxAngularVelocity();
}
void Actor::MaximumAngularVelocity::set( float value )
{
	_actor->setMaxAngularVelocity( value );
}

// Mass
/// <summary>Gets or Sets the Mass of the Actor</summary>
float Actor::Mass::get()
{
	return _actor->getMass();
}
void Actor::Mass::set( float value )
{
	if( value < 0 )
		throw gcnew ArgumentOutOfRangeException( "value", "Mass must be greater than or equal to 0" );
	
	_actor->setMass( value );
}

Vector3 Actor::CenterOfMassLocalPosition::get()
{
	return Math::NxVec3ToVector3( _actor->getCMassLocalPosition() );
}

Vector3 Actor::CenterOfMassGlobalPosition::get()
{
	return Math::NxVec3ToVector3( _actor->getCMassGlobalPosition() );
}

Vector3 Actor::MassSpaceInertiaTensor::get()
{
	return Math::NxVec3ToVector3( _actor->getMassSpaceInertiaTensor() );
}
void Actor::MassSpaceInertiaTensor::set( Vector3 value )
{
	_actor->setMassSpaceInertiaTensor( Math::Vector3ToNxVec3( value ) );
}

// Damping
float Actor::LinearDamping::get()
{
	return _actor->getLinearDamping();
}
void Actor::LinearDamping::set( float value )
{
	_actor->setLinearDamping( value );
}

float Actor::AngularDamping::get()
{
	return _actor->getAngularDamping();
}
void Actor::AngularDamping::set( float value )
{
	_actor->setAngularDamping( value );
}

// CCD
float Actor::CCDMotionThreshold::get()
{
	return _actor->getCCDMotionThreshold();
}
void Actor::CCDMotionThreshold::set( float value )
{
	_actor->setCCDMotionThreshold( value );
}

// Momentum
Vector3 Actor::LinearMomentum::get()
{
	return Math::NxVec3ToVector3( _actor->getLinearMomentum() );
}
void Actor::LinearMomentum::set( Vector3 value )
{
	_actor->setLinearMomentum( Math::Vector3ToNxVec3( value ) );
}
Vector3 Actor::AngularMomentum::get()
{
	return Math::NxVec3ToVector3( _actor->getAngularMomentum() );
}
void Actor::AngularMomentum::set( Vector3 value )
{
	_actor->setAngularMomentum( Math::Vector3ToNxVec3( value ) );
}

// Group
short Actor::Group::get()
{
	return _actor->getGroup();
}
void Actor::Group::set( short value )
{
	_actor->setGroup( value );
}

short Actor::DominanceGroup::get()
{
	return _actor->getDominanceGroup();
}
void Actor::DominanceGroup::set( short value )
{
	_actor->setDominanceGroup( value );
}

int Actor::SolverIterationCount::get()
{
	return _actor->getSolverIterationCount();
}
void Actor::SolverIterationCount::set( int value )
{
	_actor->setSolverIterationCount( value );
}

float Actor::ContactReportThreshold::get()
{
	return _actor->getContactReportThreshold();
}
void Actor::ContactReportThreshold::set( float value )
{
	_actor->setContactReportThreshold( value );
}

ContactPairFlag Actor::ContactReportFlags::get()
{
	return (ContactPairFlag)_actor->getContactReportFlags();
}
void Actor::ContactReportFlags::set( ContactPairFlag value )
{
	_actor->setContactReportFlags( (NxU32)value );
}

short Actor::ForceFieldMaterial::get()
{
	return _actor->getForceFieldMaterial();
}
void Actor::ForceFieldMaterial::set( short value )
{
	_actor->setForceFieldMaterial( value );
}

Object^ Actor::UserData::get()
{
	return _userData;
}
void Actor::UserData::set( Object^ value )
{
	_userData = value;
}

NxActor* Actor::UnmanagedPointer::get()
{
	return _actor;
}
void Actor::UnmanagedPointer::set( NxActor* value )
{
	_actor = value;
}