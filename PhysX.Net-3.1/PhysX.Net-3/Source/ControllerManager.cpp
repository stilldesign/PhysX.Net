#include "StdAfx.h"
#include "ControllerManager.h"
#include "ControllerDesc.h"
#include "BoxController.h"
#include "CapsuleController.h"
#include "Scene.h"
#include "ControllerDesc.h"
#include "BoxControllerDesc.h"
#include "CapsuleControllerDesc.h"
#include "Physics.h"
#include "FailedToCreateObjectException.h"
#include <PxBoxController.h> 
#include <PxCapsuleController.h> 

PhysX::ControllerManager::ControllerManager(PxControllerManager* manager, PhysX::Scene^ owner)
{
	if (manager == NULL)
		throw gcnew ArgumentNullException("manager");
	ThrowIfNullOrDisposed(owner, "owner");

	ObjectTable::Add((intptr_t)manager, this, owner);

	_manager = manager;
	_scene = owner;

	_controllers = gcnew List<Controller^>();
}
PhysX::ControllerManager::~ControllerManager()
{
	this->!ControllerManager();
}
PhysX::ControllerManager::!ControllerManager()
{
	OnDisposing(this, nullptr);

	if (this->Disposed)
		return;
	
	_manager->release();
	_manager = NULL;

	_scene = nullptr;
	_controllers = nullptr;

	OnDisposed(this, nullptr);
}
bool PhysX::ControllerManager::Disposed::get()
{
	return _manager == NULL;
}

generic<class T>
T ControllerManager::CreateController(ControllerDesc^ controllerDesc)
{
	return (T)CreateController(controllerDesc);
}
Controller^ ControllerManager::CreateController(ControllerDesc^ controllerDesc)
{
	ThrowIfDescriptionIsNullOrInvalid(controllerDesc, "controllerDesc");

	PxPhysics* physicsSdk = this->Scene->Physics->UnmanagedPointer;
	PxScene* scene = this->Scene->UnmanagedPointer;

	ControllerShapeType type = controllerDesc->Type;

	Controller^ controller;

	switch(controllerDesc->Type)
	{
		case ControllerShapeType::Box:
			{
				PxBoxControllerDesc desc = BoxControllerDesc::ToUnmanaged((BoxControllerDesc^)controllerDesc);
				PxBoxController* boxController = (PxBoxController*)_manager->createController(*physicsSdk, scene, desc);

				if (boxController == NULL)
					throw gcnew FailedToCreateObjectException("Failed to create box controller");

				BoxController^ c = gcnew BoxController(boxController, this);

				controller = c;
			}
			break;
		case ControllerShapeType::Capsule:
			{
				PxCapsuleControllerDesc desc = CapsuleControllerDesc::ToUnmanaged((CapsuleControllerDesc^)controllerDesc);
				PxCapsuleController* capsuleController = (PxCapsuleController*)_manager->createController(*physicsSdk, scene, desc);

				if (capsuleController == NULL)
					throw gcnew FailedToCreateObjectException("Failed to create capsule controller");

				CapsuleController^ c = gcnew CapsuleController(capsuleController, this);

				controller = c;
			}
			break;

		default:
			throw gcnew NotSupportedException(String::Format("Unsupported controller type '{0}'", controllerDesc->Type));
	}

	_controllers->Add(controller);

	return controller;
}

void PhysX::ControllerManager::UpdateControllers()
{
	_manager->updateControllers();
}

PhysX::Scene^ ControllerManager::Scene::get()
{
	return _scene;
}

IEnumerable<Controller^>^ ControllerManager::Controllers::get()
{
	return _controllers;
}

PxControllerManager* ControllerManager::UnmanagedPointer::get()
{
	return _manager;
}