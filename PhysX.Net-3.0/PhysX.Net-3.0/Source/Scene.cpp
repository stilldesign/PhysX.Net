#include "StdAfx.h"
#include "Scene.h"
#include "SceneDesc.h"

using namespace PhysX;

Scene::Scene(PxScene* scene)
{
	_scene = scene;
}
Scene::~Scene()
{
	this->!Scene();
}
Scene::!Scene()
{
	if (Disposed)
		return;

	_scene->release();
	_scene = NULL;
}

bool Scene::Disposed::get()
{
	return _scene == NULL;
}

SceneDesc^ Scene::SaveToDesc()
{
	SceneDesc^ desc = gcnew SceneDesc();
	
	if (!this->UnmanagedPointer->saveToDesc(*desc->UnmanagedPointer))
		return nullptr;

	
	
	return desc;
}

SceneFlag Scene::Flags::get()
{
	return ToManagedEnum(SceneFlag, _scene->getFlags());
}
void Scene::Flags::set(SceneFlag value)
{
	
}

PxScene* Scene::UnmanagedPointer::get()
{
	return _scene;
}