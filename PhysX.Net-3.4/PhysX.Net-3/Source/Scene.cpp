#include "StdAfx.h"
#include "Scene.h"
#include "Bounds3.h"
#include "QueryHit.h"
#include "QueryFilterData.h"
#include "Geometry.h"
#include "Actor.h"
#include "Physics.h"
#include "ControllerManager.h"
#include "Shape.h"
#include "RaycastHit.h"
#include "RigidActor.h"
#include "SimulationStatistics.h"
#include "Articulation.h"
#include "Aggregate.h"
#include "SceneSweepOperationObject.h"
#include "SweepHit.h"
#include "FailedToCreateObjectException.h"
#include "RenderBuffer.h"
#include "InternalRaycastCallback.h"
#include "InternalSweepCallback.h"
#include "QueryFilterCallback.h"
#include "QueryCache.h"
#include "OverlapHit.h"
#include "InternalOverlapCallback.h"
#include "Collection.h"
#include "SceneLimits.h"
#include "ContactModifyCallback.h"
#include "BroadPhaseCallback.h"
#include "SimulationEventCallback.h"

using namespace PhysX;

Scene::Scene(PxScene* scene, PhysX::Physics^ physics, PhysX::BroadPhaseCallback^ broadPhaseCallback, PhysX::SimulationFilterCallback^ simulationFilterCallback)
{
	if (scene == NULL)
		throw gcnew ArgumentNullException("scene");
	ThrowIfNullOrDisposed(physics, "physics");

	_scene = scene;
	_physics = physics;
	_broadPhaseCallback = broadPhaseCallback;
	_simulationFilterCallback = simulationFilterCallback;

	ObjectTable::Instance->Add((intptr_t)scene, this, physics);
}
Scene::~Scene()
{
	this->!Scene();
}
Scene::!Scene()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_scene->release();
	_scene = NULL;

	OnDisposed(this, nullptr);
}

bool Scene::Disposed::get()
{
	return _scene == NULL;
}

void Scene::SetFlag(SceneFlag flag, bool value)
{
	this->UnmanagedPointer->setFlag(ToUnmanagedEnum(PxSceneFlag, flag), value);
}

//

PhysX::Physics^ Scene::Physics::get()
{
	return _physics;
}

RenderBuffer^ Scene::GetRenderBuffer([Optional] Nullable<RenderBufferDataFlags> flags)
{
	const PxRenderBuffer& buffer = this->UnmanagedPointer->getRenderBuffer();

	return RenderBuffer::ToManaged(buffer, flags.GetValueOrDefault(RenderBufferDataFlags::All));
}

SimulationStatistics^ Scene::GetSimulationStatistics()
{
	PxSimulationStatistics stats;
	_scene->getSimulationStatistics(stats);

	return SimulationStatistics::ToManaged(&stats);
}

float Scene::WakeCounterResetValue::get()
{
	return _scene->getWakeCounterResetValue();
}

void Scene::ShiftOrigin(Vector3 shift)
{
	_scene->shiftOrigin(UV(shift));
}

#pragma region Actors
IReadOnlyList<Actor^>^ Scene::GetActors(ActorTypeFlag types)
{
	int n = _scene->getNbActors(ToUnmanagedEnum(PxActorTypeFlag, types));

	PxActor** unmanaged = new PxActor*[n];

	_scene->getActors(ToUnmanagedEnum(PxActorTypeFlag, types), unmanaged, n);

	//

	auto managed = gcnew List<Actor^>(n);

	for (size_t i = 0; i < n; i++)
	{
		auto obj = ObjectTable::Instance->TryGetObject<Actor^>((intptr_t)unmanaged[i]);

		if (obj != nullptr)
			managed->Add(obj);
	}

	delete[] unmanaged;

	return managed;
}

array<RigidDynamic^>^ Scene::RigidDynamicActors::get()
{
	return ObjectTable::Instance->GetObjectsOfOwnerAndType<RigidDynamic^>(this->Physics);
}
array<RigidStatic^>^ Scene::RigidStaticActors::get()
{
	return ObjectTable::Instance->GetObjectsOfOwnerAndType<RigidStatic^>(this->Physics);
}

int Scene::GetNumberOfActors(ActorTypeFlag types)
{
	return _scene->getNbActors(ToUnmanagedEnum(PxActorTypeFlag, types));
}

void Scene::AddActor(Actor^ actor)
{
	ThrowIfNullOrDisposed(actor, "actor");

	_scene->addActor(*actor->UnmanagedPointer);
}
void Scene::RemoveActor(Actor^ actor)
{
	ThrowIfNullOrDisposed(actor, "actor");

	_scene->removeActor(*actor->UnmanagedPointer);
}

array<Articulation^>^ Scene::Articulations::get()
{
	return ObjectTable::Instance->GetObjectsOfOwnerAndType<Articulation^>(this);
}
#pragma endregion

#pragma region Joints
Joint^ Scene::CreateJoint(JointType type, RigidActor^ actor0, Matrix localFrame0, RigidActor^ actor1, Matrix localFrame1)
{
	return this->Physics->CreateJoint(type, actor0, localFrame0, actor1, localFrame1);
}

generic<typename T> where T : Joint
T Scene::CreateJoint(RigidActor^ actor0, Matrix localFrame0, RigidActor^ actor1, Matrix localFrame1)
{
	return this->Physics->CreateJoint<T>(actor0, localFrame0, actor1, localFrame1);
}
#pragma endregion

#pragma region Grouping
DominanceGroupPair Scene::GetDominanceGroupPair(Byte group1, Byte group2)
{
	return DominanceGroupPair::ToManaged(_scene->getDominanceGroupPair(group1, group2));
}

void Scene::SetDominanceGroupPair(Byte group1, Byte group2, DominanceGroupPair dominance)
{
	_scene->setDominanceGroupPair(group1, group2, DominanceGroupPair::ToUnmanaged(dominance));
}
#pragma endregion

void Scene::Simulate(float elapsedTime)
{
	_scene->simulate(elapsedTime);
}
bool Scene::CheckResults([Optional] bool block)
{
	return _scene->checkResults(block);
}
bool Scene::FetchResults([Optional] bool block)
{
	return _scene->fetchResults(block);
}
void Scene::FlushSimulation([Optional] bool sendPendingReports)
{
	_scene->flushSimulation(sendPendingReports);
}

int Scene::SolverBatchSize::get()
{
	return _scene->getSolverBatchSize();
}
void Scene::SolverBatchSize::set(int value)
{
	_scene->setSolverBatchSize(value);
}

Vector3 Scene::Gravity::get()
{
	return MathUtil::PxVec3ToVector3(_scene->getGravity());
}
void Scene::Gravity::set(Vector3 value)
{
	_scene->setGravity(MathUtil::Vector3ToPxVec3(value));
}

#pragma region Visualization
float Scene::GetVisualizationParameter(VisualizationParameter param)
{
	return _scene->getVisualizationParameter((PxVisualizationParameter::Enum)(PxU32)param);
}
bool Scene::SetVisualizationParameter(VisualizationParameter param, float value)
{
	return _scene->setVisualizationParameter((PxVisualizationParameter::Enum)(PxU32)param, value);
}
bool Scene::SetVisualizationParameter(VisualizationParameter param, bool value)
{
	return SetVisualizationParameter(param, value ? 1.0f : 0.0f);
}

Bounds3 Scene::VisualizationCullingBox::get()
{
	return Bounds3::ToManaged(_scene->getVisualizationCullingBox());
}
void Scene::VisualizationCullingBox::set(Bounds3 value)
{
	_scene->setVisualizationCullingBox(Bounds3::ToUnmanaged(value));
}
#pragma endregion

bool Scene::Raycast(Vector3 origin, Vector3 direction, float distance, int maximumHits, Func<array<RaycastHit^>^, bool>^ hitCall, [Optional] HitFlag hitFlag, [Optional] Nullable<QueryFilterData> filterData, [Optional] QueryFilterCallback^ filterCallback, [Optional] QueryCache^ cache)
{
	if (maximumHits < 0)
		throw gcnew ArgumentOutOfRangeException("maximumHits");
	ThrowIfNull(hitCall, "hitCall");

	PxVec3 o = UV(origin);
	PxVec3 d = UV(direction);

	PxRaycastHit* hits;
	try
	{
		hits = new PxRaycastHit[maximumHits];
		InternalRaycastCallback hc(hits, maximumHits, hitCall);

		PxHitFlags f = ToUnmanagedEnum(PxHitFlag, hitFlag);

		PxQueryFilterData fd = (filterData.HasValue ? QueryFilterData::ToUnmanaged(filterData.Value) : PxQueryFilterData());

		UserQueryFilterCallback* qfcb = (filterCallback == nullptr ? NULL : &UserQueryFilterCallback(filterCallback));

		PxQueryCache* qc = (cache == nullptr ? NULL : &QueryCache::ToUnmanaged(cache));

		bool result = _scene->raycast(o, d, distance, hc, f, fd, qfcb, qc);

		return result;
	}
	finally
	{
		delete[] hits;
	}
}

bool Scene::Sweep(Geometry^ geometry, Matrix pose, Vector3 direction, float distance, int maximumHits, Func<array<SweepHit^>^, bool>^ hitCall, [Optional] HitFlag hitFlag, [Optional] Nullable<QueryFilterData> filterData, [Optional] QueryFilterCallback^ filterCallback, [Optional] QueryCache^ cache)
{
	if (maximumHits < 0)
		throw gcnew ArgumentOutOfRangeException("maximumHits");
	ThrowIfNull(hitCall, "hitCall");

	PxGeometry* g = geometry->ToUnmanaged();
	PxTransform p = MathUtil::MatrixToPxTransform(pose);
	PxVec3 d = UV(direction);

	PxSweepHit* hits;
	try
	{
		hits = new PxSweepHit[maximumHits];
		InternalSweepCallback hc(hits, maximumHits, hitCall);

		PxHitFlags f = ToUnmanagedEnum(PxHitFlag, hitFlag);

		PxQueryFilterData fd = (filterData.HasValue ? QueryFilterData::ToUnmanaged(filterData.Value) : PxQueryFilterData());

		UserQueryFilterCallback* qfcb = (filterCallback == nullptr ? NULL : &UserQueryFilterCallback(filterCallback));

		PxQueryCache* qc = (cache == nullptr ? NULL : &QueryCache::ToUnmanaged(cache));

		bool result = _scene->sweep(*g, p, d, distance, hc, f, fd, qfcb, qc);

		return result;
	}
	finally
	{
		delete[] hits;
	}
}

bool Scene::Overlap(Geometry^ geometry, Matrix pose, int maximumOverlaps, Func<array<OverlapHit^>^, bool>^ hitCall, [Optional] Nullable<QueryFilterData> filterData, [Optional] QueryFilterCallback^ filterCallback)
{
	ThrowIfNull(geometry, "geometry");
	if (maximumOverlaps < 0)
		throw gcnew ArgumentOutOfRangeException("maximumOverlaps");
	ThrowIfNull(hitCall, "hitCall");

	PxGeometry* g = geometry->ToUnmanaged();
	PxTransform p = MathUtil::MatrixToPxTransform(pose);

	PxOverlapHit* overlaps;
	try
	{
		overlaps = new PxOverlapHit[maximumOverlaps];
		InternalOverlapCallback oc(overlaps, maximumOverlaps, hitCall);

		PxQueryFilterData fd = (filterData.HasValue ? QueryFilterData::ToUnmanaged(filterData.Value) : PxQueryFilterData());

		UserQueryFilterCallback* qfcb = (filterCallback == nullptr ? NULL : &UserQueryFilterCallback(filterCallback));

		bool result = _scene->overlap(*g, p, oc, fd, qfcb);

		return result;
	}
	finally
	{
		delete[] overlaps;
	}
}

#pragma region Character
ControllerManager^ Scene::CreateControllerManager()
{
	PxControllerManager* manager = PxCreateControllerManager(*_scene);

	if (manager == NULL)
		throw gcnew FailedToCreateObjectException("Failed to create controller manager");

	ControllerManager^ c = gcnew ControllerManager(manager, this);

	return c;
}

#pragma region Articulation and Aggregate
void Scene::AddArticulation(Articulation^ articulation)
{
	ThrowIfNullOrDisposed(articulation, "articulation");

	_scene->addArticulation(*articulation->UnmanagedPointer);
}

void Scene::RemoveArticulation(Articulation^ articulation)
{
	_scene->removeArticulation(*articulation->UnmanagedPointer);
}

void Scene::AddAggregate(Aggregate^ aggregate)
{
	_scene->addAggregate(*aggregate->UnmanagedPointer);
}

void Scene::RemoveAggregate(Aggregate^ aggregate)
{
	_scene->removeAggregate(*aggregate->UnmanagedPointer);
}

array<Aggregate^>^ Scene::Aggregates::get()
{
	return ObjectTable::Instance->GetObjectsOfOwnerAndType<Aggregate^>(this);
}
#pragma endregion

#pragma region Collection
Collection^ Scene::CreateCollection()
{
	PxCollection* collection = PxCollectionExt::createCollection(*_scene);

	return gcnew Collection(collection, this);
}
#pragma endregion

SimulationEventCallback^ Scene::GetSimulationEventCallback()
{
	PxSimulationEventCallback* c = _scene->getSimulationEventCallback();

	if (c == NULL)
		return nullptr;

	// Get the SimulationEventCallback instance wrapping the unmanaged class
	if (ObjectTable::Instance->Contains((intptr_t)c))
		return ObjectTable::Instance->GetObject<SimulationEventCallback^>((intptr_t)c);
	else
		return nullptr;
}
void Scene::SetSimulationEventCallback(SimulationEventCallback^ callback)
{
	_scene->setSimulationEventCallback(callback == nullptr ? NULL : callback->UnmanagedPointer);
}

void Scene::ResetFiltering(Actor^ actor)
{
	_scene->resetFiltering(*actor->UnmanagedPointer);
}
void Scene::ResetFiltering(RigidActor^ actor, array<Shape^>^ shapes)
{
	auto s = new PxShape*[shapes->Length];
	for (int i = 0; i < shapes->Length; i++)
	{
		s[i] = shapes[i]->UnmanagedPointer;
	}

	_scene->resetFiltering(*actor->UnmanagedPointer, s, shapes->Length);

	delete[] s;
}

int Scene::CreateClient()
{
	return _scene->createClient();
}

int Scene::DynamicTreeRebuildRateHint::get()
{
	return _scene->getDynamicTreeRebuildRateHint();
}
void Scene::DynamicTreeRebuildRateHint::set(int value)
{
	_scene->setDynamicTreeRebuildRateHint(value);
}

int Scene::Timestamp::get()
{
	return _scene->getTimestamp();
}

PhysX::FrictionType Scene::FrictionType::get()
{
	return (PhysX::FrictionType)_scene->getFrictionType();
}
void Scene::FrictionType::set(PhysX::FrictionType value)
{
	_scene->setFrictionType(ToUnmanagedEnum(PxFrictionType, value));
}

SceneFlag Scene::Flags::get()
{
	return ToManagedEnum(SceneFlag, _scene->getFlags());
}

PhysX::SceneQueryUpdateMode Scene::SceneQueryUpdateMode::get()
{
	return (PhysX::SceneQueryUpdateMode)_scene->getSceneQueryUpdateMode();
}
void Scene::SceneQueryUpdateMode::set(PhysX::SceneQueryUpdateMode value)
{
	_scene->setSceneQueryUpdateMode(ToUnmanagedEnum(PxSceneQueryUpdateMode, value));
}

int Scene::SceneQueryStaticTimestamp::get()
{
	return _scene->getSceneQueryStaticTimestamp();
}

PhysX::SceneLimits^ Scene::SceneLimits::get()
{
	return PhysX::SceneLimits::ToManaged(_scene->getLimits());
}
void Scene::SceneLimits::set(PhysX::SceneLimits^ value)
{
	_scene->setLimits(PhysX::SceneLimits::ToUnmanaged(value));
}

PhysX::ContactModifyCallback^ Scene::ContactModifyCallback::get()
{
	return _contactModifyCallback;
}
void Scene::ContactModifyCallback::set(PhysX::ContactModifyCallback^ value)
{
	_contactModifyCallback = value;

	_scene->setContactModifyCallback(value == nullptr ? NULL : value->UnmanagedPointer);
}

PhysX::BroadPhaseCallback^ Scene::BroadPhaseCallback::get()
{
	return _broadPhaseCallback;
}
void Scene::BroadPhaseCallback::set(PhysX::BroadPhaseCallback^ value)
{
	_broadPhaseCallback = value;

	_scene->setBroadPhaseCallback(value == nullptr ? nullptr : value->UnmanagedPointer);
}

SimulationFilterCallback^ Scene::FilterCallback::get()
{
	return _simulationFilterCallback;
}

PxScene* Scene::UnmanagedPointer::get()
{
	return _scene;
}