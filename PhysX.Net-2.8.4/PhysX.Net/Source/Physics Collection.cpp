#include "StdAfx.h"

#include "Physics Collection.h"
#include "Functions.h"
#include "Core.h"
#include "Scene.h"
#include "Actor.h"
#include "Soft Body.h"
#include "Cloth.h"
#include "Compartment.h"
#include "User Notify.h"
#include "Pair Flag.h"
#include "Core Description.h"
#include <NXU_customcopy.h>
#include "Scene Description.h"
#include "Utilities User Notify.h"

using namespace StillDesign::PhysX;
using namespace StillDesign::PhysX::Utilities;

#define List System::Collections::Generic::List

PhysicsCollection::PhysicsCollection()
{
	_physicsCollection = new NXU::NxuPhysicsCollection();
	
	_convexMeshDesc = gcnew List<ConvexMeshDescription^>();
	_triangleMeshDesc = gcnew List<TriangleMeshDescription^>();
	_heightFieldDesc = gcnew List<HeightFieldDescription^>();
	_clothMeshDesc = gcnew List<ClothMeshDescription^>();
	_sofyBodyMeshDesc = gcnew List<SoftBodyMeshDescription^>();
	_sceneDesc = gcnew List<SceneDescription^>();
}
PhysicsCollection::PhysicsCollection( NXU::NxuPhysicsCollection* collection )
{
	_physicsCollection = collection;
	
	//NXU::CustomCopy copy;
	//
	//{
	//	NxPhysicsSDKDesc* d = new NxPhysicsSDKDesc();
	//	collection->mSDK.copyTo( *d, copy );
	//	_coreDesc = gcnew CoreDescription( d );
	//}
	//
	//for each( NXU::NxSceneDesc* sceneDesc in collection->mScenes )
	//{
	//	NxSceneDesc* d = new NxSceneDesc();
	//	sceneDesc->copyTo( *d, copy );
	//	
	//	SceneDescription^ desc = gcnew SceneDescription( d );
	//	
	//	_sceneDesc->Add( desc );
	//}
}
PhysicsCollection::~PhysicsCollection()
{
	this->!PhysicsCollection();
}
PhysicsCollection::!PhysicsCollection()
{
	SAFE_DELETE( _physicsCollection );
}

//

bool PhysicsCollection::InstantiateCollection( Core^ core )
{
	return InstantiateCollection( core, nullptr, Nullable<Matrix>(), nullptr );
}
bool PhysicsCollection::InstantiateCollection( Core^ core, Scene^ scene )
{
	return InstantiateCollection( core, scene, Nullable<Matrix>(), nullptr );
}
bool PhysicsCollection::InstantiateCollection( Core^ core, Scene^ scene, Nullable<Matrix> rootNode, StillDesign::PhysX::Utilities::UserNotify^ userNotify )
{
	ThrowIfNullOrDisposed( core, "core" );
	ThrowIfDisposed( scene, "scene" );
	
	NxMat34 r;
	if( rootNode.HasValue )
		r = Math::MatrixToMat34( rootNode.Value );
	
	NXU_userNotify* n;
	if( userNotify == nullptr )
		n = new InternalUserNotify();
	else
		n = userNotify->UnmanagedPointer;
	
	NxScene* s = (scene == nullptr ? NULL : scene->UnmanagedPointer);
	
	bool result = NXU::instantiateCollection( _physicsCollection, *core->UnmanagedPointer, s, rootNode.HasValue ? &r : NULL, n );
	
	return result;
}

bool PhysicsCollection::AddParameter( PhysicsParameter parameter, float value )
{
	return NXU::addParameter( *_physicsCollection, (NxU32)parameter, value );
}

bool PhysicsCollection::AddCore( Core^ core )
{
	return NXU::addPhysicsSDK( *_physicsCollection, *core->UnmanagedPointer );
}

bool PhysicsCollection::AddScene( Scene^ scene )
{
	return NXU::addScene( *_physicsCollection, *scene->UnmanagedPointer );
}
bool PhysicsCollection::AddScene( Scene^ scene, String^ userProperties, String^ id )
{
	return NXU::addScene( *_physicsCollection, *scene->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddEntireScene( Scene^ scene )
{
	return NXU::addEntireScene( *_physicsCollection, *scene->UnmanagedPointer );
}
bool PhysicsCollection::AddEntireScene( Scene^ scene, String^ userProperties, String^ id )
{
	return NXU::addEntireScene( *_physicsCollection, *scene->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddActor( Actor^ actor )
{
	return NXU::addActor( *_physicsCollection, *actor->UnmanagedPointer );
}
bool PhysicsCollection::AddActor( Actor^ actor, String^ userProperties, String^ id )
{
	return NXU::addActor( *_physicsCollection, *actor->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddJoint( Joint^ joint )
{
	return NXU::addJoint( *_physicsCollection, *joint->UnmanagedPointer );
}
bool PhysicsCollection::AddJoint( Joint^ joint, String^ userProperties, String^ id )
{
	return NXU::addJoint( *_physicsCollection, *joint->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddCloth( Cloth^ cloth )
{
	return NXU::addCloth( *_physicsCollection, *cloth->UnmanagedPointer );
}
bool PhysicsCollection::AddCloth( Cloth^ cloth, String^ userProperties, String^ id )
{
	return NXU::addCloth( *_physicsCollection, *cloth->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddSoftBody( SoftBody^ softBody )
{
	return NXU::addSoftBody( *_physicsCollection, *softBody->UnmanagedPointer );
}
bool PhysicsCollection::AddSoftBody( SoftBody^ softBody, String^ userProperties, String^ id )
{
	return NXU::addSoftBody( *_physicsCollection, *softBody->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddFluid( Fluid^ fluid )
{
	return NXU::addFluid( *_physicsCollection, *fluid->UnmanagedPointer );
}
bool PhysicsCollection::AddFluid( Fluid^ fluid, String^ userProperties, String^ id )
{
	return NXU::addFluid( *_physicsCollection, *fluid->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddMaterial( Material^ material )
{
	return NXU::addMaterial( *_physicsCollection, *material->UnmanagedPointer );
}
bool PhysicsCollection::AddMaterial( Material^ material, String^ userProperties, String^ id )
{
	return NXU::addMaterial( *_physicsCollection, *material->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddConvexMesh( ConvexMesh^ convexMesh )
{
	return NXU::addConvexMesh( *_physicsCollection, *convexMesh->UnmanagedPointer );
}
bool PhysicsCollection::AddConvexMesh( ConvexMesh^ convexMesh, String^ userProperties, String^ id )
{
	return NXU::addConvexMesh( *_physicsCollection, *convexMesh->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddTriangleMesh( TriangleMesh^ triangleMesh )
{
	return NXU::addTriangleMesh( *_physicsCollection, *triangleMesh->UnmanagedPointer );
}
bool PhysicsCollection::AddTriangleMesh( TriangleMesh^ triangleMesh, String^ userProperties, String^ id )
{
	return NXU::addTriangleMesh( *_physicsCollection, *triangleMesh->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddHeightField( HeightField^ heightField )
{
	return NXU::addHeightField( *_physicsCollection, *heightField->UnmanagedPointer );
}
bool PhysicsCollection::AddHeightField( HeightField^ heightField, String^ userProperties, String^ id )
{
	return NXU::addHeightField( *_physicsCollection, *heightField->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddCCDSkeleton( CCDSkeleton^ skeleton )
{
	return NXU::addCCDSkeleton( *_physicsCollection, *skeleton->UnmanagedPointer );
}
bool PhysicsCollection::AddCCDSkeleton( CCDSkeleton^ skeleton, String^ userProperties, String^ id )
{
	return NXU::addCCDSkeleton( *_physicsCollection, *skeleton->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddForceField( ForceField^ forceField )
{
	return NXU::addForceField( *_physicsCollection, *forceField->UnmanagedPointer );
}
bool PhysicsCollection::AddForceField( ForceField^ forceField, String^ userProperties, String^ id )
{
	return NXU::addForceField( *_physicsCollection, *forceField->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
}

//bool PhysicsCollection::AddPairFlag( PairFlag^ pairFlag )
//{
//	return NXU::addPairFlag( *_physicsCollection, *pairFlag );
//}
//bool PhysicsCollection::AddPairFlag( PairFlag^ pairFlag, String^ userProperties, String^ id )
//{
//	return NXU::addPairFlag( *_physicsCollection, *pairFlag->UnmanagedPointer, Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( id ) );
//}

bool PhysicsCollection::AddGroupCollisionFlag( int group1, int group2, bool enabled )
{
	return NXU::addGroupCollisionFlag( *_physicsCollection, group1, group2, enabled );
}

bool PhysicsCollection::AddActorGroupFlag( int group1, int group2, ContactPairFlag flag )
{
	return NXU::addActorGroupFlag( *_physicsCollection, group1, group2, (NxU32)flag );
}

bool PhysicsCollection::SetFilterOperations( bool active, FilterOperation op0, FilterOperation op1, FilterOperation op2, GroupsMask filterConstant0, GroupsMask filterConstant1 )
{
	return NXU::setFilterOps( *_physicsCollection, active, (NxFilterOp)op0, (NxFilterOp)op1, (NxFilterOp)op2, (NxGroupsMask)filterConstant0, (NxGroupsMask)filterConstant1 );
}

bool PhysicsCollection::AddCompartment( Compartment^ compartment )
{
	return NXU::addCompartment( *_physicsCollection, *compartment->UnmanagedPointer );
}
bool PhysicsCollection::AddCompartment( Compartment^ compartment, String^ id )
{
	return NXU::addCompartment( *_physicsCollection, *compartment->UnmanagedPointer, Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddClothMesh( ClothMesh^ clothMesh )
{
	return NXU::addClothMesh( *_physicsCollection, *clothMesh->UnmanagedPointer );
}
bool PhysicsCollection::AddClothMesh( ClothMesh^ clothMesh, String^ id )
{
	return NXU::addClothMesh( *_physicsCollection, *clothMesh->UnmanagedPointer, Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddSoftBodyMesh( SoftBodyMesh^ softBodyMesh )
{
	return NXU::addSoftBodyMesh( *_physicsCollection, *softBodyMesh->UnmanagedPointer );
}
bool PhysicsCollection::AddSoftBodyMesh( SoftBodyMesh^ softBodyMesh, String^ id )
{
	return NXU::addSoftBodyMesh( *_physicsCollection, *softBodyMesh->UnmanagedPointer, Functions::ManagedToUnmanagedString( id ) );
}

bool PhysicsCollection::AddSceneInstance( String^ instanceId, String^ sceneName, Matrix rootNode )
{
	return NXU::addSceneInstance( *_physicsCollection, Functions::ManagedToUnmanagedString( instanceId ), Functions::ManagedToUnmanagedString( sceneName ), Math::MatrixToMat34( rootNode ) );
}
bool PhysicsCollection::AddSceneInstance( String^ instanceId, String^ sceneName, Matrix rootNode, bool ignorePlane, String^ userProperties )
{
	return NXU::addSceneInstance( *_physicsCollection, Functions::ManagedToUnmanagedString( instanceId ), Functions::ManagedToUnmanagedString( sceneName ), Math::MatrixToMat34( rootNode ), ignorePlane, Functions::ManagedToUnmanagedString( userProperties ) );
}

bool PhysicsCollection::AddToCurrentSceneInstance( String^ instanceId, String^ sceneName, Matrix rootNode )
{
	return NXU::addToCurrentSceneInstance( *_physicsCollection, Functions::ManagedToUnmanagedString( instanceId ), Functions::ManagedToUnmanagedString( sceneName ), Math::MatrixToMat34( rootNode ) );
}
bool PhysicsCollection::AddToCurrentSceneInstance( String^ instanceId, String^ sceneName, Matrix rootNode, bool ignorePlane, String^ userProperties )
{
	return NXU::addToCurrentSceneInstance( *_physicsCollection, Functions::ManagedToUnmanagedString( instanceId ), Functions::ManagedToUnmanagedString( sceneName ), Math::MatrixToMat34( rootNode ), ignorePlane, Functions::ManagedToUnmanagedString( userProperties ) );
}

bool PhysicsCollection::CloseCurrentSceneInstance()
{
	return NXU::closeCurrentSceneInstance( *_physicsCollection );
}

String^ PhysicsCollection::GetSceneName( int sceneNumber )
{
	return Functions::UnmanagedToManagedString( NXU::getSceneName( *_physicsCollection, sceneNumber ) );
}
int PhysicsCollection::GetSceneCount()
{
	return NXU::getSceneCount( *_physicsCollection );
}
int PhysicsCollection::GetSceneInstanceCount()
{
	return NXU::getSceneInstanceCount( *_physicsCollection );
}

String^ PhysicsCollection::GetSceneInstanceName( int sceneNumber )
{
	return Functions::UnmanagedToManagedString( NXU::getSceneInstanceName( *_physicsCollection, sceneNumber ) );
}
String^ PhysicsCollection::GetSceneInstanceSceneName( int sceneNumber )
{
	return Functions::UnmanagedToManagedString( NXU::getSceneInstanceSceneName( *_physicsCollection, sceneNumber ) );
}

void PhysicsCollection::ReleasePersistentMemory()
{
	NXU::releasePersistentMemory();
}

void PhysicsCollection::SetUseClothActiveState( bool state )
{
	NXU::setUseClothActiveState( state );
}
void PhysicsCollection::SetUseSoftBodyActiveState( bool state )
{
	NXU::setUseSoftBodyActiveState( state );
}
void PhysicsCollection::SetAutoGenerateCCDSkeletons( bool state, float shrink, int maxV )
{
	NXU::setAutoGenerateCCDSkeletons( state, shrink, maxV );
}

int PhysicsCollection::CreateCCDSkeletons()
{
	return NXU::createCCDSkeletons( *_physicsCollection );
}
int PhysicsCollection::CreateCCDSkeletons( float shrink, int maxV )
{
	return NXU::createCCDSkeletons( *_physicsCollection, shrink, maxV );
}

bool PhysicsCollection::AutoGenerateCCDSkeletons( Actor^ actor )
{
	return NXU::autoGenerateCCDSkeletons( actor->UnmanagedPointer );
}
bool PhysicsCollection::AutoGenerateCCDSkeletons( Actor^ actor, float shrink, int maxV )
{
	return NXU::autoGenerateCCDSkeletons( actor->UnmanagedPointer, shrink, maxV );
}

Dictionary<String^, String^>^ PhysicsCollection::ParseUserProperties( String^ userProperties )
{
	NxU32 count;
	const char** p = NXU::parseUserProperties( Functions::ManagedToUnmanagedString( userProperties ), count );
	
	Dictionary<String^, String^>^ props = gcnew Dictionary<String^, String^>();
	for( unsigned int x = 0; x < count; x += 2 )
	{
		//String^ key = Functions::UnmanagedToManagedString( p
		
		//props->Add( 
	}
	
	throw gcnew NotImplementedException();
}
String^ PhysicsCollection::GetKeyValue( String^ userProperties, String^ key )
{
	return Functions::UnmanagedToManagedString( NXU::getKeyValue( Functions::ManagedToUnmanagedString( userProperties ), Functions::ManagedToUnmanagedString( key ) ) );
}

void PhysicsCollection::SetEndianMode( bool processorEndian )
{
	NXU::setEndianMode( processorEndian );
}
void PhysicsCollection::SetEndianMode( bool processorEndian, bool endianSave )
{
	NXU::setEndianMode( processorEndian, endianSave );
}

//

NXU::NxuPhysicsCollection* PhysicsCollection::UnmanagedPointer::get()
{
	return _physicsCollection;
}

#undef List