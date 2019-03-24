#include "StdAfx.h"
#include "Physics.h"
#include "Scene.h"
#include "SceneDesc.h"
#include "Material.h"
#include "SceneCreationException.h"
#include "PhysicsAlreadyInstantiatedException.h"
#include "RigidDynamic.h"
#include "RigidStatic.h"
#include "RigidActor.h"
#include "ErrorCallback.h"
#include "HeightFieldDesc.h"
#include "HeightField.h"
#include "FailedToCreateObjectException.h"
#include "Foundation.h"
#include "CookingParams.h"
#include "Cooking.h"
#include "TriangleMesh.h"
#include "Shape.h"
#include "RuntimeFileChecks.h"
#include "Collection.h"
#include "Pvd.h"
#include "ConvexMesh.h"
#include "VehicleSDK.h"
#include "ConstraintShaderTable.h"
#include "Articulation.h"
#include "Aggregate.h"
#include "Joint.h"
#include "D6Joint.h"
#include "DistanceJoint.h"
#include "FixedJoint.h"
#include "PrismaticJoint.h"
#include "RevoluteJoint.h"
#include "SphericalJoint.h"

using namespace PhysX;

static Physics::Physics()
{
	_instantiated = false;
}
Physics::Physics(PhysX::Foundation^ foundation, [Optional] bool checkRuntimeFiles, [Optional] PhysX::VisualDebugger::Pvd^ pvd)
{
	ThrowIfNull(foundation, "foundation");
	if (checkRuntimeFiles)
		RuntimeFileChecks::Check();

	_foundation = foundation;
	_pvd = pvd;

	Init();

	PxFoundation* f = foundation->UnmanagedPointer;
	PxTolerancesScale s;

	_physics = PxCreatePhysics(
		PX_PHYSICS_VERSION,
		*f,
		s, 
		false,
		GetPointerOrNull(pvd));

	if (_physics == NULL)
		throw gcnew Exception("Failed to create physics instance");

	PostInit(foundation);
}
Physics::~Physics()
{
	this->!Physics();
}
Physics::!Physics()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;
	
	PxCloseExtensions();

	_physics->release();
	_physics = NULL;

	_instantiated = false;
	
	OnDisposed(this, nullptr);
}
bool Physics::Disposed::get()
{
	return (_physics == NULL);
}

void Physics::Init()
{
	if (_instantiated)
		throw gcnew PhysicsAlreadyInstantiatedException("The physics core object has already been instantiated. Check Physics.Instantiated before calling this ctor.");

	_instantiated = true;
}
void Physics::PostInit(PhysX::Foundation^ owner)
{
	ThrowIfNullOrDisposed(owner, "owner");

	ObjectTable::Instance->Add((intptr_t)_physics, this, owner);

	//

	// Initalize the extensions. This is required for almost anything useful in the PhysX SDK
	// The SDK errors catastrophically unless this is called
	if (!PxInitExtensions(*_physics, GetPointerOrNull(_pvd)))
		throw gcnew InvalidOperationException("Failed to initalize PhysX extensions");

	// Vehicle SDK
	_vehicleSDK = gcnew PhysX::VehicleSDK(this);

	//

	// Populate objects that exist in the physics object already
	PxMaterial** materials = new PxMaterial*[_physics->getNbMaterials()];
	_physics->getMaterials(materials, _physics->getNbMaterials());
	for (PxU32 i = 0; i < _physics->getNbMaterials(); i++)
	{
		auto material = gcnew Material(materials[i], this);
	}

	//

	ObjectTable::Instance->ObjectAdded += gcnew EventHandler<ObjectTableEventArgs^>(this, &Physics::OnObjectTableAdded);
	ObjectTable::Instance->ObjectRemoved += gcnew EventHandler<ObjectTableEventArgs^>(this, &Physics::OnObjectTableRemoved);
}

void Physics::OnObjectTableAdded(Object^ sender, ObjectTableEventArgs^ e)
{
	if (IsInstanceOf<Material^>(e->ManagedObject))
		OnMaterialAdded(dynamic_cast<Material^>(e->ManagedObject));
}
void Physics::OnObjectTableRemoved(Object^ sender, ObjectTableEventArgs^ e)
{
	if (IsInstanceOf<Material^>(e->ManagedObject))
		OnMaterialRemoved(dynamic_cast<Material^>(e->ManagedObject));
}

bool Physics::Instantiated::get()
{
	return _instantiated;
}

PhysX::Foundation^ Physics::Foundation::get()
{
	return _foundation;
}

#pragma region Scene
Scene^ Physics::CreateScene()
{
	auto sceneDesc = gcnew SceneDesc(Nullable<TolerancesScale>());

	return CreateScene(sceneDesc);
}
Scene^ Physics::CreateScene(SceneDesc^ sceneDesc)
{
	ThrowIfDescriptionIsNullOrInvalid(sceneDesc, "sceneDesc");

	PxScene* s = _physics->createScene(*sceneDesc->UnmanagedPointer);

	if (s == NULL)
		throw gcnew SceneCreationException("Failed to create scene");

	return gcnew Scene(s, this, sceneDesc->BroadPhaseCallback, sceneDesc->SimulationFilterCallback);
}

array<Scene^>^ Physics::Scenes::get()
{
	return ObjectTable::Instance->GetObjectsOfOwnerAndType<Scene^>(this);
}
#pragma endregion

#pragma region Material
Material^ Physics::CreateMaterial(float staticFriction, float dynamicFriction, float restitution)
{
	PxMaterial* m = _physics->createMaterial(staticFriction, dynamicFriction, restitution);

	if (m == NULL)
		throw gcnew Exception("Failed to create material");

	return gcnew Material(m, this);
}

array<Material^>^ Physics::Materials::get()
{
	return ObjectTable::Instance->GetObjectsOfOwnerAndType<Material^>(this);
}
#pragma endregion

#pragma region HeightField
HeightField^ Physics::CreateHeightField(System::IO::Stream^ stream)
{
	ThrowIfNull(stream, "stream");

	// TODO: Memory leak
	PxDefaultMemoryInputData* ms = Util::StreamToUnmanagedInputStream(stream);

	auto hf = _physics->createHeightField(*ms);

	if (hf == NULL)
		throw gcnew FailedToCreateObjectException("Failed to create height field object");

	return gcnew HeightField(hf, this);
}

array<PhysX::HeightField^>^ Physics::HeightFields::get()
{
	return ObjectTable::Instance->GetObjectsOfOwnerAndType<PhysX::HeightField^>(this);
}
#pragma endregion

#pragma region Triangle Mesh
TriangleMesh^ Physics::CreateTriangleMesh(System::IO::Stream^ stream)
{
	ThrowIfNull(stream, "stream");

	try
	{
		// TODO: Memory leak
		PxDefaultMemoryInputData* ms = Util::StreamToUnmanagedInputStream(stream);

		PxTriangleMesh* triangleMesh = _physics->createTriangleMesh(*ms);

		if (triangleMesh == NULL)
			throw gcnew FailedToCreateObjectException("Failed to create triangle mesh");
	
		auto t = gcnew PhysX::TriangleMesh(triangleMesh, this);

		//delete ms;

		return t;
	}
	finally
	{
		//delete[] ms.GetMemory();
	}
}

array<PhysX::TriangleMesh^>^ Physics::TriangleMesh::get()
{
	return ObjectTable::Instance->GetObjectsOfOwnerAndType<PhysX::TriangleMesh^>(this);
}
#pragma endregion

#pragma region Convex Mesh
ConvexMesh^ Physics::CreateConvexMesh(System::IO::Stream^ stream)
{
	try
	{
		// TODO: Memory leak
		PxDefaultMemoryInputData* ms = Util::StreamToUnmanagedInputStream(stream);

		PxConvexMesh* convexMesh = _physics->createConvexMesh(*ms);

		if (convexMesh == NULL)
			throw gcnew FailedToCreateObjectException("Failed to create convex mesh");
	
		auto cm = gcnew PhysX::ConvexMesh(convexMesh, this);

		//delete ms;

		return cm;
	}
	finally
	{
		//delete[] ms.GetMemory();
	}
}

array<PhysX::ConvexMesh^>^ Physics::ConvexMesh::get()
{
	return ObjectTable::Instance->GetObjectsOfOwnerAndType<PhysX::ConvexMesh^>(this);
}
#pragma endregion

#pragma region Rigid Actors
RigidDynamic^ Physics::CreateRigidDynamic([Optional] Nullable<Matrix> pose)
{
	PxTransform p = MathUtil::MatrixToPxTransform(pose.GetValueOrDefault(Matrix::Identity));

	PxRigidDynamic* a = _physics->createRigidDynamic(p);

	RigidDynamic^ actor = gcnew RigidDynamic(a, this);

	return actor;
}

RigidStatic^ Physics::CreateRigidStatic([Optional] Nullable<Matrix> pose)
{
	PxTransform p = MathUtil::MatrixToPxTransform(pose.GetValueOrDefault(Matrix::Identity));

	PxRigidStatic* a = _physics->createRigidStatic(p);

	RigidStatic^ actor = gcnew RigidStatic(a, this);

	return actor;
}

array<RigidActor^>^ Physics::RigidActors::get()
{
	return ObjectTable::Instance->GetObjectsOfOwnerAndType<RigidActor^>(this);
}
#pragma endregion

#pragma region Joints
Joint^ Physics::CreateJoint(JointType type, RigidActor^ actor0, Matrix localFrame0, RigidActor^ actor1, Matrix localFrame1)
{
	PxPhysics* physics = this->UnmanagedPointer;

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
T Physics::CreateJoint(RigidActor^ actor0, Matrix localFrame0, RigidActor^ actor1, Matrix localFrame1)
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

array<Joint^>^ Physics::Joints::get()
{
	return ObjectTable::Instance->GetObjectsOfType<Joint^>();
}
#pragma endregion

#pragma region Cooking
Cooking^ Physics::CreateCooking([Optional] CookingParams^ parameters)
{
	PxCookingParams p = (parameters == nullptr ? PxCookingParams(_physics->getTolerancesScale()) : CookingParams::ToUnmanaged(parameters));

	auto cooking = PxCreateCooking(PX_PHYSICS_VERSION, _physics->getFoundation(), p);

	auto c = gcnew Cooking(cooking, this->Foundation);

	return c;
}
#pragma endregion

#pragma region Collection
Collection^ Physics::CreateCollection()
{
	PxCollection* collection = PxCollectionExt::createCollection(*_physics);

	return gcnew Collection(collection, this);
}
#pragma endregion

#pragma region Remote Debugger
PhysX::VisualDebugger::Pvd^ Physics::Pvd::get()
{
	return _pvd;
}
#pragma endregion

// TODO: Implement
Constraint^ Physics::CreateConstraint(RigidActor^ actor0, RigidActor^ actor1, ConstraintConnector^ connector, ConstraintShaderTable^ shaders, int dataSize)
{
	ThrowIfNull(actor0, "actor0");
	ThrowIfNull(actor1, "actor1");

	throw gcnew NotImplementedException();

	//PxConstraint* c = _physics->createConstraint(
	//	actor0->UnmanagedPointer, 
	//	actor1->UnmanagedPointer, 
	//	*connector->UnmanagedPointer, 
	//	*shaders->UnmanagedPointer, 
	//	dataSize);

	//return gcnew Constraint(c);
}

PhysX::VehicleSDK^ Physics::VehicleSDK::get()
{
	return _vehicleSDK;
}

Articulation^ Physics::CreateArticulation()
{
	PxArticulation* a = _physics->createArticulation();

	return gcnew Articulation(a, this);
}

Aggregate^ Physics::CreateAggregate(int maximumSize, bool enableSelfCollision)
{
	PxAggregate* a = _physics->createAggregate(maximumSize, enableSelfCollision);

	return gcnew Aggregate(a, this);
}

PxPhysics* Physics::UnmanagedPointer::get()
{
	return _physics;
}