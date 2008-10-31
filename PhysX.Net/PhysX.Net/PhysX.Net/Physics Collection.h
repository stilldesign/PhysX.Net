#pragma once

#include "Enums.h"
#include "Groups Mask.h"
#include "NXU_Helper.h" 

class NxuPhysicsCollection;

using namespace System::Collections::Generic;

#define List System::Collections::Generic::List

namespace StillDesign
{
	namespace PhysX
	{
		ref class Actor;
		ref class Scene;
		ref class Core;
		ref class Joint;
		ref class Cloth;
		ref class SoftBody;
		ref class Fluid;
		ref class Material;
		ref class ConvexMesh;
		ref class TriangleMesh;
		ref class HeightField;
		ref class CCDSkeleton;
		ref class ForceField;
		ref class PairFlag;
		ref class Compartment;
		ref class ClothMesh;
		ref class SoftBodyMesh;
		ref class UserNotify;
		ref class CoreDescription;
		ref class ConvexMeshDescription;
		ref class TriangleMeshDescription;
		ref class HeightFieldDescription;
		ref class ForceFieldDescription;
		ref class CompartmentDescription;
		ref class ClothMeshDescription;
		ref class SoftBodyMeshDescription;
		ref class SceneDescription;
		
		namespace Utilities
		{
			ref class ErrorReport;
			ref class UserNotify;
			
			public ref class PhysicsCollection
			{
				private:
					NXU::NxuPhysicsCollection* _physicsCollection;
					
					CoreDescription^ _coreDesc;
					List<ConvexMeshDescription^>^ _convexMeshDesc;
					List<TriangleMeshDescription^>^ _triangleMeshDesc;
					List<HeightFieldDescription^>^ _heightFieldDesc;
					//List<CCDSkeletonDe
					List<ClothMeshDescription^>^ _clothMeshDesc;
					List<SoftBodyMeshDescription^>^ _sofyBodyMeshDesc;
					List<SceneDescription^>^ _sceneDesc;
					
				public:
					PhysicsCollection();
				internal:
					PhysicsCollection( NXU::NxuPhysicsCollection* collection );
					~PhysicsCollection();
				protected:
					!PhysicsCollection();
				
				public:
					bool InstantiateCollection( Core^ core );
					bool InstantiateCollection( Core^ core, Scene^ scene );
					bool InstantiateCollection( Core^ core, Scene^ scene, Nullable<Matrix> rootNode, UserNotify^ userNotify );
					
					bool AddParameter( PhysicsParameter parameter, float value );
					
					bool AddCore( Core^ core );
					
					bool AddScene( Scene^ scene );
					bool AddScene( Scene^ scene, String^ userProperties, String^ id );
					
					bool AddEntireScene( Scene^ scene );
					// TODO: Add NXU_userNotify
					bool AddEntireScene( Scene^ scene, String^ userProperties, String^ id );
					
					bool AddActor( Actor^ actor );
					bool AddActor( Actor^ actor, String^ userProperties, String^ id );
					
					bool AddJoint( Joint^ joint );
					bool AddJoint( Joint^ joint, String^ userProperties, String^ id );
					
					bool AddCloth( Cloth^ cloth );
					bool AddCloth( Cloth^ cloth, String^ userProperties, String^ id );
					
					bool AddSoftBody( SoftBody^ softBody );
					bool AddSoftBody( SoftBody^ softBody, String^ userProperties, String^ id );
					
					bool AddFluid( Fluid^ fluid );
					bool AddFluid( Fluid^ fluid, String^ userProperties, String^ id );
					
					bool AddMaterial( Material^ material );
					bool AddMaterial( Material^ material, String^ userProperties, String^ id );
					
					bool AddConvexMesh( ConvexMesh^ convexMesh );
					bool AddConvexMesh( ConvexMesh^ convexMesh, String^ userProperties, String^ id );
					
					bool AddTriangleMesh( TriangleMesh^ triangleMesh );
					bool AddTriangleMesh( TriangleMesh^ triangleMesh, String^ userProperties, String^ id );
					
					bool AddHeightField( HeightField^ heightField );
					bool AddHeightField( HeightField^ heightField, String^ userProperties, String^ id );
					
					bool AddCCDSkeleton( CCDSkeleton^ skeleton );
					bool AddCCDSkeleton( CCDSkeleton^ skeleton, String^ userProperties, String^ id );
					
					bool AddForceField( ForceField^ forceField );
					bool AddForceField( ForceField^ forceField, String^ userProperties, String^ id );
					
					//bool AddPairFlag( PairFlag^ pairFlag );
					//bool AddPairFlag( PairFlag^ pairFlag, String^ userProperties, String^ id );
					
					bool AddGroupCollisionFlag( int group1, int group2, bool enabled );
					
					bool AddActorGroupFlag( int group1, int group2, ContactPairFlag flag );
					
					bool SetFilterOperations( bool active, FilterOperation op0, FilterOperation op1, FilterOperation op2, GroupsMask filterConstant0, GroupsMask filterConstant1 );
					
					bool AddCompartment( Compartment^ compartment );
					bool AddCompartment( Compartment^ compartment, String^ id );
					
					bool AddClothMesh( ClothMesh^ clothMesh );
					bool AddClothMesh( ClothMesh^ clothMesh, String^ id );
					
					bool AddSoftBodyMesh( SoftBodyMesh^ softBodyMesh );
					bool AddSoftBodyMesh( SoftBodyMesh^ softBodyMesh, String^ id );
					
					bool AddSceneInstance( String^ instanceId, String^ sceneName, Matrix rootNode );
					bool AddSceneInstance( String^ instanceId, String^ sceneName, Matrix rootNode, bool ignorePlane, String^ userProperties );
					
					bool AddToCurrentSceneInstance( String^ instanceId, String^ sceneName, Matrix rootNode );
					bool AddToCurrentSceneInstance( String^ instanceId, String^ sceneName, Matrix rootNode, bool ignorePlane, String^ userProperties );
					
					bool CloseCurrentSceneInstance();
					
					String^ GetSceneName( int sceneNumber );
					int GetSceneCount();
					int GetSceneInstanceCount();
					
					String^ GetSceneInstanceName( int sceneNumber );
					String^ GetSceneInstanceSceneName( int sceneNumber );
					
					void ReleasePersistentMemory();
					
					void SetUseClothActiveState( bool state );
					void SetUseSoftBodyActiveState( bool state );
					void SetAutoGenerateCCDSkeletons( bool state, float shrink, int maxV );
					
					int CreateCCDSkeletons();
					int CreateCCDSkeletons( float shrink, int maxV );
					
					bool AutoGenerateCCDSkeletons( Actor^ actor);
					bool AutoGenerateCCDSkeletons( Actor^ actor, float shrink, int maxV );
					
					Dictionary<String^, String^>^ ParseUserProperties( String^ userProperties );
					String^ GetKeyValue( String^ userProperties, String^ key );
					
					void SetEndianMode( bool processorEndian );
					void SetEndianMode( bool processorEndian, bool endianSave );
					
					//
					
				internal:
					property NXU::NxuPhysicsCollection* UnmanagedPointer
					{
						NXU::NxuPhysicsCollection* get();
					}
			};
		};
	};
};

#undef List