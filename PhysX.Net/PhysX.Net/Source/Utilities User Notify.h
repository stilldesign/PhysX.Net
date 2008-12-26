#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		ref class Core;
		ref class Scene;
		ref class Compartment;
		ref class Joint;
		ref class ForceField;
		ref class Actor;
		ref class Cloth;
		ref class SoftBody;
		ref class Fluid;
		ref class TriangleMesh;
		ref class ConvexMesh;
		ref class ClothMesh;
		ref class SoftBodyMesh;
		ref class CCDSkeleton;
		ref class HeightField;
		ref class Material;
		
		ref class SceneDescription;
		ref class CompartmentDescription;
		ref class JointDescription;
		ref class ForceFieldDescription;
		ref class ActorDescription;
		ref class ClothDescription;
		ref class SoftBodyDescription;
		ref class FluidDescription;
		ref class TriangleMeshDescription;
		ref class ConvexMeshDescription;
		ref class ClothMeshDescription;
		ref class SoftBodyMeshDescription;
		ref class HeightFieldDescription;
		ref class MaterialDescription;
		ref class SimpleTriangleMesh;
		
		namespace Utilities
		{
			class InternalUserNotify;
			
			public ref class UserNotify abstract
			{
				private:
					StillDesign::PhysX::Utilities::InternalUserNotify* _userNotify;
					
				public:
					UserNotify();
					~UserNotify();
				protected:
					!UserNotify();
					
				public:
					virtual void NotifyScene( int sceneNumber, Scene^ scene, String^ userProperties ) {}
					virtual void NotifyCompartment( Compartment^ compartment ) {}
					virtual void NotifyJoint( Joint^ joint, String^ userProperties ) {}
					virtual void NotifyForceField( ForceField^ forceField, String^ userProperties ) {}
					virtual void NotifyActor( Actor^ actor, String^ userProperties ) {}
					virtual void NotifyCloth( Cloth^ cloth, String^ userProperties ) {}
					virtual void NotifySoftBody( SoftBody^ softBody, String^ userProperties ) {}
					virtual void NotifyFluid( Fluid^ fluid, String^ userProperties ) {}
					virtual void NotifyTriangleMesh( TriangleMesh^ triangleMesh, String^ userProperties ) {}
					virtual void NotifyConvexMesh( ConvexMesh^ convexMesh, String^ userProperties ) {}
					virtual void NotifyClothMesh( ClothMesh^ clothMesh, String^ userProperties ) {}
					virtual void NotifySoftBodyMesh( SoftBodyMesh^ softBodyMesh, String^ userProperties ) {}
					virtual void NotifyCCDSkeleton( CCDSkeleton^ skeleton, String^ userProperties ) {}
					virtual void NotifyHeightField( HeightField^ heightField, String^ userProperties ) {}
					virtual void NotifyMaterial( Material^ material, String^ userProperties ) {}
					virtual void NotifySaveActor( Actor^ actor, String^ userProperties ) {}
					
					virtual void PreNotifyScene( int sceneNumber, SceneDescription^ scene, String^ userProperties ) {}
					virtual bool PreNotifyCompartment( CompartmentDescription^ compartment ) { return true; }
					virtual bool PreNotifyJoint( JointDescription^ joint, String^ userProperties ) { return true; }
					virtual bool PreNotifyForceField( ForceFieldDescription^ forceField, String^ userProperties ) { return true; }
					virtual bool PreNotifyActor( ActorDescription^ actor, String^ userProperties ) { return true; }
					virtual bool PreNotifyCloth( ClothDescription^ cloth, String^ userProperties ) { return true; }
					virtual bool PreNotifySoftBody( SoftBodyDescription^ softBody, String^ userProperties ) { return true; }
					virtual bool PreNotifyFluid( FluidDescription^ fluid, String^ userProperties ) { return true; }
					virtual bool PreNotifyTriangleMesh( TriangleMeshDescription^ triangleMesh, String^ userProperties ) { return true; }
					virtual bool PreNotifyConvexMesh( ConvexMeshDescription^ convexMesh, String^ userProperties ) { return true; }
					virtual bool PreNotifyClothMesh( ClothMeshDescription^ clothMesh, String^ userProperties ) { return true; }
					virtual bool PreNotifySoftBodyMesh( SoftBodyMeshDescription^ softBodyMesh, String^ userProperties ) { return true; }
					virtual bool PreNotifyCCDSkeleton( SimpleTriangleMesh^ skeletonMesh, String^ userProperties ) { return true; }
					virtual bool PreNotifyHeightField( HeightFieldDescription^ heightField, String^ userProperties ) { return true; }
					virtual bool PreNotifyMaterial( MaterialDescription^ material, String^ userProperties ) { return true; }
					
					virtual void PreNotifySceneInstance( String^ name, String^ sceneName, String^ userProperties, Matrix rootNode, int depth ) {}
					
					virtual void PreNotifySceneFailed( int sceneNumber, SceneDescription^ scene, String^ userProperties ) {}
					virtual void PreNotifyCompartmentFailed( CompartmentDescription^ compartment, String^ userProperties ) {}
					virtual void PreNotifyJointFailed( JointDescription^ joint, String^ userProperties ) {}
					virtual void PreNotifyForceFieldFailed( ForceFieldDescription^ forceField, String^ userProperties ) {}
					virtual void PreNotifyActorFailed( ActorDescription^ actor, String^ userProperties ) {}
					virtual void PreNotifyClothFailed( ClothDescription^ cloth, String^ userProperties ) {}
					virtual void PreNotifySoftBodyFailed( SoftBodyDescription^ softBody, String^ userProperties ) {}
					virtual void PreNotifyFluidFailed( FluidDescription^ fluid, String^ userProperties ) {}
					virtual void PreNotifyTriangleMeshFailed( TriangleMeshDescription^ triangleMesh, String^ userProperties ) {}
					virtual void PreNotifyConvexMeshFailed( ConvexMeshDescription^ convexMesh, String^ userProperties ) {}
					virtual void PreNotifyClothMeshFailed( ClothMeshDescription^ clothMesh, String^ userProperties ) {}
					virtual void PreNotifySoftBodyMeshFailed( SoftBodyMeshDescription^ softBodyMesh, String^ userProperties ) {}
					virtual void PreNotifyCCDSkeletonFailed( SimpleTriangleMesh^ skeletonMesh, String^ userProperties ) {}
					virtual void PreNotifyHeightFieldFailed( HeightFieldDescription^ heightField, String^ userProperties ) {}
					virtual void PreNotifyMaterialFailed( MaterialDescription^ material, String^ userProperties ) {}
					
					//generic<class T> where T : ref class
					//array<T>^ GetObjectsOfType();
					
					property StillDesign::PhysX::Utilities::InternalUserNotify* UnmanagedPointer
					{
						StillDesign::PhysX::Utilities::InternalUserNotify* get();
					}
			};
			
			class InternalUserNotify : public NXU_userNotify
			{
				private:
					gcroot<UserNotify^> _userNotify;
				
				public:
					InternalUserNotify( gcroot<UserNotify^> notify );
					
					virtual void  NXU_notifyScene (NxU32 sno, NxScene *scene, const char *userProperties);
					virtual void  NXU_notifyCompartment (NxCompartment *compartment) ;
					virtual void  NXU_notifyJoint (NxJoint *joint, const char *userProperties) ;
					virtual void  NXU_notifyForceField (NxForceField *effector, const char *userProperties) ;
					virtual void  NXU_notifyActor (NxActor *actor, const char *userProperties) ;
					virtual void  NXU_notifyCloth (NxCloth *cloth, const char *userProperties) ;
					virtual void  NXU_notifySoftBody (NxSoftBody *softBody, const char *userProperties) ;
					virtual void  NXU_notifyFluid (NxFluid *fluid, const char *userProperties) ;
					virtual void  NXU_notifyTriangleMesh (NxTriangleMesh *t, const char *userProperties) ;
					virtual void  NXU_notifyConvexMesh (NxConvexMesh *c, const char *userProperties) ;
					virtual void  NXU_notifyClothMesh (NxClothMesh *t, const char *userProperties) ;
					virtual void  NXU_notifySoftBodyMesh (NxSoftBodyMesh *t, const char *userProperties) ;
					virtual void  NXU_notifyCCDSkeleton (NxCCDSkeleton *t, const char *userProperties) ;
					virtual void  NXU_notifyHeightField (NxHeightField *t, const char *userProperties) ;
					virtual void  NXU_notifyMaterial (NxMaterial *t, const char *userProperties) ;
					virtual void  NXU_notifySaveActor (NxActor *pActor, const char **pUserProperties) ;
					virtual NxScene *  NXU_preNotifyScene (unsigned int sno, NxSceneDesc &scene, const char *userProperties) ;
					virtual bool  NXU_preNotifyCompartment (NxCompartmentDesc &compartment) ;
					virtual bool  NXU_preNotifyJoint (NxJointDesc &joint, const char *userProperties) ;
					virtual bool  NXU_preNotifyForceField (NxForceFieldDesc &effector, const char *userProperties) ;
					virtual bool  NXU_preNotifyActor (NxActorDesc &actor, const char *userProperties) ;
					virtual bool  NXU_preNotifyCloth (NxClothDesc &cloth, const char *userProperties) ;
					virtual bool  NXU_preNotifySoftBody (NxSoftBodyDesc &softBody, const char *userProperties) ;
					virtual bool  NXU_preNotifyFluid (NxFluidDesc &fluid, const char *userProperties) ;
					virtual bool  NXU_preNotifyTriangleMesh (NxTriangleMeshDesc &t, const char *userProperties) ;
					virtual bool  NXU_preNotifyConvexMesh (NxConvexMeshDesc &t, const char *userProperties) ;
					virtual bool  NXU_preNotifyClothMesh (NxClothMeshDesc &t, const char *userProperties) ;
					virtual bool  NXU_preNotifySoftBodyMesh (NxSoftBodyMeshDesc &t, const char *userProperties) ;
					virtual bool  NXU_preNotifyCCDSkeleton (NxSimpleTriangleMesh &t, const char *userProperties) ;
					virtual bool  NXU_preNotifyHeightField (NxHeightFieldDesc &t, const char *userProperties) ;
					virtual bool  NXU_preNotifyMaterial (NxMaterialDesc &t, const char *userProperties) ;
					virtual bool  NXU_preNotifySceneInstance (const char *name, const char *sceneName, const char *userProperties, NxMat34 &rootNode, NxU32 depth) ;
					virtual void  NXU_notifySceneFailed (unsigned int sno, NxSceneDesc &scene, const char *userProperties) ;
					virtual void  NXU_notifyCompartmentFailed (NxCompartmentDesc &compartment) ;
					virtual void  NXU_notifyJointFailed (NxJointDesc &joint, const char *userProperties) ;
					virtual void  NXU_notifySpringAndDamperEffectorFailed (NxSpringAndDamperEffectorDesc &effector, const char *userProperties) ;
					virtual void  NXU_notifyForceFieldFailed (NxForceFieldDesc &effector, const char *userProperties) ;
					virtual void  NXU_notifyActorFailed (NxActorDesc &actor, const char *userProperties) ;
					virtual void  NXU_notifyClothFailed (NxClothDesc &cloth, const char *userProperties) ;
					virtual void  NXU_notifySoftBodyFailed (NxSoftBodyDesc &softBody, const char *userProperties) ;
					virtual void  NXU_notifyFluidFailed (NxFluidDesc &fluid, const char *userProperties) ;
					virtual void  NXU_notifyTriangleMeshFailed (NxTriangleMeshDesc &t, const char *userProperties) ;
					virtual void  NXU_notifyConvexMeshFailed (NxConvexMeshDesc &t, const char *userProperties) ;
					virtual void  NXU_notifyClothMeshFailed (NxClothMeshDesc &t, const char *userProperties) ;
					virtual void  NXU_notifySoftBodyMeshFailed (NxSoftBodyMeshDesc &t, const char *userProperties) ;
					virtual void  NXU_notifyCCDSkeletonFailed (NxSimpleTriangleMesh &t, const char *userProperties) ;
					virtual void  NXU_notifyHeightFieldFailed (NxHeightFieldDesc &t, const char *userProperties) ;
					virtual void  NXU_notifyMaterialFailed (NxMaterialDesc &t, const char *userProperties) ;
			};
		};
	};
};