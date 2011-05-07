#include "StdAfx.h"
#include "Physics.h"
#include "Scene.h"
#include "SceneDesc.h"
#include "Material.h"
#include "SceneCreationException.h"

#include <PxDefaultAllocator.h>
#include <PxDefaultErrorCallback.h>

using namespace PhysX;

Physics::Physics(PxPhysics* physics)
{
	Init();

	_physics = physics;
}
Physics::Physics()
{
	Init();

	_allocator = new PxDefaultAllocator();
	_errorCallback = new PxDefaultErrorCallback();

	_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_allocator, *_errorCallback, PxTolerancesScale());

	if(_physics == NULL)
		throw gcnew Exception("Failed to create physics instance");
}
void Physics::Init()
{
	_scenes = gcnew List<Scene^>();
	_materials = gcnew List<Material^>();
}
Physics::~Physics()
{
	this->!Physics();
}
Physics::!Physics()
{
	if (Disposed)
		return;

	_physics->release();
	_physics = NULL;
}
bool Physics::Disposed::get()
{
	return _physics == NULL;
}

#pragma region Scene
Scene^ Physics::CreateScene(SceneDesc^ sceneDesc)
{
	ThrowIfNullOrDisposed(sceneDesc, "sceneDesc");

	PxScene* s = _physics->createScene(*sceneDesc->UnmanagedPointer);

	if (s == NULL)
		throw gcnew SceneCreationException("Failed to create scene");

	Scene^ scene = gcnew Scene(s);

	_scenes->Add(scene);

	return scene;
}

IEnumerable<Scene^>^ Physics::Scenes::get()
{
	return _scenes;
}
#pragma endregion

#pragma region Material
Material^ Physics::CreateMaterial(float staticFriction, float dynamicFriction, float restitution)
{
	PxMaterial* m = _physics->createMaterial(staticFriction, dynamicFriction, restitution);

	if (m == NULL)
		throw gcnew Exception("Failed to create material");

	Material^ material = gcnew Material(m);

	_materials->Add(material);

	return material;
}
#pragma endregion