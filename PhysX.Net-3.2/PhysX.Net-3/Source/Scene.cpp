#include "StdAfx.h"
#include "Scene.h"
#include "SceneDesc.h"
#include "Bounds3.h"
#include "SceneQueryHit.h"
#include "SceneQueryFilterData.h"
#include "Geometry.h"
#include "Actor.h"
#include "ActiveTransform.h"
#include "Physics.h"
#include "ControllerManager.h"
#include "Shape.h"
#include "RaycastHit.h"
#include "Joint.h"
#include "D6Joint.h"
#include "DistanceJoint.h"
#include "FixedJoint.h"
#include "RigidActor.h"
#include "PrismaticJoint.h"
#include "RevoluteJoint.h"
#include "SphericalJoint.h"
#include "SimulationStatistics.h"
#include "Articulation.h"
#include "Aggregate.h"
#include "SceneSweepOperationObject.h"
#include "SweepHit.h"
#include "FailedToCreateObjectException.h"
#include "RenderBuffer.h"
#include "SweepCache.h"
#include <PxFixedJoint.h>

using namespace PhysX;

Scene::Scene(PxScene* scene, PhysX::Physics^ physics)
{
	if (scene == NULL)
		throw gcnew ArgumentNullException("scene");
	ThrowIfNullOrDisposed(physics, "physics");

	_scene = scene;
	_physics = physics;

	ObjectTable::Add((intptr_t)scene, this, physics);
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

SceneDesc^ Scene::SaveToDesc()
{
	SceneDesc^ desc = gcnew SceneDesc(TolerancesScale());
	
	if (!this->UnmanagedPointer->saveToDesc(*desc->UnmanagedPointer))
		return nullptr;

	return desc;
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

RenderBuffer^ Scene::GetRenderBuffer()
{
	const PxRenderBuffer& buffer = this->UnmanagedPointer->getRenderBuffer();

	auto b = RenderBuffer::ToManaged(buffer);

	return b;
}

SimulationStatistics^ Scene::GetSimulationStatistics()
{
	PxSimulationStatistics stats;
	_scene->getSimulationStatistics(stats);

	return SimulationStatistics::ToManaged(&stats);
}

#pragma region Actors
IEnumerable<Actor^>^ Scene::Actors::get()
{
	return ObjectTable::GetObjectsOfOwnerAndType<Actor^>(this->Physics);
}
int Scene::GetNumberOfActors(ActorTypeSelectionFlag types)
{
	return _scene->getNbActors(ToUnmanagedEnum(PxActorTypeSelectionFlag, types));
}

array<ActiveTransform^>^ Scene::GetActiveTransforms([Optional] Nullable<int> clientId)
{
	int c = clientId.GetValueOrDefault(PX_DEFAULT_CLIENT);

	PxU32 n;
	PxActiveTransform* t = _scene->getActiveTransforms(n, c);

	array<ActiveTransform^>^ transforms = gcnew array<ActiveTransform^>(n);
	for (PxU32 i = 0; i < n; i++)
	{
		transforms[i] = ActiveTransform::ToManaged(t[i]);
	}

	return transforms;
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

/// <summary>Gets the articulations.</summary>
IEnumerable<Articulation^>^ Scene::Articulations::get()
{
	return ObjectTable::GetObjectsOfOwnerAndType<Articulation^>(this);
}
#pragma endregion

#pragma region Joints
Joint^ Scene::CreateJoint(JointType type, RigidActor^ actor0, Matrix localFrame0, RigidActor^ actor1, Matrix localFrame1)
{
	PxPhysics* physics = this->Physics->UnmanagedPointer;

	PxRigidActor* a0 = GetPointerOrNull(actor0);
	PxRigidActor* a1 = GetPointerOrNull(actor1);

	PxTransform lf0 = MathUtil::MatrixToPxTransform(localFrame0);
	PxTransform lf1 = MathUtil::MatrixToPxTransform(localFrame1);

	Joint^ joint = nullptr;

	switch (type)
	{
		case JointType::D6:
		{
			auto d6 = PxD6JointCreate(*physics, a0, lf0, a1, lf1);

			auto d6Joint = joint = gcnew D6Joint(d6, this);
		}
		break;

		case JointType::Distance:
		{
			auto distance = PxDistanceJointCreate(*physics, a0, lf0, a1, lf1);

			auto distanceJoint = joint = gcnew DistanceJoint(distance, this);
		}
		break;

		case JointType::Fixed:
		{
			auto fixed = PxFixedJointCreate(*physics, a0, lf0, a1, lf1);

			auto fixedJoint = joint = gcnew FixedJoint(fixed, this);
		}
		break;

		case JointType::Prismatic:
		{
			auto primatic = PxPrismaticJointCreate(*physics, a0, lf0, a1, lf1);

			auto primaticJoint = joint = gcnew PrismaticJoint(primatic, this);
		}
		break;

		case JointType::Revolute:
		{
			auto revolute = PxRevoluteJointCreate(*physics, a0, lf0, a1, lf1);

			auto revoluteJoint = joint = gcnew RevoluteJoint(revolute, this);
		}
		break;

		case JointType::Spherical:
		{
			auto spherical = PxSphericalJointCreate(*physics, a0, lf0, a1, lf1);

			auto sphericalJoint = joint = gcnew SphericalJoint(spherical, this);
		}
		break;
	}

	if (joint == nullptr)
		throw gcnew ArgumentException(String::Format("Unsupported joint type {0}", type));

	return joint;
}

generic<typename T> where T : Joint
T Scene::CreateJoint(RigidActor^ actor0, Matrix localFrame0, RigidActor^ actor1, Matrix localFrame1)
{
	JointType type;

	if (T::typeid == D6Joint::typeid)
		type = JointType::D6;

	else if (T::typeid == DistanceJoint::typeid)
		type = JointType::Distance;

	else if (T::typeid == FixedJoint::typeid)
		type = JointType::Fixed;

	else if (T::typeid == PrismaticJoint::typeid)
		type = JointType::Prismatic;

	else if (T::typeid == RevoluteJoint::typeid)
		type = JointType::Revolute;

	else if (T::typeid == SphericalJoint::typeid)
		type = JointType::Spherical;

	else
		throw gcnew ArgumentException("Unsupported joint type");

	return (T)CreateJoint(type, actor0, localFrame0, actor1, localFrame1);
}

IEnumerable<Joint^>^ Scene::Joints::get()
{
	// Extend this object table method to support inheritance selection
	return ObjectTable::GetObjectsOfOwnerAndType<Joint^>(this);
}
#pragma endregion

#pragma region Grouping
ConstraintDominance Scene::GetDominanceGroupPair (Byte group1, Byte group2)
{
	return ConstraintDominance::ToManaged(_scene->getDominanceGroupPair(group1, group2));
}

void Scene::SetDominanceGroupPair(Byte group1, Byte group2, ConstraintDominance dominance)
{
	_scene->setDominanceGroupPair(group1, group2, ConstraintDominance::ToUnmanaged(dominance));
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
void Scene::Flush([Optional] bool sendPendingReports)
{
	_scene->flush(sendPendingReports);
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
	return Bounds3::FromUnmanaged(_scene->getVisualizationCullingBox());
}
void Scene::VisualizationCullingBox::set(Bounds3 value)
{
	_scene->setVisualizationCullingBox(Bounds3::ToUnmanaged(value));
}
#pragma endregion

#pragma region Raycast
SceneQueryHit^ Scene::RaycastAny(Vector3 origin, Vector3 direction, float distance, [Optional] Nullable<SceneQueryFilterData> filterData)
{
	PxSceneQueryFilterData filter = (filterData.HasValue ? SceneQueryFilterData::ToUnmanaged(filterData.Value) : PxSceneQueryFilterData());

	PxSceneQueryHit hit;
	bool result = _scene->raycastAny(MathUtil::Vector3ToPxVec3(origin), MathUtil::Vector3ToPxVec3(direction), distance, hit, filter);

	if (!result)
		return nullptr;

	return SceneQueryHit::ToManaged(&hit);
}

RaycastHit^ Scene::RaycastSingle(Vector3 origin, Vector3 direction, float distance, [Optional] Nullable<SceneQueryFlags> outputFlags, [Optional] Nullable<SceneQueryFilterData> filterData)
{
	PxSceneQueryFilterData filter = (filterData.HasValue ? SceneQueryFilterData::ToUnmanaged(filterData.Value) : PxSceneQueryFilterData());

	PxSceneQueryFlags of = ToUnmanagedEnum(PxSceneQueryFlag, outputFlags.GetValueOrDefault(SceneQueryFlags::Distance));
	PxRaycastHit hit;
	bool result = _scene->raycastSingle(MathUtil::Vector3ToPxVec3(origin), MathUtil::Vector3ToPxVec3(direction), distance, of, hit);

	if (!result)
		return nullptr;

	return RaycastHit::ToManaged(hit);
}

array<RaycastHit^>^ Scene::RaycastMultiple(Vector3 origin, Vector3 direction, float distance, SceneQueryFlags outputFlags, int hitBufferSize, [Optional] Nullable<SceneQueryFilterData> filterData)
{
	if (hitBufferSize < 0)
		throw gcnew ArgumentOutOfRangeException("hitBufferSize", "Hit buffer size must be greater than or equal to 0");
	if (hitBufferSize == 0)
		return gcnew array<RaycastHit^>(0);

	PxRaycastHit* h;
	try
	{
		h = new PxRaycastHit[hitBufferSize];
		bool blockingHit = false;
		PxSceneQueryFilterData filter = (filterData.HasValue ? SceneQueryFilterData::ToUnmanaged(filterData.Value) : PxSceneQueryFilterData());

		int hitCount = _scene->raycastMultiple
		(
			UV(origin), 
			UV(direction), 
			distance, 
			ToUnmanagedEnum(PxSceneQueryFlag, outputFlags), 
			h, 
			hitBufferSize, 
			blockingHit, 
			filter
		);

		if (hitCount == -1)
			return nullptr;

		int n = (hitCount < hitBufferSize ? hitCount : hitBufferSize);

		auto hits = gcnew array<RaycastHit^>(n);
		for (int i = 0; i < n; i++)
		{
			hits[i] = RaycastHit::ToManaged(*(h + i));
		}

		return hits;
	}
	finally
	{
		delete[] h;
		h = NULL;
	}
}
#pragma endregion

#pragma region Sweep
SceneQueryHit^ Scene::SweepAny(Geometry^ geometry, Matrix pose, Vector3 direction, float distance, SceneQueryFlags queryFlags, [Optional] Nullable<SceneQueryFilterData> filterData)
{
	ThrowIfNull(geometry, "geometry");

	PxGeometry* geom;
	try
	{
		PxSceneQueryFilterData fd = (filterData.HasValue ? SceneQueryFilterData::ToUnmanaged(filterData.Value) : PxSceneQueryFilterData());

		geom = geometry->ToUnmanaged();

		PxSceneQueryHit hit;
		bool result = _scene->sweepAny
		(
			*geom,
			MathUtil::MatrixToPxTransform(pose),
			MathUtil::Vector3ToPxVec3(direction),
			distance,
			ToUnmanagedEnum(PxSceneQueryFlag, queryFlags),
			hit,
			fd
		);

		if (!result)
			return nullptr;

		return SceneQueryHit::ToManaged(&hit);
	}
	finally
	{
		delete geom;
	}
}

array<SweepHit^>^ Scene::SweepMultiple(PhysX::Geometry^ geometry, Matrix pose, Nullable<PhysX::FilterData> filterData, Vector3 direction, float distance, SceneQueryFlags outputFlags, int maxNumberOfHits, Nullable<SceneQueryFilterFlag> filterFlags)
{
	ThrowIfNull(geometry, "geometry");

	auto objects = gcnew array<SceneSweepOperationObject^>(1);
		objects[0] = gcnew SceneSweepOperationObject(geometry, pose, filterData);

	return SweepMultiple(objects, direction, distance, outputFlags, maxNumberOfHits, filterFlags);
}
array<SweepHit^>^ Scene::SweepMultiple(array<SceneSweepOperationObject^>^ objects, Vector3 direction, float distance, SceneQueryFlags outputFlags, int maxNumberOfHits, Nullable<SceneQueryFilterFlag> filterFlags)
{
	ThrowIfNull(objects, "objects");
	if (objects->Length == 0)
		return nullptr;

	int n = objects->Length;

	// Checks

	// Make sure that (if any) filter data is supplied, all filter data is supplied
	bool useFilterData = objects[0]->FilterData.HasValue;
	if (useFilterData)
	{
		for (int i = 1; i < n; i++)
		{
			if (!objects[i]->FilterData.HasValue)
				throw gcnew ArgumentException("Either no FilterData objects should be supplied, or all FilterData objects should be supplied");
		}
	}

	// Geometry
	for each(SceneSweepOperationObject^ object in objects)
	{
		if (object->Geometry == nullptr)
			throw gcnew ArgumentException("Objects array contains a null geometry", "objects");
	}

	//

	const PxGeometry** g = new const PxGeometry*[n];
	PxTransform* t = new PxTransform[n];
	PxFilterData* f = useFilterData ? new PxFilterData[n] : NULL;

	for (int i = 0; i < n; i++)
	{
		g[i] = objects[i]->Geometry->ToUnmanaged();
		t[i] = MathUtil::MatrixToPxTransform(objects[i]->Pose);

		if (useFilterData)
			f[i] = FilterData::ToUnmanaged(objects[i]->FilterData.Value);
	}

	PxSceneQueryFilterFlags ff = filterFlags.HasValue ? 
		ToUnmanagedEnum2(PxSceneQueryFilterFlags, filterFlags.Value) : 
		PxSceneQueryFilterFlag::eDYNAMIC|PxSceneQueryFilterFlag::eSTATIC;

	//
	
	PxSweepHit* h = new PxSweepHit[maxNumberOfHits];
	bool blockingHit;
	int numOfHits = _scene->sweepMultiple
	(
		g, 
		t,
		f,
		n,
		UV(direction),
		distance, 
		ToUnmanagedEnum(PxSceneQueryFlag, outputFlags), 
		h,
		maxNumberOfHits, 
		blockingHit, 
		ff
	);

	// Clean up
	for (int i = 0; i < n; i++)
	{
		delete g[i];
	}
	delete[] g;
	delete[] t;
	delete[] f;
	
	if (!blockingHit || numOfHits == -1)
	{
		delete[] h;

		return nullptr;
	}

	auto hits = gcnew array<SweepHit^>(numOfHits);
	for (int i = 0; i < numOfHits; i++)
	{
		hits[i] = SweepHit::ToManaged(h[i]);
	}

	delete[] h;

	return hits;
}
#pragma endregion

#pragma region Overlap
Shape^ Scene::OverlapAny(Geometry^ geometry, Matrix pose, [Optional] Nullable<SceneQueryFilterData> filterData)
{
	ThrowIfNull(geometry, "geometry");

	PxSceneQueryFilterData filter = (filterData.HasValue ? SceneQueryFilterData::ToUnmanaged(filterData.Value) : PxSceneQueryFilterData());

	PxShape* hitShape = NULL;
	bool result = _scene->overlapAny(*geometry->ToUnmanaged(), MathUtil::MatrixToPxTransform(pose), hitShape, filter);

	if (!result)
		return nullptr;

	return ObjectTable::GetObject<Shape^>((intptr_t)hitShape);
}

array<Shape^>^ Scene::OverlapMultiple(Geometry^ geometry, Matrix pose, [Optional] Nullable<int> hitLimit, [Optional] Nullable<SceneQueryFilterData> filterData)
{
	ThrowIfNull(geometry, "geometry");

	PxSceneQueryFilterData filter = (filterData.HasValue ? SceneQueryFilterData::ToUnmanaged(filterData.Value) : PxSceneQueryFilterData());

	int hitLimitVal = hitLimit.GetValueOrDefault(100);
	if (hitLimitVal <= 0)
		return gcnew array<Shape^>(0);

	PxGeometry* g = geometry->ToUnmanaged();

	PxShape** hitShapes = new PxShape*[hitLimitVal];

	int hitCount = _scene->overlapMultiple(*g, MathUtil::MatrixToPxTransform(pose), hitShapes, hitLimitVal, filter);

	auto shapes = gcnew array<Shape^>(hitCount);
	for (int i = 0; i < hitCount; i++)
	{
		shapes[i] = ObjectTable::GetObject<Shape^>((intptr_t)hitShapes[i]);
	}

	delete[] hitShapes;

	delete g;

	return shapes;
}
#pragma endregion

#pragma region Character
ControllerManager^ Scene::CreateControllerManager()
{
	PxControllerManager* manager = PxCreateControllerManager(_scene->getPhysics().getFoundation());

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

IEnumerable<Aggregate^>^ Scene::Aggregates::get()
{
	return ObjectTable::GetObjectsOfOwnerAndType<Aggregate^>(this);
}
#pragma endregion

SweepCache^ Scene::CreateSweepCache()
{
	// 5 is the default size in the SDK
	return CreateSweepCache(5.0f);
}
SweepCache^ Scene::CreateSweepCache(float dimensions)
{
	PxSweepCache* sc = _scene->createSweepCache(dimensions);

	return gcnew SweepCache(sc);
}

SimulationEventCallback^ Scene::GetSimulationEventCallback(int clientId)
{
	PxSimulationEventCallback* c = _scene->getSimulationEventCallback(clientId);

	if (c == NULL)
		return nullptr;

	// Get the SimulationEventCallback instance wrapping the unmanaged class
	if (ObjectTable::Contains((intptr_t)c))
		return ObjectTable::GetObject<SimulationEventCallback^>((intptr_t)c);
	else
		return nullptr;
}
void Scene::SetSimulationEventCallback(SimulationEventCallback^ callback, int clientId)
{
	_scene->setSimulationEventCallback(callback == nullptr ? NULL : callback->UnmanagedPointer, clientId);
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

//

SceneFlag Scene::Flags::get()
{
	return ToManagedEnum(SceneFlag, _scene->getFlags());
}

PxScene* Scene::UnmanagedPointer::get()
{
	return _scene;
}