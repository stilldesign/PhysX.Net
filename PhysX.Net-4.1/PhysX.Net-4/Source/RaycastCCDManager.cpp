#include "StdAfx.h"
#include "RaycastCCDManager.h"
#include "Scene.h"
#include "RigidDynamic.h"
#include "Shape.h"
#include <extensions\PxRaycastCCD.h>

using namespace PhysX;

PhysX::RaycastCCDManager::RaycastCCDManager(Scene^ scene)
{
	ThrowIfNullOrDisposed(scene, "scene");

	_manager = new physx::RaycastCCDManager(scene->UnmanagedPointer);
}
PhysX::RaycastCCDManager::~RaycastCCDManager()
{
	this->!RaycastCCDManager();
}
PhysX::RaycastCCDManager::!RaycastCCDManager()
{
	SAFE_DELETE(_manager);
}

bool PhysX::RaycastCCDManager::RegisterRaycastCCDObject(RigidDynamic^ actor, Shape^ shape)
{
	ThrowIfNullOrDisposed(actor, "actor");
	ThrowIfNullOrDisposed(shape, "shape");

	_manager->registerRaycastCCDObject(actor->UnmanagedPointer, shape->UnmanagedPointer);
}

void PhysX::RaycastCCDManager::DoRaycastCCD(bool doDynamicDynamicCCD)
{
	_manager->doRaycastCCD(doDynamicDynamicCCD);
}