#include "StdAfx.h"

#include "Scene.h"
#include "Scene Description.h"
#include "Scene Timing Information.h"
#include "Core.h"
#include "Material.h"
#include "Shape.h"
#include "Actor.h"
#include "User Contact Report.h"
#include "Sphere.h"
#include "Scene Statistics.h"
#include "Scene Limits.h"
#include "Shape.h"
#include "Debug Renderable.h"
#include "Actor Description.h"
#include "Material Description.h"
#include "Cylindrical Joint.h"
#include "Cylindrical Joint Description.h"
#include "D6 Joint.h"
#include "D6 Joint Description.h"
#include "Distance Joint.h"
#include "Distance Joint Description.h"
#include "Fixed Joint.h"
#include "Fixed Joint Description.h"
#include "Point In Plane Joint.h"
#include "Point In Plane Joint Description.h"
#include "Point On Line Joint.h"
#include "Point On Line Joint Description.h"
#include "Prismatic Joint.h"
#include "Prismatic Joint Description.h"
#include "Pulley Joint.h"
#include "Pulley Joint Description.h"
#include "Revolute Joint.h"
#include "Revolute Joint Description.h"
#include "Spherical Joint.h"
#include "Spherical Joint Description.h"
#include "Cloth.h"
#include "Cloth Description.h"
#include "Force Field.h"
#include "Force Field Description.h"
//#include "Implicit Screen Mesh.h"
//#include "Implicit Screen Mesh Description.h"
#include "Controller Manager.h"
#include "Controller.h"
#include "Functions.h"
#include "Raycast Reporting.h"
#include "Fluid.h"
#include "Fluid Description.h"
#include "Triangle Mesh.h"
#include "Cloth Mesh.h"
#include "Sweep Cache.h"
#include "Shape Description.h"
#include "Soft Body Description.h"
#include "Compartment Description.h"
#include "User Notify.h"
#include "Fluid User Notify.h"
#include "User Trigger Report.h"
#include "User Contact Modify.h"
#include "User Entity Report.h"
#include "Box.h"
#include "Capsule.h"
#include "User Actor Pair Filtering.h"
#include "Compartment.h"
#include "Pair Flag.h"
#include "Constraint Dominance.h"
#include "Force Field Linear Kernel Description.h"
#include "Force Field Shape Group Description.h"
#include "Force Field Shape Group.h"
#include "Mesh Data.h"
#include "Soft Body Split Pair Data.h"
#include "PhysX Exception.h"

#include <NxScene.h>
#include <NxSceneDesc.h>
#include <NxDebugRenderable.h> 
#include <NxControllerManager.h> 
#include <ControllerManager.h> 

using namespace StillDesign::PhysX;

//

#pragma region Constructor etc
Scene::Scene( NxScene* scene )
{
	if( scene == NULL )
		throw gcnew ArgumentNullException( "scene", "Scene argument is NULL" );
	
	ObjectCache::Add( (intptr_t)scene, this );
	
	_scene = scene;
	_core = ObjectCache::GetObject<StillDesign::PhysX::Core^>( (intptr_t)(&scene->getPhysicsSDK()) );
	
	_actors = gcnew ElementCollection< Actor^ >();
	//_shapes = gcnew ElementCollection< Shape^ >();
	_materials = gcnew ElementCollection< Material^ >();
	_joints = gcnew ElementCollection< Joint^ >();
	_cloths = gcnew ElementCollection< Cloth^ >();
	_forceFields = gcnew ElementCollection< ForceField^ >();
	_controllerManagers = gcnew ElementCollection< ControllerManager^ >();
	//_controllerCollection = gcnew ElementCollection< Controller^ >();
	_fluids = gcnew ElementCollection< Fluid^ >();
	_softBodies = gcnew ElementCollection< SoftBody^ >();
	_compartments = gcnew ElementCollection< Compartment^ >();
	_forceFieldLinearKernels = gcnew ElementCollection< ForceFieldLinearKernel^ >();
	_forceFieldShapeGroups = gcnew ElementCollection< ForceFieldShapeGroup^ >();
	
	//
	
	//_actors->onAdd += gcnew EventHandlerItem<Actor^>( this, &Scene::Actors_onAdd );
	//_actors->onRemove += gcnew EventHandlerItem<Actor^>( this, &Scene::Actors_onRemove );
	
	//_controllerManagers->onAdd += gcnew EventHandlerItem< ControllerManager^ >( this, &Scene::_controllerManagerCollection_onAdd );
	//_controllerManagers->onRemove += gcnew EventHandlerItem< ControllerManager^ >( this, &Scene::_controllerManagerCollection_onRemove );
	
	// Compartments
	for( unsigned int x = 0; x < scene->getNbCompartments(); x++ )
	{
		NxCompartment* compartment;
		_scene->getCompartmentArray( &compartment, 1, x );
		
		_compartments->Add( gcnew Compartment( compartment, this ) );
	}
	// Materials
	for( unsigned int x = 0; x < scene->getNbMaterials(); x++ )
	{
		NxMaterial* material = scene->getMaterialFromIndex( x );
		
		_materials->Add( gcnew Material( material ) );
	}
	_defaultMaterial = _materials[ 0 ];
		_defaultMaterial->Restitution = 0.3f;
		_defaultMaterial->StaticFriction = 0.5f;
		_defaultMaterial->DynamicFriction = 0.5f;
	
	// Actors
	for( unsigned int x = 0; x < scene->getNbActors(); x++ )
	{
		NxActor* actor = scene->getActors()[ x ];
		if( actor == NULL )
			continue;
		
		_actors->Add( gcnew Actor( actor ) );
	}
	// Joints
	scene->resetJointIterator();
	for( unsigned int x = 0; x < scene->getNbJoints(); x++ )
	{
		NxJoint* joint = scene->getNextJoint();
		Joint^ j;
		
		switch( joint->getType() )
		{
			case NX_JOINT_CYLINDRICAL:
				j = gcnew CylindricalJoint( joint->isCylindricalJoint() );
			break;
			case NX_JOINT_D6:
				j = gcnew D6Joint( joint->isD6Joint() );
			break;
			case NX_JOINT_DISTANCE:
				j = gcnew DistanceJoint( joint->isDistanceJoint() );
			break;
			case NX_JOINT_FIXED:
				j = gcnew FixedJoint( joint->isFixedJoint() );
			break;
			case NX_JOINT_POINT_IN_PLANE:
				j = gcnew PointInPlaneJoint( joint->isPointInPlaneJoint() );
			break;
			case NX_JOINT_POINT_ON_LINE:
				j = gcnew PointOnLineJoint( joint->isPointOnLineJoint() );
			break;
			case NX_JOINT_PRISMATIC:
				j = gcnew PrismaticJoint( joint->isPrismaticJoint() );
			break;
			case NX_JOINT_PULLEY:
				j = gcnew PulleyJoint( joint->isPulleyJoint() );
			break;
			case NX_JOINT_REVOLUTE:
				j = gcnew RevoluteJoint( joint->isRevoluteJoint() );
			break;
			case NX_JOINT_SPHERICAL:
				j = gcnew SphericalJoint( joint->isSphericalJoint() );
			break;
			
			default:
				throw gcnew NotSupportedException( "Invalid Joint Type" );
		}
		
		_joints->Add( j );
	}
	// Cloths
	for( unsigned int x = 0; x < scene->getNbCloths(); x++ )
	{
		NxCloth* cloth = scene->getCloths()[ x ];
		
		MeshData^ meshData = gcnew MeshData( cloth->getMeshData() );
		
		_cloths->Add( gcnew Cloth( cloth, meshData ) );
	}
	// Force Fields
	for( unsigned int x = 0; x < scene->getNbForceFields(); x++ )
	{
		_forceFields->Add( gcnew ForceField( scene->getForceFields()[ x ] ) );
	}
	// Force Field Linear Kernels
	_scene->resetForceFieldLinearKernelsIterator();
	for( unsigned int x = 0; x < scene->getNbForceFieldLinearKernels(); x++ )
	{
		_forceFieldLinearKernels->Add( gcnew ForceFieldLinearKernel( scene->getNextForceFieldLinearKernel() ) );
	}
	// Force Field Shape Groups
	_scene->resetForceFieldShapeGroupsIterator();
	for( unsigned int x = 0; x < scene->getNbForceFieldShapeGroups(); x++ )
	{
		_forceFieldShapeGroups->Add( gcnew ForceFieldShapeGroup( scene->getNextForceFieldShapeGroup() ) );
	}
	// Fluids
	for( unsigned int x = 0; x < scene->getNbFluids(); x++ )
	{
		_fluids->Add( gcnew Fluid( scene->getFluids()[ x ] ) );
	}
}
Scene::~Scene()
{
	this->!Scene();
}
Scene::!Scene()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_compartments->DisposeOfAll();
	_actors->DisposeOfAll();
	_materials->DisposeOfAll();
	_joints->DisposeOfAll();
	_cloths->DisposeOfAll();
	_forceFields->DisposeOfAll();
	_forceFieldLinearKernels->DisposeOfAll();
	_forceFieldShapeGroups->DisposeOfAll();
	_controllerManagers->DisposeOfAll();
	_fluids->DisposeOfAll();
	_softBodies->DisposeOfAll();
	
	_compartments = nullptr;
	_actors = nullptr;
	_materials = nullptr;
	_joints = nullptr;
	_cloths = nullptr;
	_forceFields = nullptr;
	_forceFieldLinearKernels = nullptr;
	_forceFieldShapeGroups = nullptr;
	_controllerManagers = nullptr;
	_fluids = nullptr;
	_softBodies = nullptr;
	
	_userNotify = nullptr;
	_fluidUserNotify = nullptr;
	_userContactModify = nullptr;
	_userContactReport = nullptr;
	_userTriggerReport = nullptr;
	
	_defaultMaterial = nullptr;
	
	_core->UnmanagedPointer->releaseScene( *_scene );
	_scene = NULL;
	_core = nullptr;
	
	OnDisposed( this, nullptr );
}
bool Scene::IsDisposed::get()
{
	return ( _scene == NULL );
}
#pragma endregion

#pragma region Add Unmanaged Objects
Actor^ Scene::AddActor( NxActor* actor )
{
	Actor^ a = gcnew Actor( actor );
	
	_actors->Add( a );
	
	return a;
}
Material^ Scene::AddMaterial( NxMaterial* material )
{
	Material^ m = gcnew Material( material );
	
	_materials->Add( m );
	
	return m;
}
Joint^ Scene::AddJoint( NxJoint* joint )
{
	Joint^ j;
	
	switch( joint->getType() )
	{
		case NX_JOINT_CYLINDRICAL:
			j = gcnew CylindricalJoint( joint->isCylindricalJoint() );
		break;
		case NX_JOINT_D6:
			j = gcnew D6Joint( joint->isD6Joint() );
		break;
		case NX_JOINT_DISTANCE:
			j = gcnew DistanceJoint( joint->isDistanceJoint() );
		break;
		case NX_JOINT_FIXED:
			j = gcnew FixedJoint( joint->isFixedJoint() );
		break;
		case NX_JOINT_POINT_IN_PLANE:
			j = gcnew PointInPlaneJoint( joint->isPointInPlaneJoint() );
		break;
		case NX_JOINT_POINT_ON_LINE:
			j = gcnew PointOnLineJoint( joint->isPointOnLineJoint() );
		break;
		case NX_JOINT_PRISMATIC:
			j = gcnew PrismaticJoint( joint->isPrismaticJoint() );
		break;
		case NX_JOINT_PULLEY:
			j = gcnew PulleyJoint( joint->isPulleyJoint() );
		break;
		case NX_JOINT_REVOLUTE:
			j = gcnew RevoluteJoint( joint->isRevoluteJoint() );
		break;
		case NX_JOINT_SPHERICAL:
			j = gcnew SphericalJoint( joint->isSphericalJoint() );
		break;
		
		default:
			throw gcnew NotSupportedException( "Invalid joint type" );
	}
	
	_joints->Add( j );
	
	return j;
}
Cloth^ Scene::AddCloth( NxCloth* cloth )
{
	Cloth^ c = gcnew Cloth( cloth, gcnew MeshData( cloth->getMeshData() ) );
	
	_cloths->Add( c );
	
	return c;
}
ForceField^ Scene::AddForceField( NxForceField* forceField )
{
	ForceField^ f = gcnew ForceField( forceField );
	
	_forceFields->Add( f );
	
	return f;
}
StillDesign::PhysX::ControllerManager^ Scene::AddControllerManager( NxControllerManager* manager )
{
	StillDesign::PhysX::ControllerManager^ m = gcnew StillDesign::PhysX::ControllerManager( manager, this );
	
	_controllerManagers->Add( m );
	
	return m;
}
Fluid^ Scene::AddFluid( NxFluid* fluid )
{
	Fluid^ f = gcnew Fluid( fluid );
	
	_fluids->Add( f );
	
	return f;
}
ForceFieldLinearKernel^ Scene::AddForceFieldLinearKernel( NxForceFieldLinearKernel* kernel )
{
	ForceFieldLinearKernel^ k = gcnew ForceFieldLinearKernel( kernel );
	
	_forceFieldLinearKernels->Add( k );
	
	return k;
}
ForceFieldShapeGroup^ Scene::AddForceFieldShapeGroup( NxForceFieldShapeGroup* group )
{
	ForceFieldShapeGroup^ g = gcnew ForceFieldShapeGroup( group );
	
	_forceFieldShapeGroups->Add( g );
	
	return g;
}
SoftBody^ Scene::AddSoftBody( NxSoftBody* softBody )
{
	MeshData^ meshData = gcnew MeshData( softBody->getMeshData() );
	SoftBodySplitPairData^ splitPairData = gcnew SoftBodySplitPairData( softBody->getSplitPairData() );
	
	SoftBody^ s = gcnew SoftBody( softBody, meshData, splitPairData );
	
	_softBodies->Add( s );
	
	return s;
}
#pragma endregion

SceneDescription^ Scene::SaveToDescription()
{
	SceneDescription^ desc = gcnew SceneDescription();
	
	if( this->UnmanagedPointer->saveToDesc( *desc->UnmanagedPointer ) == false )
	{
		return nullptr;
	}else{
		desc->UserNotify = this->UserNotify;
		desc->FluidUserNotify = this->FluidUserNotify;
		desc->UserContactModify = this->UserContactModify;
		desc->UserContactReport = this->UserContactReport;
		desc->UserTriggerReport = this->UserTriggerReport;
		desc->Name = this->Name;
		desc->UserData = this->UserData;
	}
	
	return desc;
}

Actor^ Scene::CreateActor( ActorDescription^ actorDescription )
{
	if( actorDescription == nullptr )
		throw gcnew ArgumentNullException( "actorDescription" );
	if( actorDescription->IsValid() == false )
		throw gcnew ArgumentException( "Actor description is invalid" );
	
	{
		int index = 0;
		for each( ShapeDescription^ shape in actorDescription->Shapes )
		{
			if( shape->IsValid() == false )
				throw gcnew InvalidOperationException( "Shape description is invalid. Shape index: {0}" );
			
			index++;
		}
	}
	
	NxActor* actor = _scene->createActor( *actorDescription->UnmanagedPointer );
	if( actor == NULL )
		throw gcnew PhysXException( "Failed to create actor" );
	
	Actor^ a = gcnew Actor( actor );
	
	a->UserData = actorDescription->UserData;
	
	_actors->Add( a );
	
	return a;
}
Material^ Scene::CreateMaterial( MaterialDescription^ materialDescription )
{
	if( materialDescription == nullptr )
		throw gcnew ArgumentNullException( "materialDescription" );
	if( materialDescription->IsValid() == false )
		throw gcnew ArgumentException( "Material description is invalid" );
	
	NxMaterial* material = _scene->createMaterial( *materialDescription->UnmanagedPointer );
	if ( material == NULL )
		throw gcnew PhysXException( "Failed to create material" );
	
	Material^ mat = gcnew Material( material );
		mat->Name = materialDescription->Name;
		
	_materials->Add( mat );
	
	return mat;
}
Joint^ Scene::CreateJoint( JointDescription^ jointDescription )
{
	if( jointDescription == nullptr )
		throw gcnew ArgumentNullException( "jointDescription" );
	if( jointDescription->IsValid() == false )
		throw gcnew ArgumentException( "Joint description is invalid" );
	
	NxJoint* joint = _scene->createJoint( *jointDescription->UnmanagedPointer );
	if ( joint == NULL )
		throw gcnew PhysXException( "Failed to create joint" );
	
	Joint^ j;
	switch( jointDescription->Type )
	{
		case JointType::Cylindrical:
			j = gcnew CylindricalJoint( joint->isCylindricalJoint() );
		break;
		case JointType::D6:
			j = gcnew D6Joint( joint->isD6Joint() );
		break;
		case JointType::Distance:
			j = gcnew DistanceJoint( joint->isDistanceJoint() );
		break;
		case JointType::Fixed:
			j = gcnew FixedJoint( joint->isFixedJoint() );
		break;
		case JointType::PointInPlane:
			j = gcnew PointInPlaneJoint( joint->isPointInPlaneJoint() );
		break;
		case JointType::PointOnLine:
			j = gcnew PointOnLineJoint( joint->isPointOnLineJoint() );
		break;
		case JointType::Prismatic:
			j = gcnew PrismaticJoint( joint->isPrismaticJoint() );
		break;
		case JointType::Pulley:
			j = gcnew PulleyJoint( joint->isPulleyJoint() );
		break;
		case JointType::Revolute:
			j = gcnew RevoluteJoint( joint->isRevoluteJoint() );
		break;
		case JointType::Spherical:
			j = gcnew SphericalJoint( joint->isSphericalJoint() );
		break;
		
		default:
			throw gcnew PhysXException( "Joint type not supported" );
	}
	
	j->Name = jointDescription->Name;
	j->UserData = jointDescription->UserData;
	
	_joints->Add( j );
	
	return j;
}
Cloth^ Scene::CreateCloth( ClothDescription^ clothDescription )
{
	if( clothDescription == nullptr )
		throw gcnew ArgumentNullException( "clothDescription" );
	if( clothDescription->IsValid() == false )
		throw gcnew ArgumentException( "Cloth description is invalid" );
	
	NxCloth* cloth = _scene->createCloth( *clothDescription->UnmanagedPointer );
	if ( cloth == NULL )
		throw gcnew PhysXException( "Failed to create cloth" );
	
	Cloth^ c = gcnew Cloth( cloth, clothDescription->MeshData );
		c->UserData = clothDescription->UserData;
	
	_cloths->Add( c );
	
	return c;
}
ForceField^ Scene::CreateForceField( ForceFieldDescription^ forceFieldDescription )
{
	if( forceFieldDescription == nullptr )
		throw gcnew ArgumentNullException( "forceFieldDescription" );
	if( forceFieldDescription->IsValid() == false )
		throw gcnew ArgumentException( "Force field description is invalid" );
	
	NxForceField* forceField = _scene->createForceField( *forceFieldDescription->UnmanagedPointer );
	if ( forceField == NULL )
		throw gcnew PhysXException( "Failed to create force field" );
	
	ForceField^ f = gcnew ForceField( forceField );
		f->UserData = forceFieldDescription->UserData;
		
	_forceFields->Add( f );
	
	return f;
}
//ImplicitScreenMesh^ Scene::CreateImplicitScreenMesh( ImplicitScreenMeshDescription^ implicitScreenMeshDescription )
//{
//#if _DEBUG
//	if( implicitScreenMeshDescription == nullptr || implicitScreenMeshDescription->IsValid() == false )
//		throw gcnew PhysicsException( "Implicit Screen Mesh Description is Null or Invalid" );
//#endif
//	
//	NxImplicitScreenMesh* implicitScreenMesh = _scene->createImplicitScreenMesh( *implicitScreenMeshDescription->UnmanagedPointer );
//	
//	ImplicitScreenMesh^ i = ImplicitScreenMesh::FromUnmanagedPointer( this, implicitScreenMesh );
//	
//	_implicitScreenMeshes->Add( i );
//	
//	return i;
//}
StillDesign::PhysX::ControllerManager^ Scene::CreateControllerManager()
{
	ControllerManagerAllocator* a = new ControllerManagerAllocator();
	
	NxControllerManager* manager = NxCreateControllerManager( a );
	if ( manager == NULL )
		throw gcnew PhysXException( "Failed to create controller manager" );
	
	ControllerManager^ c = gcnew ControllerManager( manager, this );
	
	_controllerManagers->Add( c );
	
	return c;
}
Fluid^ Scene::CreateFluid( FluidDescription^ fluidDescription )
{
	if( fluidDescription == nullptr )
		throw gcnew ArgumentNullException( "fluidDescription" );
	if( fluidDescription->IsValid() == false )
		throw gcnew ArgumentException( "Fluid description is invalid" );
	
	NxFluid* f = _scene->createFluid( *fluidDescription->UnmanagedPointer );

	if( f == NULL )
		throw gcnew PhysXException( "Failed to create fluid" );
	
	Fluid^ fluid = gcnew Fluid( f, fluidDescription->ParticleWriteData, fluidDescription->ParticleDeletionIdWriteData, fluidDescription->ParticleCreationIdWriteData, fluidDescription->FluidPacketData );
		fluid->UserData = fluidDescription->UserData;
	
	_fluids->Add( fluid );
	
	return fluid;
}
ForceFieldLinearKernel^ Scene::CreateForceFieldLinearKernel( ForceFieldLinearKernelDescription^ kernelDescription )
{
	if( kernelDescription == nullptr )
		throw gcnew ArgumentNullException( "kernelDescription" );
	if( kernelDescription->IsValid() == false )
		throw gcnew ArgumentException( "Kernel description is invalid" );
	
	NxForceFieldLinearKernel* k = _scene->createForceFieldLinearKernel( *kernelDescription->UnmanagedPointer );
	
	if( k == NULL )
		throw gcnew PhysXException( "Failed to create force field linear kernel" );
	
	ForceFieldLinearKernel^ kernel = gcnew ForceFieldLinearKernel( k );
		kernel->UserData = kernelDescription->UserData;
	
	_forceFieldLinearKernels->Add( kernel );
	
	return kernel;
}
short Scene::CreateForceFieldMaterial()
{
	return _scene->createForceFieldMaterial();
}
void Scene::ReleaseForceFieldMaterial( short materialIndex )
{
	_scene->releaseForceFieldMaterial( materialIndex );
}
short Scene::CreateForceFieldVariety()
{
	return _scene->createForceFieldVariety();
}
void Scene::ReleaseForceFieldVariety( short varietyIndex )
{
	_scene->releaseForceFieldVariety( varietyIndex );
}
ForceFieldShapeGroup^ Scene::CreateForceFieldShapeGroup( ForceFieldShapeGroupDescription^ groupDescription )
{
	if( groupDescription == nullptr )
		throw gcnew ArgumentNullException( "groupDescription" );
	if( groupDescription->IsValid() == false )
		throw gcnew ArgumentException( "Group description invalid" );
	
	NxForceFieldShapeGroup* g = _scene->createForceFieldShapeGroup( *groupDescription->UnmanagedPointer );
	
	if( g == NULL )
		throw gcnew PhysXException( "Failed to create force field shape group" );
	
	ForceFieldShapeGroup^ group = gcnew ForceFieldShapeGroup( g );
		group->UserData = groupDescription->UserData;
	
	_forceFieldShapeGroups->Add( group );
	
	return group;
}

SweepCache^ Scene::CreateSweepCache()
{
	NxSweepCache* sweepCache = _scene->createSweepCache();
	
	return gcnew SweepCache( sweepCache, this );
}
SoftBody^ Scene::CreateSoftBody( SoftBodyDescription^ softBodyDescription )
{
	if( softBodyDescription == nullptr )
		throw gcnew ArgumentNullException( "softBodyDescription" );
	if( softBodyDescription->IsValid() == false )
		throw gcnew ArgumentException( "Soft body description invalid" );
	
	NxSoftBody* softBody = _scene->createSoftBody( *softBodyDescription->UnmanagedPointer );
	
	if( softBody == NULL )
		throw gcnew PhysXException( "Failed to create soft body" );
	
	SoftBody^ s = gcnew SoftBody( softBody, softBodyDescription->MeshData, softBodyDescription->SplitPairData );
		s->UserData = softBodyDescription->UserData;
		
	_softBodies->Add( s );
	
	return s;
}
Compartment^ Scene::CreateCompartment( CompartmentDescription^ compartmentDescription )
{
	if( compartmentDescription == nullptr )
		throw gcnew ArgumentNullException( "compartmentDescription" );
	if( compartmentDescription->IsValid() == false )
		throw gcnew ArgumentException( "Compartment description invalid" );
	
	NxCompartment* compartment = _scene->createCompartment( *compartmentDescription->UnmanagedPointer );
	
	if( compartment == NULL )
		throw gcnew PhysXException( "Failed to create compartment" );
	
	Compartment^ c = gcnew Compartment( compartment, this );
	
	_compartments->Add( c );
	
	return c;
}

//

void Scene::Simulate( float elapsedTime )
{
	_scene->simulate( elapsedTime );
}
void Scene::FlushStream()
{
	_scene->flushStream();
}
void Scene::FetchResults( SimulationStatus status, bool block )
{
	_scene->fetchResults( (NxSimulationStatus)status, block );
}
void Scene::FlushCaches()
{
	_scene->flushCaches();
}


void Scene::LockQueries()
{
	_scene->lockQueries();
}
void Scene::UnlockQueries()
{
	_scene->unlockQueries();
}
bool Scene::CheckResults( SimulationStatus status )
{
	return _scene->checkResults( (NxSimulationStatus)status  );
}
bool Scene::CheckResults( SimulationStatus status, bool block )
{
	return _scene->checkResults( (NxSimulationStatus)status, block );
}

bool Scene::CookFluidMeshHotspot( Bounds3 bounds, int packetSizeMultiplier, float restParticlePerMeter, float kernelRadiusMultiplier, float motionLimitMultiplier, float collisionDistanceMultiplier )
{
	return CookFluidMeshHotspot( bounds, packetSizeMultiplier, restParticlePerMeter, kernelRadiusMultiplier, motionLimitMultiplier, collisionDistanceMultiplier, nullptr, false );
}
bool Scene::CookFluidMeshHotspot( Bounds3 bounds, int packetSizeMultiplier, float restParticlePerMeter, float kernelRadiusMultiplier, float motionLimitMultiplier, float collisionDistanceMultiplier, Compartment^ compartment, bool forceStrictCookingFormat )
{
	ThrowIfDisposed( compartment, "compartment" );
	
	return _scene->cookFluidMeshHotspot( (NxBounds3)bounds, packetSizeMultiplier, restParticlePerMeter, kernelRadiusMultiplier, motionLimitMultiplier, collisionDistanceMultiplier, compartment == nullptr ? NULL : compartment->UnmanagedPointer, forceStrictCookingFormat );
}

ThreadPollResult Scene::PollForWork( ThreadWait waitType )
{
	return (ThreadPollResult)_scene->pollForWork( (NxThreadWait)waitType );
}
ThreadPollResult Scene::PollForBackgroundWork( ThreadWait waitType )
{
	return (ThreadPollResult)_scene->pollForBackgroundWork( (NxThreadWait)waitType );
}
void Scene::ResetPollForWork()
{
	_scene->resetPollForWork();
}
void Scene::ShutdownWorkerThreads()
{
	_scene->shutdownWorkerThreads();
}

String^ SceneDescription::Name::get()
{
	return _name;
}
void SceneDescription::Name::set( String^ value )
{
	_name = value;
}

// Overlap
array<Shape^>^ Scene::OverlappedShapes( Sphere sphere, ShapesType type )
{
	return OverlappedShapes( sphere, type, 0xFFFFFFFF, Nullable<GroupsMask>(), false );
}
array<Shape^>^ Scene::OverlappedShapes( Sphere sphere, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision )
{
	NxU32 n = _scene->getTotalNbShapes();
	NxShape** s = new NxShape*[ n ];
	
	NxGroupsMask* mask = groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL;
	unsigned int overlapCount = _scene->overlapSphereShapes( (NxSphere)sphere, (NxShapesType)type, n, s, NULL, activeGroups, mask, accurateCollision );
	
	array<Shape^>^ shapes = gcnew array<Shape^>( overlapCount );
	
	for( unsigned int x = 0; x < overlapCount; x++ )
	{
		shapes[ x ] = ObjectCache::GetObject<Shape^>( (intptr_t)s[ x ] );
	}
	
	delete[] s;
	s = NULL;
	
	return shapes;
}
int Scene::OverlappedShapes( Sphere sphere, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision, UserEntityShapeReport^ callback )
{
	NxGroupsMask* mask = groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL;
	
	return _scene->overlapSphereShapes( (NxSphere)sphere, (NxShapesType)type, 0, NULL, callback->UnmanagedPointer, activeGroups, mask, accurateCollision );
}
array<Shape^>^ Scene::OverlappedShapes( Bounds3 worldBounds, ShapesType type )
{
	return OverlappedShapes( worldBounds, type, 0xFFFFFFFF, Nullable<GroupsMask>(), false );
}
array<Shape^>^ Scene::OverlappedShapes( Bounds3 worldBounds, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision )
{
	NxU32 n = _scene->getTotalNbShapes();
	NxShape** s = new NxShape*[ n ];
	
	NxGroupsMask* mask = groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL;
	unsigned int overlapCount = _scene->overlapAABBShapes( (NxBounds3)worldBounds, (NxShapesType)type, n, s, NULL, activeGroups, mask, accurateCollision );
	
	array<Shape^>^ shapes = gcnew array<Shape^>( overlapCount );
	
	for( unsigned int x = 0; x < overlapCount; x++ )
	{
		shapes[ x ] = ObjectCache::GetObject<Shape^>( (intptr_t)s[ x ] );
	}
	
	delete[] s;
	s = NULL;
	
	return shapes;
}
int Scene::OverlappedShapes( Bounds3 worldBounds, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision, UserEntityShapeReport^ callback )
{
	NxGroupsMask* mask = groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL;
	
	return _scene->overlapAABBShapes( (NxBounds3)worldBounds, (NxShapesType)type, 0, NULL, callback->UnmanagedPointer, activeGroups, mask, accurateCollision );
}
array<Shape^>^ Scene::OverlappedShapes( Box worldBox, ShapesType type )
{
	return OverlappedShapes( worldBox, type, 0xFFFFFFFF, Nullable<GroupsMask>(), false );
}
array<Shape^>^ Scene::OverlappedShapes( Box worldBox, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision )
{
	NxU32 n = _scene->getTotalNbShapes();
	NxShape** s = new NxShape*[ n ];
	
	NxGroupsMask* mask = groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL;
	unsigned int overlapCount = _scene->overlapOBBShapes( (NxBox)worldBox, (NxShapesType)type, n, s, NULL, activeGroups, mask, accurateCollision );
	
	array<Shape^>^ shapes = gcnew array<Shape^>( overlapCount );
	
	for( unsigned int x = 0; x < overlapCount; x++ )
	{
		shapes[ x ] = ObjectCache::GetObject<Shape^>( (intptr_t)s[ x ] );
	}
	
	delete[] s;
	s = NULL;
	
	return shapes;
}
int Scene::OverlappedShapes( Box worldBox, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision, UserEntityShapeReport^ callback )
{
	NxGroupsMask* mask = groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL;
	
	return _scene->overlapOBBShapes( (NxBox)worldBox, (NxShapesType)type, 0, NULL, callback->UnmanagedPointer, activeGroups, mask, accurateCollision );
}
array<Shape^>^ Scene::OverlappedShapes( Capsule worldCapsule, ShapesType type )
{
	return OverlappedShapes( worldCapsule, type, 0xFFFFFFFF, Nullable<GroupsMask>(), false );
}
array<Shape^>^ Scene::OverlappedShapes( Capsule worldCapsule, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision )
{
	NxU32 n = _scene->getTotalNbShapes();
	NxShape** s = new NxShape*[ n ];
	
	NxGroupsMask* mask = groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL;
	unsigned int overlapCount = _scene->overlapCapsuleShapes( (NxCapsule)worldCapsule, (NxShapesType)type, n, s, NULL, activeGroups, mask, accurateCollision );
	
	array<Shape^>^ shapes = gcnew array<Shape^>( overlapCount );
	
	for( unsigned int x = 0; x < overlapCount; x++ )
	{
		shapes[ x ] = ObjectCache::GetObject<Shape^>( (intptr_t)s[ x ] );
	}
	
	delete[] s;
	s = NULL;
	
	return shapes;
}

int Scene::OverlappedShapes( Capsule worldCapsule, ShapesType type, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, bool accurateCollision, UserEntityShapeReport^ callback )
{
	NxGroupsMask* mask = groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL;
	
	return _scene->overlapCapsuleShapes( (NxCapsule)worldCapsule, (NxShapesType)type, 0, NULL, callback->UnmanagedPointer, activeGroups, mask, accurateCollision );
}
//

void Scene::SetGroupCollisionFlag( short group1, short group2, bool enable )
{
	_scene->setGroupCollisionFlag( group1, group2, enable );
}
bool Scene::GetGroupCollisionFlag( short group1, short group2 )
{
	return _scene->getGroupCollisionFlag( group1, group2 );
}

ConstraintDominance Scene::GetDominanceGroupPair( short group1, short group2 )
{
	return (ConstraintDominance)_scene->getDominanceGroupPair( group1, group2 );
}
void Scene::SetDominanceGroupPair( short group1, short group2, ConstraintDominance dominance )
{
	_scene->setDominanceGroupPair( group1, group2, (NxConstraintDominance)dominance );
}

SceneStatistics^ Scene::GetStatistics()
{
	return gcnew SceneStatistics( this );
}
SceneLimits^ Scene::GetLimits()
{
	return SceneLimits::FromScene( this );
}

array<PairFlag^>^ Scene::GetPairFlags()
{
	array<PairFlag^>^ f = gcnew array<PairFlag^>( _scene->getNbPairs() );
	
	NxPairFlag* flags = new NxPairFlag[ _scene->getNbPairs() ];
	_scene->getPairFlagArray( flags, _scene->getNbPairs() );
	for( unsigned int x = 0; x < _scene->getNbPairs(); x++ )
	{
		f[ x ] = gcnew PairFlag( flags[ x ] );
	}
	
	delete[] flags;
	
	return f;
}
void Scene::SetActorPairFlags( Actor^ actorA, Actor^ actorB, ContactPairFlag contactPairFlag )
{
	ThrowIfNullOrDisposed( actorA, "actorA" );
	ThrowIfNullOrDisposed( actorB, "actorB" );
	
	_scene->setActorPairFlags( *actorA->UnmanagedPointer, *actorB->UnmanagedPointer, (NxU32)contactPairFlag );
}
ContactPairFlag Scene::GetActorPairFlags( Actor^ actorA, Actor^ actorB )
{
	ThrowIfNullOrDisposed( actorA, "actorA" );
	ThrowIfNullOrDisposed( actorB, "actorB" );
	
	return (ContactPairFlag)_scene->getActorPairFlags( *actorA->UnmanagedPointer, *actorB->UnmanagedPointer );
}

ContactPairFlag Scene::GetShapePairFlags( Shape^ shapeA, Shape^ shapeB )
{
	ThrowIfNullOrDisposed( shapeA, "shapeA" );
	ThrowIfNullOrDisposed( shapeB, "shapeB" );
	
	return (ContactPairFlag)_scene->getShapePairFlags( *shapeA->UnmanagedPointer, *shapeB->UnmanagedPointer );
}
void Scene::SetShapePairFlags( Shape^ shapeA, Shape^ shapeB, ContactPairFlag contactPairFlag )
{
	ThrowIfNullOrDisposed( shapeA, "shapeA" );
	ThrowIfNullOrDisposed( shapeB, "shapeB" );
	
	_scene->setShapePairFlags( *shapeA->UnmanagedPointer, *shapeB->UnmanagedPointer, (NxContactPairFlag)contactPairFlag );
}

int Scene::GetActorGroupPairFlags( short group1, short group2 )
{
	return _scene->getActorGroupPairFlags( group1, group2 );
}
void Scene::SetActorGroupPairFlags( short group1, short group2, ContactPairFlag contactPairFlag )
{
	_scene->setActorGroupPairFlags( group1, group2, (NxContactPairFlag)contactPairFlag );
}
array<ActorGroupPair>^ Scene::GetActorGroupPairs()
{
	System::Collections::Generic::List<ActorGroupPair>^ pairs = gcnew System::Collections::Generic::List<ActorGroupPair>();
	
	NxActorGroupPair pair;
	NxU32 i = 0;
	for( unsigned int x = 0; x < _scene->getNbActorGroupPairs(); x++ )
	{
		_scene->getActorGroupPairArray( &pair, 1, i );
		
		if( i == 0 )
			break;
		else
			pairs->Add( (ActorGroupPair)pair );
	}
	
	return pairs->ToArray();
}

void Scene::SetFilterOperations( FilterOperation op0, FilterOperation op1, FilterOperation op2 )
{
	_scene->setFilterOps( (NxFilterOp)op0, (NxFilterOp)op1, (NxFilterOp)op2 );
}
void Scene::SetFilterBoolean( bool flag )
{
	_scene->setFilterBool( flag );
}
void Scene::SetFilterConstant0( GroupsMask mask )
{
	_scene->setFilterConstant0( (NxGroupsMask)mask );
}
void Scene::SetFilterConstant1( GroupsMask mask )
{
	_scene->setFilterConstant1( (NxGroupsMask)mask );
}
void Scene::GetFilterOperations( [Out] FilterOperation% op0, [Out] FilterOperation% op1, [Out] FilterOperation% op2 )
{
	NxFilterOp a, b, c;
	
	_scene->getFilterOps( a, b, c );
	
	op0 = (FilterOperation)a;
	op1 = (FilterOperation)b;
	op2 = (FilterOperation)c;
}
bool Scene::GetFilterBoolean()
{
	return _scene->getFilterBool();
}
GroupsMask Scene::GetFilterConstant0()
{
	return (GroupsMask)_scene->getFilterConstant0();
}
GroupsMask Scene::GetFilterConstant1()
{
	return (GroupsMask)_scene->getFilterConstant1();
}

DebugRenderable^ Scene::GetDebugRenderable()
{
	const NxDebugRenderable* data = _scene->getDebugRenderable();
	
	DebugRenderable^ r = gcnew DebugRenderable( data );
	
	return r;
}

#pragma region Raycast
#pragma region RaycastAnyBounds
bool Scene::RaycastAnyBounds( StillDesign::PhysX::Ray worldRay, ShapesType shapesType )
{
	return RaycastAnyBounds( worldRay, shapesType, 0xFFFFFFFF, NX_MAX_F32, Nullable<GroupsMask>() );
}
bool Scene::RaycastAnyBounds( StillDesign::PhysX::Ray worldRay, ShapesType shapesType, unsigned int groups, float maximumDistance, Nullable<GroupsMask> groupsMask )
{
	return _scene->raycastAnyBounds( (NxRay)worldRay, (NxShapesType)shapesType, groups, maximumDistance, groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL );
}
#pragma endregion

#pragma region RaycastAnyShape
bool Scene::RaycastAnyShape( StillDesign::PhysX::Ray worldRay, ShapesType shapeTypes )
{
	return RaycastAnyShape( worldRay, shapeTypes, 0xFFFFFFFF, NX_MAX_F32, Nullable<GroupsMask>(), nullptr );
}
bool Scene::RaycastAnyShape( StillDesign::PhysX::Ray worldRay, ShapesType shapeTypes, unsigned int groups, float maximumDistance, Nullable<GroupsMask> groupsMask, [Out] Shape^ cache )
{
	NxShape* cacheShape = (cache == nullptr ? NULL : cache->UnmanagedPointer);
	
	bool result = _scene->raycastAnyShape( (NxRay)worldRay, (NxShapesType)shapeTypes, groups, maximumDistance, groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL, &cacheShape );
	
	if( cacheShape != NULL )
		cache = ObjectCache::GetObject<Shape^>( (intptr_t)cacheShape );
	
	return result;
}
#pragma endregion

#pragma region RaycastAllBounds
int Scene::RaycastAllBounds( StillDesign::PhysX::Ray worldRay, UserRaycastReport^ userRaycastReport, ShapesType shapesType )
{
	return RaycastAllBounds( worldRay, userRaycastReport, shapesType, 0xFFFFFFFF, NX_MAX_F32, 0xFFFFFFFF, Nullable<GroupsMask>() );
}
int Scene::RaycastAllBounds( StillDesign::PhysX::Ray worldRay, UserRaycastReport^ userRaycastReport, ShapesType shapesType, unsigned int groups, float maximumDistance, unsigned int hintFlags, Nullable<GroupsMask> groupsMask )
{
	return _scene->raycastAllBounds( (NxRay)worldRay, *userRaycastReport->UnmanagedPointer, (NxShapesType)shapesType, groups, maximumDistance, hintFlags, groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL );
}
#pragma endregion

#pragma region RaycastAllShapes
int Scene::RaycastAllShapes( StillDesign::PhysX::Ray worldRay, UserRaycastReport^ userRaycastReport, ShapesType shapesType )
{
	return RaycastAllShapes( worldRay, userRaycastReport, shapesType, 0xFFFFFFFF, NX_MAX_F32, 0xFFFFFFFF, Nullable<GroupsMask>() );
}
int Scene::RaycastAllShapes( StillDesign::PhysX::Ray worldRay, UserRaycastReport^ userRaycastReport, ShapesType shapesType, unsigned int groups, float maximumDistance, unsigned int hintFlags, Nullable<GroupsMask> groupsMask )
{
	ThrowIfNull( userRaycastReport, "userRaycastReport" );
	
	return _scene->raycastAllShapes( (NxRay)worldRay, *userRaycastReport->UnmanagedPointer, (NxShapesType)shapesType, groups, maximumDistance, hintFlags, groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL );
}
array<RaycastHit^>^ Scene::RaycastAllShapes( StillDesign::PhysX::Ray worldRay, ShapesType shapeTypes )
{
	RaycastReport^ report = gcnew RaycastReport();
	
	RaycastAllShapes( worldRay, report, shapeTypes );
	
	return report->Hits->ToArray();
}
#pragma endregion

#pragma region RaycastClosestBounds
RaycastHit^ Scene::RaycastClosestBounds( StillDesign::PhysX::Ray worldRay, ShapesType shapeTypes )
{
	return RaycastClosestBounds( worldRay, shapeTypes, 0xFFFFFFFF, NX_MAX_F32, 0xFFFFFFFF, Nullable<GroupsMask>() );
}
RaycastHit^ Scene::RaycastClosestBounds( StillDesign::PhysX::Ray worldRay, ShapesType shapeTypes, unsigned int groups, float maximumDistance, unsigned int hintFlags, Nullable<GroupsMask> groupsMask )
{
	NxGroupsMask* mask = groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL;
	
	NxRaycastHit hit;
	_scene->raycastClosestBounds( (NxRay)worldRay, (NxShapesType)shapeTypes, hit, groups, maximumDistance, hintFlags, mask );
	
	return (RaycastHit^)hit;
}
#pragma endregion

#pragma region RaycastClosestBounds
RaycastHit^ Scene::RaycastClosestShape( StillDesign::PhysX::Ray worldRay, ShapesType shapeTypes )
{
	return RaycastClosestShape( worldRay, shapeTypes, 0xFFFFFFFF, NX_MAX_F32, 0xFFFFFFFF, Nullable<GroupsMask>() );
}
RaycastHit^ Scene::RaycastClosestShape( StillDesign::PhysX::Ray worldRay, ShapesType shapeTypes, unsigned int groups, float maximumDistance, unsigned int hintFlags, Nullable<GroupsMask> groupsMask )
{
	NxRaycastHit h;
	
	NxGroupsMask* mask = groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL;
	
	_scene->raycastClosestShape( (NxRay)worldRay, (NxShapesType)shapeTypes, h, groups, maximumDistance, hintFlags, mask );
	
	return (RaycastHit^)h;
}
#pragma endregion
#pragma endregion

// Box Sweeps
array<SweepQueryHit^>^ Scene::LinearObbSweep( Box worldBox, Vector3 motion, SweepFlags flags, Object^ userData )
{
	return LinearObbSweep( worldBox, motion, flags, userData, 0xFFFFFFFF, Nullable<GroupsMask>() );
}
array<SweepQueryHit^>^ Scene::LinearObbSweep( Box worldBox, Vector3 motion, SweepFlags flags, Object^ userData, unsigned int activeGroups, Nullable<GroupsMask> groupsMask )
{
	return LinearSweep<Box>( worldBox, motion, flags, userData, nullptr, activeGroups, groupsMask );
}
void Scene::LinearObbSweep( Box worldBox, Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback )
{
	LinearObbSweep( worldBox, motion, flags, userData, callback, 0xFFFFFFFF, Nullable<GroupsMask>() );
}
void Scene::LinearObbSweep( Box worldBox, Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback, unsigned int activeGroups, Nullable<GroupsMask> groupsMask )
{
	if( callback == nullptr )
		throw gcnew ArgumentNullException( "callback" );
	
	LinearSweep<Box>( worldBox, motion, flags, userData, callback, activeGroups, groupsMask );
}

// Capsule Sweeps
array<SweepQueryHit^>^ Scene::LinearCapsuleSweep( Capsule worldCapsule, Vector3 motion, SweepFlags flags, Object^ userData )
{
	return LinearCapsuleSweep( worldCapsule, motion, flags, userData, 0xFFFFFFFF, Nullable<GroupsMask>() );
}
array<SweepQueryHit^>^ Scene::LinearCapsuleSweep( Capsule worldCapsule, Vector3 motion, SweepFlags flags, Object^ userData, unsigned int activeGroups, Nullable<GroupsMask> groupsMask )
{
	return LinearSweep<Capsule>( worldCapsule, motion, flags, userData, nullptr, activeGroups, groupsMask );
}
void Scene::LinearCapsuleSweep( Capsule worldCapsule, Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback )
{
	LinearCapsuleSweep( worldCapsule, motion, flags, userData, callback, 0xFFFFFFFF, Nullable<GroupsMask>() );
}
void Scene::LinearCapsuleSweep( Capsule worldCapsule, Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback, unsigned int activeGroups, Nullable<GroupsMask> groupsMask )
{
	if( callback == nullptr )
		throw gcnew ArgumentNullException( "callback" );
	
	LinearSweep<Capsule>( worldCapsule, motion, flags, userData, callback, activeGroups, groupsMask );
}

generic<class T>
array<SweepQueryHit^>^ Scene::LinearSweep( T sweepObject, Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback, unsigned int activeGroups, Nullable<GroupsMask> groupsMask )
{
	{
		if( T::typeid != Box::typeid && T::typeid != Capsule::typeid )
			throw gcnew ArgumentException( "Invalid sweep object. Must be either a Box or Capsule" );
		
		if( (int)(flags & SweepFlags::Statics) == 0 && (int)(flags & SweepFlags::Dynamics) == 0 )
			throw gcnew ArgumentException( "flags", "Flags argument must be either or a combination of Statics and Dynamics" );
	}
	
	bool returnHits = ( callback == nullptr );
	
	int numberOfShapes;
	NxSweepQueryHit* hits;
	if( returnHits == true )
	{
		numberOfShapes = _scene->getTotalNbShapes();
		
		hits = new NxSweepQueryHit[ numberOfShapes ];
		ZeroMemory( hits, sizeof( NxSweepQueryHit ) * numberOfShapes );
	}else{
		numberOfShapes = 0;
	}
	
	NxVec3 m = StillDesign::PhysX::Math::Vector3ToNxVec3( motion );
	
	NxBox b = (NxBox)(Box());
	
	int shapesHit;
	if( T::typeid == Box::typeid )
	{
		Box box = (Box)sweepObject;
		
		shapesHit = _scene->linearOBBSweep( (NxBox)box, m, (NxU32)flags, NULL, numberOfShapes, hits, callback == nullptr ? NULL : callback->UnmanagedPointer, activeGroups, groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL );
	}else if( T::typeid == Capsule::typeid ){
		Capsule capsule = (Capsule)sweepObject;
		
		shapesHit = _scene->linearCapsuleSweep( (NxCapsule)capsule, m, (NxU32)flags, NULL, numberOfShapes, hits, callback == nullptr ? NULL : callback->UnmanagedPointer, activeGroups, groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL );
	}else{
		throw gcnew PhysXException( "Internal error; sweep object type is unsupported" );
	}
	
	// If callback is provided; we stop here no return
	if( returnHits == false )
	{
		return nullptr;
	}else{
		//// TODO Should this throw? probably not.
		//if( shapesHit >= numberOfShapes )
		//	throw gcnew PhysXException( "Internal error; number of returned shapes exceeds maximum shapes" );
		
		array<SweepQueryHit^>^ shapes = gcnew array<SweepQueryHit^>( shapesHit );
		for( int x = 0; x < shapesHit; x++ )
		{
			shapes[ x ] = gcnew SweepQueryHit( &(hits[ x ]), userData );
		}
		
		delete[] hits;
		hits = NULL;
		
		return shapes;
	}
}

// Cull Tests
array<Shape^>^ Scene::CullShapes( array<Plane>^ planes, ShapesType shapesType )
{
	return CullShapes( planes, shapesType, 0xFFFFFFFF, Nullable<GroupsMask>() );
}
array<Shape^>^ Scene::CullShapes( array<Plane>^ planes, ShapesType shapesType, unsigned int activeGroups, Nullable<GroupsMask> groupsMask )
{
	if( planes == nullptr )
		throw gcnew ArgumentNullException( "planes" );
	
	NxU32 n = _scene->getTotalNbShapes();
	
	NxShape** s = new NxShape*[ n ];
	
	NxPlane* p = new NxPlane[ planes->Length ];
	for( int x = 0; x < planes->Length; x++ )
	{
		Plane plane = planes[ x ];
		
#if GRAPHICS_XNA2 || GRAPHICS_SLIMDX
		p[ x ] = NxPlane( Math::Vector3ToNxVec3( plane.Normal ), plane.D );
#elif GRAPHICS_MDX
		p[ x ] = NxPlane( plane.A, plane.B, plane.C, plane.D );
#endif
	}
	
	NxGroupsMask* mask = groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL;
	unsigned int overlapCount = _scene->cullShapes( planes->Length, p, (NxShapesType)shapesType, n, s, NULL, activeGroups, mask );
	
	array<Shape^>^ shapes = gcnew array<Shape^>( overlapCount );
	
	for( unsigned int x = 0; x < overlapCount; x++ )
	{
		shapes[ x ] = ObjectCache::GetObject<Shape^>( (intptr_t)s[ x ] );
	}
	
	delete[] p, s;
	
	return shapes;
}
int Scene::CullShapes( array<Plane>^ planes, ShapesType shapesType, unsigned int activeGroups, Nullable<GroupsMask> groupsMask, UserEntityShapeReport^ callback )
{
	if( planes == nullptr )
		throw gcnew ArgumentNullException( "planes" );
	
	NxPlane* p = new NxPlane[ planes->Length ];
	for( int x = 0; x < planes->Length; x++ )
	{
		Plane plane = planes[ x ];
		
#if GRAPHICS_XNA2 || GRAPHICS_SLIMDX
		p[ x ] = NxPlane( Math::Vector3ToNxVec3( plane.Normal ), plane.D );
#elif GRAPHICS_MDX
		p[ x ] = NxPlane( plane.A, plane.B, plane.C, plane.D );
#endif
	}
	
	NxGroupsMask* mask = groupsMask.HasValue ? &((NxGroupsMask)groupsMask.Value) : NULL;
	unsigned int overlapCount = _scene->cullShapes( planes->Length, p, (NxShapesType)shapesType, 0, NULL, callback->UnmanagedPointer, activeGroups, mask );
	
	delete[] p;
	
	return overlapCount;
}

array<ActiveTransform^>^ Scene::GetActiveTransforms()
{
	NxU32 c;
	NxActiveTransform* t = _scene->getActiveTransforms( c );
	
	array<ActiveTransform^>^ transforms = gcnew array<ActiveTransform^>( c );
	
	for( unsigned int x = 0; x < c; x++ )
	{
		transforms[ x ] = gcnew ActiveTransform( *(t + x) );
	}
	
	return transforms;
}

//

//void Scene::Actors_onAdd( Object^ sender, Actor^ item )
//{
//	for each( Shape^ shape in item->Shapes )
//	{
//		_shapes->Add( shape );
//	}
//	
//	item->Shapes->onAdd += gcnew EventHandlerItem<Shape^>( this, &Scene::Actors_Shapes_onAdd );
//	item->Shapes->onRemove += gcnew EventHandlerItem<Shape^>( this, &Scene::Actors_Shapes_onRemove );
//}
//void Scene::Actors_onRemove( Object^ sender, Actor^ item )
//{
//	for each( Shape^ shape in item->Shapes )
//	{
//		_shapes->Remove( shape );
//	}
//	
//	item->Shapes->onAdd -= gcnew EventHandlerItem<Shape^>( this, &Scene::Actors_Shapes_onAdd );
//	item->Shapes->onRemove -= gcnew EventHandlerItem<Shape^>( this, &Scene::Actors_Shapes_onRemove );
//}
//void Scene::Actors_Shapes_onAdd( Object^ sender, Shape^ item )
//{
//	_shapes->Add( item );
//}
//void Scene::Actors_Shapes_onRemove( Object^ sender, Shape^ item )
//{
//	_shapes->Remove( item );
//}
//
//void Scene::_controllerManagerCollection_onAdd( System::Object^ sender, StillDesign::PhysX::ControllerManager^ e )
//{
//	e->Controllers->onAdd += gcnew EventHandlerItem<Controller^>( this, &Scene::Controllers_onAdd );
//	e->Controllers->onRemove += gcnew EventHandlerItem<Controller^>( this, &Scene::Controllers_onRemove );
//}
//void Scene::_controllerManagerCollection_onRemove( System::Object^ sender, StillDesign::PhysX::ControllerManager^ e )
//{
//	e->Controllers->onAdd -= gcnew EventHandlerItem<Controller^>( this, &Scene::Controllers_onAdd );
//	e->Controllers->onRemove -= gcnew EventHandlerItem<Controller^>( this, &Scene::Controllers_onRemove );
//}
//
//void Scene::Controllers_onAdd( System::Object^ sender, StillDesign::PhysX::Controller^ e )
//{
//	_controllerCollection->Add( e );
//	
//	Actor^ actor = e->Actor;
//	
//	_actors->Add( actor );
//}
//void Scene::Controllers_onRemove( System::Object^ sender, StillDesign::PhysX::Controller^ e )
//{
//	_controllerCollection->Remove( e );
//	
//	Actor^ actor = e->Actor;
//	
//	_actors->Remove( actor );
//}


// Properties

StillDesign::PhysX::Core^ Scene::Core::get()
{
	return _core;
}

ReadOnlyList< Actor^ >^ Scene::Actors::get()
{
	return _actors->ReadOnlyCollection;
}
//ReadOnlyList< Shape^ >^ Scene::Shapes::get()
//{
//	return _shapes->ReadOnlyCollection;
//}
ReadOnlyList< Material^ >^ Scene::Materials::get()
{
	return _materials->ReadOnlyCollection;
}
ReadOnlyList< StillDesign::PhysX::ControllerManager^ >^ Scene::ControllerManagers::get()
{
	return _controllerManagers->ReadOnlyCollection;
}
//ReadOnlyList< StillDesign::PhysX::Controller^ >^ Scene::Controllers::get()
//{
//	return _controllerCollection->ReadOnlyCollection;
//}
ReadOnlyList< Joint^ >^ Scene::Joints::get()
{
	return _joints->ReadOnlyCollection;
}
ReadOnlyList< Cloth^ >^ Scene::Cloths::get()
{
	return _cloths->ReadOnlyCollection;
}
ReadOnlyList< ForceField^ >^ Scene::ForceFields::get()
{
	return _forceFields->ReadOnlyCollection;
}
ReadOnlyList< Fluid^ >^ Scene::Fluids::get()
{
	return _fluids->ReadOnlyCollection;
}
ReadOnlyList< SoftBody^ >^ Scene::SoftBodies::get()
{
	return _softBodies->ReadOnlyCollection;
}
ReadOnlyList< Compartment^ >^ Scene::Compartments::get()
{
	return _compartments->ReadOnlyCollection;
}

ReadOnlyList< ForceFieldLinearKernel^ >^ Scene::ForceFieldLinearKernels::get()
{
	return _forceFieldLinearKernels->ReadOnlyCollection;
}
ReadOnlyList< ForceFieldShapeGroup^ >^ Scene::ForceFieldShapeGroups::get()
{
	return _forceFieldShapeGroups->ReadOnlyCollection;
}

//

StillDesign::PhysX::UserNotify^ Scene::UserNotify::get()
{
	return _userNotify;
}
void Scene::UserNotify::set( StillDesign::PhysX::UserNotify^ value )
{
	_userNotify = value;
	
	if( value == nullptr )
		_scene->setUserNotify( NULL );
	else
		_scene->setUserNotify( value->UnmanagedPointer );
}

StillDesign::PhysX::FluidUserNotify^ Scene::FluidUserNotify::get()
{
	return _fluidUserNotify;
}
void Scene::FluidUserNotify::set( StillDesign::PhysX::FluidUserNotify^ value )
{
	_fluidUserNotify = value;
	
	if( value == nullptr )
		_scene->setFluidUserNotify( NULL );
	else
		_scene->setFluidUserNotify( value->UnmanagedPointer );
}
StillDesign::PhysX::UserContactModify^ Scene::UserContactModify::get()
{
	return _userContactModify;
}
void Scene::UserContactModify::set( StillDesign::PhysX::UserContactModify^ value )
{
	_userContactModify = value;
	
	if( value == nullptr )
		_scene->setUserContactModify( NULL );
	else
		_scene->setUserContactModify( value->UnmanagedPointer );
}
StillDesign::PhysX::UserContactReport^ Scene::UserContactReport::get()
{
	return _userContactReport;
}
void Scene::UserContactReport::set( StillDesign::PhysX::UserContactReport^ value )
{
	_userContactReport = value;
	
	if( value == nullptr )
		_scene->setUserContactReport( NULL );
	else
		_scene->setUserContactReport( value->UnmanagedPointer );
}
StillDesign::PhysX::UserTriggerReport^ Scene::UserTriggerReport::get()
{
	return _userTriggerReport;
}
void Scene::UserTriggerReport::set( StillDesign::PhysX::UserTriggerReport^ value )
{
	_userTriggerReport = value;
	
	if( value == nullptr )
		_scene->setUserTriggerReport( NULL );
	else
		_scene->setUserTriggerReport( value->UnmanagedPointer );
}
StillDesign::PhysX::UserActorPairFiltering^ Scene::UserActorPairFiltering::get()
{
	return _userActorPairFiltering;
}
void Scene::UserActorPairFiltering::set( StillDesign::PhysX::UserActorPairFiltering^ value )
{
	_userActorPairFiltering = value;
	
	if( value == nullptr )
		_scene->setUserActorPairFiltering( NULL );
	else
		_scene->setUserActorPairFiltering( value->UnmanagedPointer );
}


String^ Scene::Name::get()
{
	return _name;
}
void Scene::Name::set( String^ value )
{
	_name = value;
}

Vector3 Scene::Gravity::get()
{
	NxVec3 gravity;
	_scene->getGravity( gravity );
	
	return Vector3( gravity.x, gravity.y, gravity.z );
}
void Scene::Gravity::set( Vector3 value )
{
	_scene->setGravity( NxVec3( value.X, value.Y, value.Z ) );
}

Material^ Scene::DefaultMaterial::get()
{
	return _defaultMaterial;
}
short Scene::HighestMaterialIndex::get()
{
	return _scene->getHighestMaterialIndex();
}

int Scene::NumberOfPairs::get()
{
	return _scene->getNbPairs();
}
int Scene::NumberOfActorGroupPairs::get()
{
	return _scene->getNbActorGroupPairs();
}


SceneFlag Scene::Flags::get()
{
	return (SceneFlag)_scene->getFlags();
}

SceneTimingInformation Scene::TimingInformation::get()
{
	float maxTimestep;
	unsigned int maxIterations;
	NxTimeStepMethod timestepMethod;
	unsigned int subSteps;
	
	_scene->getTiming( maxTimestep, maxIterations, timestepMethod, &subSteps );
	
	SceneTimingInformation timingInformation = SceneTimingInformation();
		timingInformation.MaximumTimestep = maxTimestep;
		timingInformation.MaximumIterations = (int)maxIterations;
		timingInformation.TimestepMethod = (TimestepMethod)timestepMethod;
		timingInformation.NumberOfSubSteps = (int)subSteps;
	
	return timingInformation;
}
void Scene::TimingInformation::set( SceneTimingInformation value )
{
	_scene->setTiming( value.MaximumTimestep, value.MaximumIterations, (NxTimeStepMethod)value.TimestepMethod );
}

bool Scene::IsWritable::get()
{
	return _scene->isWritable();
}

StillDesign::PhysX::SimulationType Scene::SimulationType::get()
{
	return (StillDesign::PhysX::SimulationType)_scene->getSimType();
}

int Scene::DynamicTreeRebuildRateHint::get()
{
	return _scene->getDynamicTreeRebuildRateHint();
}
void Scene::DynamicTreeRebuildRateHint::set( int value )
{
	_scene->setDynamicTreeRebuildRateHint( value );
}

int Scene::SolverBatchSize::get()
{
	return _scene->getSolverBatchSize();
}
void Scene::SolverBatchSize::set( int value )
{
	_scene->setSolverBatchSize( value );
}

Object^ Scene::UserData::get()
{
	return _userData;
}
void Scene::UserData::set( Object^ value )
{
	_userData = value;
}

NxScene* Scene::UnmanagedPointer::get()
{
	return _scene;
}

//

Scene::RaycastReport::RaycastReport() : UserRaycastReport()
{
	_hits = gcnew System::Collections::Generic::List<RaycastHit^>();
}

bool Scene::RaycastReport::OnHit( RaycastHit^ hit )
{
	_hits->Add( hit );
	
	return true;
}

System::Collections::Generic::List<RaycastHit^>^ Scene::RaycastReport::Hits::get()
{
	return _hits;
}