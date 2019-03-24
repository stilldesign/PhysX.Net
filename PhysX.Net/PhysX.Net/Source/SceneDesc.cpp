#include "StdAfx.h"
#include "TolerancesScale.h"
#include "Physics.h"
#include "PhysicsEnum.h"
#include "ContactModifyCallback.h"
#include "SceneDesc.h"
#include "SimulationFilterShader.h"
#include "BroadPhaseCallback.h"
#include "SceneLimits.h"
#include "SimulationFilterCallback.h"
#include "CudaContextManager.h"

using namespace PhysX;

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

PhysX::FrictionType SceneDesc::FrictionType::get()
{
	return (PhysX::FrictionType)_sceneDesc->frictionType;
}
void SceneDesc::FrictionType::set(PhysX::FrictionType value)
{
	_sceneDesc->frictionType = ToUnmanagedEnum(PxFrictionType, value);
}

SceneFlag SceneDesc::Flags::get()
{
	return ToManagedEnum(SceneFlag, _sceneDesc->flags);
}
void SceneDesc::Flags::set(SceneFlag value)
{
	_sceneDesc->flags = ToUnmanagedEnum(PxSceneFlag, value);
}

PhysX::BroadPhaseType SceneDesc::BroadPhaseType::get()
{
	return ToManagedEnum(PhysX::BroadPhaseType, _sceneDesc->broadPhaseType);
}
void SceneDesc::BroadPhaseType::set(PhysX::BroadPhaseType value)
{
	_sceneDesc->broadPhaseType = ToUnmanagedEnum(PxBroadPhaseType, value);
}

PhysX::SimulationEventCallback^ SceneDesc::SimulationEventCallback::get()
{
	return _simulationEventCallback;
}
void SceneDesc::SimulationEventCallback::set(PhysX::SimulationEventCallback^ value)
{
	_simulationEventCallback = value;

	_sceneDesc->simulationEventCallback = (value == nullptr ? NULL : value->UnmanagedPointer);
}

PhysX::SimulationFilterCallback^ SceneDesc::SimulationFilterCallback::get()
{
	return _simulationFilterCallback;
}
void SceneDesc::SimulationFilterCallback::set(PhysX::SimulationFilterCallback^ value)
{
	_simulationFilterCallback = value;

	_sceneDesc->filterCallback = GetPointerOrNull(value);
}

PhysX::ContactModifyCallback^ SceneDesc::ContactModifyCallback::get()
{
	return _contactModifyCallback;
}
void SceneDesc::ContactModifyCallback::set(PhysX::ContactModifyCallback^ value)
{
	_contactModifyCallback = value;

	_sceneDesc->contactModifyCallback = (value == nullptr ? NULL : value->UnmanagedPointer);
}

PhysX::SimulationFilterShader^ SceneDesc::FilterShader::get()
{
	return _filterShader;
}
void SceneDesc::FilterShader::set(PhysX::SimulationFilterShader^ value)
{
	_filterShader = value;

	// HACK: At the moment we can only have 1 filter shader regardless of what scene/scene desc
	UnmanagedSimulationFilterShader::Managed = value;
	_sceneDesc->filterShader = UnmanagedSimulationFilterShader::Filter;
}

int SceneDesc::CCDMaximumPasses::get()
{
	return _sceneDesc->ccdMaxPasses;
}
void SceneDesc::CCDMaximumPasses::set(int value)
{
	_sceneDesc->ccdMaxPasses = value;
}

PhysX::CudaContextManager^ SceneDesc::CudaContextManager::get()
{
	return _cudaContextManager;
}
void SceneDesc::CudaContextManager::set(PhysX::CudaContextManager^ value)
{
	_cudaContextManager = value;

	_sceneDesc->cudaContextManager = (value == nullptr ? NULL : value->UnmanagedPointer);
}

PhysX::BroadPhaseCallback^ SceneDesc::BroadPhaseCallback::get()
{
	return _broadPhaseCallback;
}
void SceneDesc::BroadPhaseCallback::set(PhysX::BroadPhaseCallback^ value)
{
	_broadPhaseCallback = value;

	_sceneDesc->broadPhaseCallback = (value == nullptr ? nullptr : value->UnmanagedPointer);
}

SceneLimits^ SceneDesc::Limits::get()
{
	return SceneLimits::ToManaged(_sceneDesc->limits);
}
void SceneDesc::Limits::set(SceneLimits^ value)
{
	_sceneDesc->limits = SceneLimits::ToUnmanaged(value);
}

float SceneDesc::BounceThresholdVelocity::get()
{
	return _sceneDesc->bounceThresholdVelocity;
}
void SceneDesc::BounceThresholdVelocity::set(float value)
{
	_sceneDesc->bounceThresholdVelocity = value;
}

float SceneDesc::FrictionOffsetThreshold::get()
{
	return _sceneDesc->frictionOffsetThreshold;
}
void SceneDesc::FrictionOffsetThreshold::set(float value)
{
	_sceneDesc->frictionOffsetThreshold = value;
}

int SceneDesc::DynamicTreeRebuildRateHint::get()
{
	return _sceneDesc->dynamicTreeRebuildRateHint;
}
void SceneDesc::DynamicTreeRebuildRateHint::set(int value)
{
	_sceneDesc->dynamicTreeRebuildRateHint = value;
}

int SceneDesc::SolverBatchSize::get()
{
	return _sceneDesc->solverBatchSize;
}
void SceneDesc::SolverBatchSize::set(int value)
{
	_sceneDesc->solverBatchSize = value;
}

int SceneDesc::NumberOfContactDataBlocks::get()
{
	return _sceneDesc->nbContactDataBlocks;
}
void SceneDesc::NumberOfContactDataBlocks::set(int value)
{
	_sceneDesc->nbContactDataBlocks = value;
}

int SceneDesc::MaxNumberOfContactDataBlocks::get()
{
	return _sceneDesc->maxNbContactDataBlocks;
}
void SceneDesc::MaxNumberOfContactDataBlocks::set(int value)
{
	_sceneDesc->maxNbContactDataBlocks = value;
}

int SceneDesc::ContactReportStreamBufferSize::get()
{
	return _sceneDesc->contactReportStreamBufferSize;
}
void SceneDesc::ContactReportStreamBufferSize::set(int value)
{
	_sceneDesc->contactReportStreamBufferSize = value;
}

int SceneDesc::CCDMaxPasses::get()
{
	return _sceneDesc->ccdMaxPasses;
}
void SceneDesc::CCDMaxPasses::set(int value)
{
	_sceneDesc->ccdMaxPasses = value;
}

float SceneDesc::WakeCounterResetValue::get()
{
	return _sceneDesc->wakeCounterResetValue;
}
void SceneDesc::WakeCounterResetValue::set(float value)
{
	_sceneDesc->wakeCounterResetValue = value;
}

Bounds3 SceneDesc::SanityBounds::get()
{
	return Bounds3::ToManaged(_sceneDesc->sanityBounds);
}
void SceneDesc::SanityBounds::set(Bounds3 value)
{
	_sceneDesc->sanityBounds = Bounds3::ToUnmanaged(value);
}

float SceneDesc::SolverOffsetSlop::get()
{
	return _sceneDesc->solverOffsetSlop;
}
void SceneDesc::SolverOffsetSlop::set(float value)
{
	_sceneDesc->solverOffsetSlop = value;
}

PhysX::SolverType SceneDesc::SolverType::get()
{
	return ToUnmanagedEnum2(PhysX::SolverType, _sceneDesc->solverType);
}
void SceneDesc::SolverType::set(PhysX::SolverType value)
{
	_sceneDesc->solverType = ToManagedEnum(PxSolverType::Enum, value);
}

PxSceneDesc* SceneDesc::UnmanagedPointer::get()
{
	return _sceneDesc;
}