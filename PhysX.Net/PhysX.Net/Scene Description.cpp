#include "StdAfx.h"

#include "Scene Description.h"
#include "Scene Limits.h"
#include "User Notify.h"
#include "Fluid User Notify.h"
#include "User Contact Modify.h"
#include "User Contact Report.h"
#include "User Trigger Report.h"

using namespace StillDesign::PhysX;

SceneDescription::SceneDescription()
{
	_sceneDescription = new NxSceneDesc();
}
SceneDescription::SceneDescription( NxSceneDesc* desc )
{
	Debug::Assert( desc != NULL );
	
	_sceneDescription = desc;
	_sceneLimits = (desc->limits == NULL ? nullptr : (SceneLimits^)*(desc->limits));
}
SceneDescription::~SceneDescription()
{
	this->!SceneDescription();
}
SceneDescription::!SceneDescription()
{
	if( this->IsDisposed == true )
		return;
	
	onDisposing( this, nullptr );
	
	SAFE_DELETE( _sceneDescription );
	
	_name = nullptr;
				
	_userNotify = nullptr;
	_fluidUserNotify = nullptr;
	_userContactModify = nullptr;
	_userContactReport = nullptr;
	_userTriggerReport = nullptr;
	
	_sceneLimits = nullptr;
	
	_userData = nullptr;
	
	onDisposed( this, nullptr );
}
bool SceneDescription::IsDisposed::get()
{
	return ( _sceneDescription == NULL );
}

void SceneDescription::SetToDefault()
{
	_sceneDescription->setToDefault();
	
	_name = nullptr;
	
	_userNotify = nullptr;
	_fluidUserNotify = nullptr;
	_userContactModify = nullptr;
	_userContactReport = nullptr;
	_userTriggerReport = nullptr;
	
	_sceneLimits = nullptr;
	
	_userData = nullptr;
}
bool SceneDescription::IsValid()
{
	return _sceneDescription->isValid();
}

Vector3 SceneDescription::Gravity::get()
{
	return Math::NxVec3ToVector3( _sceneDescription->gravity );
}
void SceneDescription::Gravity::set( Vector3 value )
{
	_sceneDescription->gravity = Math::Vector3ToNxVec3( value );
}

StillDesign::PhysX::UserNotify^ SceneDescription::UserNotify::get()
{
	return _userNotify;
}
void SceneDescription::UserNotify::set( StillDesign::PhysX::UserNotify^ value )
{
	_userNotify = value;
	
	if( value == nullptr )
		_sceneDescription->userNotify = NULL;
	else
		_sceneDescription->userNotify = value->UnmanagedPointer;
}

StillDesign::PhysX::FluidUserNotify^ SceneDescription::FluidUserNotify::get()
{
	return _fluidUserNotify;
}
void SceneDescription::FluidUserNotify::set( StillDesign::PhysX::FluidUserNotify^ value )
{
	_fluidUserNotify = value;
	
	if( value == nullptr )
		_sceneDescription->fluidUserNotify = NULL;
	else
		_sceneDescription->fluidUserNotify = value->UnmanagedPointer;
}
StillDesign::PhysX::UserContactModify^ SceneDescription::UserContactModify::get()
{
	return _userContactModify;
}
void SceneDescription::UserContactModify::set( StillDesign::PhysX::UserContactModify^ value )
{
	_userContactModify = value;
	
	if( value == nullptr )
		_sceneDescription->userContactModify = NULL;
	else
		_sceneDescription->userContactModify = value->UnmanagedPointer;
}
StillDesign::PhysX::UserContactReport^ SceneDescription::UserContactReport::get()
{
	return _userContactReport;
}
void SceneDescription::UserContactReport::set( StillDesign::PhysX::UserContactReport^ value )
{
	_userContactReport = value;
	
	if( value == nullptr )
		_sceneDescription->userContactReport = NULL;
	else
		_sceneDescription->userContactReport = value->UnmanagedPointer;
}
StillDesign::PhysX::UserTriggerReport^ SceneDescription::UserTriggerReport::get()
{
	return _userTriggerReport;
}
void SceneDescription::UserTriggerReport::set( StillDesign::PhysX::UserTriggerReport^ value )
{
	_userTriggerReport = value;
	
	if( value == nullptr )
		_sceneDescription->userTriggerReport = NULL;
	else
		_sceneDescription->userTriggerReport = value->UnmanagedPointer;
}

float SceneDescription::MaximumTimestep::get()
{
	return _sceneDescription->maxTimestep;
}
void SceneDescription::MaximumTimestep::set( float value )
{
	_sceneDescription->maxTimestep = value;
}

int SceneDescription::MaximumIterations::get()
{
	return _sceneDescription->maxIter;
}
void SceneDescription::MaximumIterations::set( int value )
{
	_sceneDescription->maxIter = value;
}

StillDesign::PhysX::TimestepMethod SceneDescription::TimestepMethod::get()
{
	return (StillDesign::PhysX::TimestepMethod)_sceneDescription->timeStepMethod;
}
void SceneDescription::TimestepMethod::set( StillDesign::PhysX::TimestepMethod value )
{
	_sceneDescription->timeStepMethod = (NxTimeStepMethod)value;
}

Nullable<Bounds3> SceneDescription::MaximumBounds::get()
{
	if( _sceneDescription->maxBounds == NULL )
		return Nullable<Bounds3>();
	else
		return (Bounds3)(*_sceneDescription->maxBounds);
}
void SceneDescription::MaximumBounds::set( Nullable<Bounds3> value )
{
	if( value.HasValue == false )
		_sceneDescription->maxBounds = NULL;
	else
		*_sceneDescription->maxBounds = (NxBounds3)value.Value;
}

SceneLimits^ SceneDescription::Limits::get()
{
	return _sceneLimits;
}
void SceneDescription::Limits::set( SceneLimits^ value )
{
	_sceneLimits = value;
	
	if( value == nullptr )
		_sceneDescription->limits = NULL;
	else
		*_sceneDescription->limits = (NxSceneLimits)value;
}

StillDesign::PhysX::SimulationType SceneDescription::SimulationType::get()
{
	return (StillDesign::PhysX::SimulationType)_sceneDescription->simType;
}
void SceneDescription::SimulationType::set( StillDesign::PhysX::SimulationType value )
{
	_sceneDescription->simType = (NxSimulationType)value;
}

bool SceneDescription::GroundPlaneEnabled::get()
{
	return _sceneDescription->groundPlane;
}
void SceneDescription::GroundPlaneEnabled::set( bool value )
{
	_sceneDescription->groundPlane = value;
}

bool SceneDescription::BoundsPlanesEnabled::get()
{
	return _sceneDescription->boundsPlanes;
}
void SceneDescription::BoundsPlanesEnabled::set( bool value )
{
	_sceneDescription->boundsPlanes = value;
}

SceneFlag SceneDescription::Flags::get()
{
	return (SceneFlag)_sceneDescription->flags;
}
void SceneDescription::Flags::set( SceneFlag value )
{
	_sceneDescription->flags = (NxSceneFlags)value;
}

int SceneDescription::SimulationThreadStackSize::get()
{
	return _sceneDescription->simThreadStackSize;
}
void SceneDescription::SimulationThreadStackSize::set( int value )
{
	_sceneDescription->simThreadStackSize = value;
}

StillDesign::PhysX::ThreadPriority SceneDescription::SimulationThreadPriority::get()
{
	return (StillDesign::PhysX::ThreadPriority)_sceneDescription->simThreadPriority;
}
void SceneDescription::SimulationThreadPriority::set( StillDesign::PhysX::ThreadPriority value )
{
	_sceneDescription->simThreadPriority = (NxThreadPriority)value;
}

unsigned int SceneDescription::SimulateThreadMask::get()
{
	return _sceneDescription->simThreadMask;
}
void SceneDescription::SimulateThreadMask::set( unsigned int value )
{
	_sceneDescription->simThreadMask = value;
}

int SceneDescription::InternalThreadCount::get()
{
	return _sceneDescription->internalThreadCount;
}
void SceneDescription::InternalThreadCount::set( int value )
{
	_sceneDescription->internalThreadCount = value;
}

int SceneDescription::WorkerThreadStackSize::get()
{
	return _sceneDescription->workerThreadStackSize;
}
void SceneDescription::WorkerThreadStackSize::set( int value )
{
	_sceneDescription->workerThreadStackSize = value;
}

StillDesign::PhysX::ThreadPriority SceneDescription::WorkerThreadPriority::get()
{
	return (StillDesign::PhysX::ThreadPriority)_sceneDescription->workerThreadPriority;
}
void SceneDescription::WorkerThreadPriority::set( StillDesign::PhysX::ThreadPriority value )
{
	_sceneDescription->workerThreadPriority = (NxThreadPriority)value;
}

unsigned int SceneDescription::ThreadMask::get()
{
	return _sceneDescription->threadMask;
}
void SceneDescription::ThreadMask::set( unsigned int value )
{
	_sceneDescription->threadMask = value;
}

int SceneDescription::BackgroundThreadCount::get()
{
	return _sceneDescription->backgroundThreadCount;
}
void SceneDescription::BackgroundThreadCount::set( int value )
{
	_sceneDescription->backgroundThreadCount = value;
}
ThreadPriority SceneDescription::BackgroundThreadPriority::get()
{
	return (ThreadPriority)_sceneDescription->backgroundThreadPriority;
}
void SceneDescription::BackgroundThreadPriority::set( ThreadPriority value )
{
	_sceneDescription->backgroundThreadPriority = (NxThreadPriority)value;
}
unsigned int SceneDescription::BackgroundThreadMask::get()
{
	return _sceneDescription->backgroundThreadMask;
}
void SceneDescription::BackgroundThreadMask::set( unsigned int value )
{
	_sceneDescription->backgroundThreadMask = value;
}

int SceneDescription::UpAxis::get()
{
	return _sceneDescription->upAxis;
}
void SceneDescription::UpAxis::set( int value )
{
	_sceneDescription->upAxis = value;
}

int SceneDescription::SubdivisionLevel::get()
{
	return _sceneDescription->subdivisionLevel;
}
void SceneDescription::SubdivisionLevel::set( int value )
{
	_sceneDescription->subdivisionLevel = value;
}

PruningStructure SceneDescription::StaticStructure::get()
{
	return (PruningStructure)_sceneDescription->staticStructure;
}
void SceneDescription::StaticStructure::set( PruningStructure value )
{
	_sceneDescription->staticStructure = (NxPruningStructure)value;
}
PruningStructure SceneDescription::DynamicStructure::get()
{
	return (PruningStructure)_sceneDescription->dynamicStructure;
}
void SceneDescription::DynamicStructure::set( PruningStructure value )
{
	_sceneDescription->dynamicStructure = (NxPruningStructure)value;
}
int SceneDescription::DynamicTreeRebuildRateHint::get()
{
	return _sceneDescription->dynamicTreeRebuildRateHint;
}
void SceneDescription::DynamicTreeRebuildRateHint::set( int value )
{
	_sceneDescription->dynamicTreeRebuildRateHint = value;
}

StillDesign::PhysX::BroadPhaseType SceneDescription::BroadPhaseType::get()
{
	return (StillDesign::PhysX::BroadPhaseType)_sceneDescription->bpType;
}
void SceneDescription::BroadPhaseType::set( StillDesign::PhysX::BroadPhaseType value )
{
	_sceneDescription->bpType = (NxBroadPhaseType)value;
}

int SceneDescription::NumberOfGridCellsX::get()
{
	return _sceneDescription->nbGridCellsX;
}
void SceneDescription::NumberOfGridCellsX::set( int value )
{
	_sceneDescription->nbGridCellsX = value;
}
int SceneDescription::NumberOfGridCellsY::get()
{
	return _sceneDescription->nbGridCellsY;
}
void SceneDescription::NumberOfGridCellsY::set( int value )
{
	_sceneDescription->nbGridCellsY = value;
}

int SceneDescription::SolverBatchSize::get()
{
	return _sceneDescription->solverBatchSize;
}
void SceneDescription::SolverBatchSize::set( int value )
{
	_sceneDescription->solverBatchSize = value;
}

Object^ SceneDescription::UserData::get()
{
	return _userData;
}
void SceneDescription::UserData::set( Object^ value )
{
	_userData = value;
}

NxSceneDesc* SceneDescription::UnmanagedPointer::get()
{
	return _sceneDescription;
}