#include "StdAfx.h"
#include "SceneDesc.h"
#include "TolerancesScale.h"
#include "Physics.h"
#include <PxSceneDesc.h>
#include <PxDefaultSimulationFilterShader.h>
#include <PxDefaultCpuDispatcher.h>
#include <PxCpuDispatcher.h>

using namespace PhysX;
using namespace PhysX::Math;

SceneDesc::SceneDesc([Optional] Nullable<PhysX::TolerancesScale> tolerancesScale)
{
	if (!Physics::Instantiated)
		throw gcnew InvalidOperationException("To create a SceneDesc instance you first must create a Physics instance. Internally this allows PxInitExtensions to be called.");

	PxTolerancesScale ts = tolerancesScale.HasValue ? TolerancesScale::ToUnmanaged(tolerancesScale.Value) : PxTolerancesScale();

	_sceneDesc = new PxSceneDesc(ts);

	_sceneDesc->filterShader = PxDefaultSimulationFilterShader;
	_sceneDesc->cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
}
SceneDesc::~SceneDesc()
{
	this->!SceneDesc();
}
SceneDesc::!SceneDesc()
{
	SAFE_DELETE(_sceneDesc);
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