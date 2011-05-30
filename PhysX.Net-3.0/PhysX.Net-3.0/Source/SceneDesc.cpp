#include "StdAfx.h"
#include "SceneDesc.h"
#include "TolerancesScale.h"
#include <PxSceneDesc.h>
#include <PxDefaultSimulationFilterShader.h>
#include <PxDefaultCpuDispatcher.h>
#include <PxCpuDispatcher.h>

using namespace PhysX;
using namespace PhysX::MathPrimitives;

SceneDesc::SceneDesc()
{
	_sceneDesc = new PxSceneDesc(PxTolerancesScale());

	Init();
}
SceneDesc::SceneDesc(PhysX::TolerancesScale tolerancesScale)
{
	_sceneDesc = new PxSceneDesc(TolerancesScale::ToUnmanaged(tolerancesScale));

	Init();
}
void SceneDesc::Init()
{
	_sceneDesc->filterShader = PxDefaultSimulationFilterShader;
	_sceneDesc->cpuDispatcher = new CpuDis(); //PxDefaultCpuDispatcherCreate(1);
}
SceneDesc::~SceneDesc()
{
	this->!SceneDesc();
}
SceneDesc::!SceneDesc()
{
	
}
bool SceneDesc::Disposed::get()
{
	return _sceneDesc == NULL;
}

bool SceneDesc::IsValid()
{
	return _sceneDesc->isValid();
}
void SceneDesc::SetToDefault([Optional] Nullable<PhysX::TolerancesScale> tolerancesScale)
{
	if (tolerancesScale.HasValue)
		_sceneDesc->setToDefault(PhysX::TolerancesScale::ToUnmanaged(tolerancesScale.Value));
	else
		_sceneDesc->setToDefault(PxTolerancesScale());
}

Vector3 SceneDesc::Gravity::get()
{
	return MathUtil::PxVec3ToVector3(_sceneDesc->gravity);
}
void SceneDesc::Gravity::set(Vector3 value)
{
	_sceneDesc->gravity = MathUtil::Vector3ToPxVec3(value);
}

PxSceneDesc* SceneDesc::UnmanagedPointer::get()
{
	return _sceneDesc;
}