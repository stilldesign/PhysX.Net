#include "StdAfx.h"

#include "Utilities User Notify.h"
#include "Core.h"
#include "Functions.h"
#include "Object Cache.h"
#include "Compartment Description.h"
#include "Cylindrical Joint Description.h"
#include "Force Field Description.h"
#include "Material Description.h"

using namespace StillDesign::PhysX::Utilities;

UserNotify::UserNotify()
{
	_userNotify = new StillDesign::PhysX::Utilities::InternalUserNotify( this );
}
UserNotify::~UserNotify()
{
	this->!UserNotify();
}
UserNotify::!UserNotify()
{
	SAFE_DELETE( _userNotify );
}

StillDesign::PhysX::Utilities::InternalUserNotify* UserNotify::UnmanagedPointer::get()
{
	return _userNotify;
}

//generic<class T>
//array<T>^ UserNotify::GetObjectsOfType()
//{
//	System::Collections::Generic::List<T>^ items = gcnew System::Collections::Generic::List<T>();
//	
//	for each( intptr_t key in ObjectCache::Cache->Keys )
//	{
//		if( dynamic_cast<T>( ObjectCache::Cache[ key ] ) != nullptr )
//		{
//			items->Add( (T)ObjectCache::Cache[ key ] );
//		}
//	}
//	
//	return items->ToArray();
//}

//

InternalUserNotify::InternalUserNotify( gcroot<UserNotify^> notify )
{
	_userNotify = notify;
}

void InternalUserNotify::NXU_notifyScene (NxU32 sno, NxScene *scene, const char *userProperties)
{
	Core^ core = ObjectCache::GetObject<Core^>( (intptr_t)(&scene->getPhysicsSDK()) );
	core->AddScene( scene );
	
	_userNotify->NotifyScene( sno, ObjectCache::GetObject<Scene^>( (intptr_t)scene ), ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifyCompartment (NxCompartment *compartment)
{
	System::Collections::Generic::List<Scene^>^ items = gcnew System::Collections::Generic::List<Scene^>();
	
	for each( intptr_t key in ObjectCache::Cache->Keys )
	{
		if( dynamic_cast<Scene^>( ObjectCache::Cache[ key ] ) != nullptr )
		{
			items->Add( (Scene^)ObjectCache::Cache[ key ] );
		}
	}
	
	Scene^ parentScene = nullptr;
	
	array<Scene^>^ scenes = items->ToArray(); //ObjectCache::GetObjectsOfType<Scene^>();
	for each( Scene^ scene in scenes )
	{
		NxScene* s = scene->UnmanagedPointer;
		
		NxCompartment* c;
		for( unsigned int x = 0; x < s->getNbCompartments(); x++ )
		{
			NxU32 i = x;
			s->getCompartmentArray( &c, 1, i );
			if( compartment == c )
			{
				parentScene = scene;
				break;
			}
		}
		
		if( parentScene != nullptr )
			break;
	}
	
	if( parentScene == nullptr )
		Debug::Assert( "Could not find parent scene for compartment" );
	
	Compartment^ c = gcnew Compartment( compartment, parentScene );
	
	_userNotify->NotifyCompartment( ObjectCache::GetObject<Compartment^>( (intptr_t)compartment ) );
}
void  InternalUserNotify::NXU_notifyJoint (NxJoint *joint, const char *userProperties)
{
	Scene^ scene = ObjectCache::GetObject<Scene^>( (intptr_t)(&joint->getScene()) );
	Joint^ j = scene->AddJoint( joint );
	
	_userNotify->NotifyJoint( ObjectCache::GetObject<Joint^>( (intptr_t)joint ), ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifyForceField (NxForceField *effector, const char *userProperties)
{
	Scene^ scene = ObjectCache::GetObject<Scene^>( (intptr_t)(&effector->getScene()) );
	ForceField^ f = scene->AddForceField( effector );
	
	_userNotify->NotifyForceField( f, ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifyActor (NxActor *actor, const char *userProperties)
{
	Scene^ scene = ObjectCache::GetObject<Scene^>( (intptr_t)(&actor->getScene()) );
	Actor^ a = scene->AddActor( actor );
	
	_userNotify->NotifyActor( a, ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifyCloth (NxCloth *cloth, const char *userProperties)
{
	Scene^ scene = ObjectCache::GetObject<Scene^>( (intptr_t)(&cloth->getScene()) );
	Cloth^ c = scene->AddCloth( cloth );
	
	_userNotify->NotifyCloth( c, ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifySoftBody (NxSoftBody *softBody, const char *userProperties)
{
	Scene^ scene = ObjectCache::GetObject<Scene^>( (intptr_t)(&softBody->getScene()) );
	SoftBody^ s = scene->AddSoftBody( softBody );
	
	_userNotify->NotifySoftBody( s, ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifyFluid (NxFluid *fluid, const char *userProperties)
{
	Scene^ scene = ObjectCache::GetObject<Scene^>( (intptr_t)(&fluid->getScene()) );
	Fluid^ f = scene->AddFluid( fluid );
	
	_userNotify->NotifyFluid( f, ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifyTriangleMesh (NxTriangleMesh *t, const char *userProperties)
{
	Core^ core = ObjectCache::GetObject<TriangleMesh^>( (intptr_t)&t )->Core;
	TriangleMesh^ triangleMesh = core->AddTriangleMesh( t );
	
	_userNotify->NotifyTriangleMesh( triangleMesh, ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifyConvexMesh (NxConvexMesh *c, const char *userProperties)
{
	Core^ core = ObjectCache::GetObject<ConvexMesh^>( (intptr_t)c )->Core;
	ConvexMesh^ convexMesh = core->AddConvexMesh( c );
	
	_userNotify->NotifyConvexMesh( convexMesh, ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifyClothMesh (NxClothMesh *t, const char *userProperties)
{
	Core^ core = ObjectCache::GetObject<ClothMesh^>( (intptr_t)t )->Core;
	ClothMesh^ clothMesh = core->AddClothMesh( t );
	
	_userNotify->NotifyClothMesh( clothMesh, ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifySoftBodyMesh (NxSoftBodyMesh *t, const char *userProperties)
{
	Core^ core = ObjectCache::GetObject<SoftBodyMesh^>( (intptr_t)t )->Core;
	SoftBodyMesh^ softBodyMesh = core->AddSoftBodyMesh( t );
	
	_userNotify->NotifySoftBodyMesh( softBodyMesh, ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifyCCDSkeleton (NxCCDSkeleton *t, const char *userProperties)
{
	Core^ core = ObjectCache::GetObject<CCDSkeleton^>( (intptr_t)t )->Core;
	CCDSkeleton^ skeleton = core->AddCCDSkeleton( t );
	
	_userNotify->NotifyCCDSkeleton( skeleton, ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifyHeightField (NxHeightField *t, const char *userProperties)
{
	Core^ core = ObjectCache::GetObject<HeightField^>( (intptr_t)t )->Core;
	HeightField^ heightField = core->AddHeightField( t );
	
	_userNotify->NotifyHeightField( heightField, ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifyMaterial (NxMaterial *t, const char *userProperties)
{
	Scene^ scene = ObjectCache::GetObject<Material^>( (intptr_t)t )->Scene;
	Material^ material = scene->AddMaterial( t );
	
	_userNotify->NotifyMaterial( material, ToManagedString( userProperties ) );
}
void  InternalUserNotify::NXU_notifySaveActor (NxActor *pActor, const char **pUserProperties)
{
	throw gcnew NotImplementedException();
	//_userNotify->NotifyActor( ObjectCache::GetObject<Actor^>( (intptr_t)pActor ), ToManagedString( userProperties ) );
}
NxScene *  InternalUserNotify::NXU_preNotifyScene (unsigned int sno, NxSceneDesc &scene, const char *userProperties)
{
	throw gcnew NotImplementedException();
}
bool  InternalUserNotify::NXU_preNotifyCompartment (NxCompartmentDesc &compartment)
{
	throw gcnew NotImplementedException();
	
	//CompartmentDescription^ desc = gcnew CompartmentDescription();
		//memcpy_s( desc->UnmanagedPointer, sizeof( NxCompartmentDesc ), &compartment, sizeof( NxCompartmentDesc ) );
		
	
	//return _userNotify->PreNotifyCompartment( desc );
}
bool  InternalUserNotify::NXU_preNotifyJoint (NxJointDesc &joint, const char *userProperties)
{
	JointDescription^ desc = JointDescription::CopyToManagedReference( &joint );
	
	return _userNotify->PreNotifyJoint( desc, ToManagedString( userProperties ) );
}
bool  InternalUserNotify::NXU_preNotifyForceField (NxForceFieldDesc &effector, const char *userProperties)
{
	NxForceFieldDesc* desc = new NxForceFieldDesc();
	memcpy_s( desc, sizeof( NxForceFieldDesc ), &effector, sizeof( NxForceFieldDesc ) );
	
	ForceFieldDescription^ d = gcnew ForceFieldDescription( desc );
	
	return _userNotify->PreNotifyForceField( d, ToManagedString( userProperties ) );
}
bool  InternalUserNotify::NXU_preNotifyActor (NxActorDesc &actor, const char *userProperties)
{
	return true;
}
bool  InternalUserNotify::NXU_preNotifyCloth (NxClothDesc &cloth, const char *userProperties)
{
	return true;
}
bool  InternalUserNotify::NXU_preNotifySoftBody (NxSoftBodyDesc &softBody, const char *userProperties)
{
	return true;
}
bool  InternalUserNotify::NXU_preNotifyFluid (NxFluidDesc &fluid, const char *userProperties)
{
	return true;
}
bool  InternalUserNotify::NXU_preNotifyTriangleMesh (NxTriangleMeshDesc &t, const char *userProperties)
{
	return true;
}
bool  InternalUserNotify::NXU_preNotifyConvexMesh (NxConvexMeshDesc &t, const char *userProperties)
{
	return true;
}
bool  InternalUserNotify::NXU_preNotifyClothMesh (NxClothMeshDesc &t, const char *userProperties)
{
	return true;
}
bool  InternalUserNotify::NXU_preNotifySoftBodyMesh (NxSoftBodyMeshDesc &t, const char *userProperties)
{
	return true;
}
bool  InternalUserNotify::NXU_preNotifyCCDSkeleton (NxSimpleTriangleMesh &t, const char *userProperties)
{
	return true;
}
bool  InternalUserNotify::NXU_preNotifyHeightField (NxHeightFieldDesc &t, const char *userProperties)
{
	return true;
}
bool  InternalUserNotify::NXU_preNotifyMaterial (NxMaterialDesc &t, const char *userProperties)
{
	MaterialDescription^ d = gcnew MaterialDescription();
	*d->UnmanagedPointer = t;
	
	bool result = _userNotify->PreNotifyMaterial( d, ToManagedString( userProperties ) );
	
	t = *d->UnmanagedPointer;
	
	return result;
}
bool  InternalUserNotify::NXU_preNotifySceneInstance (const char *name, const char *sceneName, const char *userProperties, NxMat34 &rootNode, NxU32 depth)
{
	return true;
}
void  InternalUserNotify::NXU_notifySceneFailed (unsigned int sno, NxSceneDesc &scene, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifyCompartmentFailed (NxCompartmentDesc &compartment)
{
	
}
void  InternalUserNotify::NXU_notifyJointFailed (NxJointDesc &joint, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifySpringAndDamperEffectorFailed (NxSpringAndDamperEffectorDesc &effector, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifyForceFieldFailed (NxForceFieldDesc &effector, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifyActorFailed (NxActorDesc &actor, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifyClothFailed (NxClothDesc &cloth, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifySoftBodyFailed (NxSoftBodyDesc &softBody, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifyFluidFailed (NxFluidDesc &fluid, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifyTriangleMeshFailed (NxTriangleMeshDesc &t, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifyConvexMeshFailed (NxConvexMeshDesc &t, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifyClothMeshFailed (NxClothMeshDesc &t, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifySoftBodyMeshFailed (NxSoftBodyMeshDesc &t, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifyCCDSkeletonFailed (NxSimpleTriangleMesh &t, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifyHeightFieldFailed (NxHeightFieldDesc &t, const char *userProperties)
{
	
}
void  InternalUserNotify::NXU_notifyMaterialFailed (NxMaterialDesc &t, const char *userProperties)
{
	
}