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
#include "ParticleSystem.h"
#include "FailedToCreateObjectException.h"
#include "Foundation.h"
#include "CookingParams.h"
#include "Cooking.h"
#include "TriangleMesh.h"
#include "Shape.h"
#include "RuntimeFileChecks.h"
#include "ParticleFluid.h"
#include "Collection.h"
#include "Connection.h"
#include "ConnectionManager.h"
#include "ConvexMesh.h"
#include "VehicleSDK.h"
#include "ClothFabric.h"
#include "Cloth.h"
#include "ClothCollisionData.h"

#include <PxDefaultAllocator.h>
#include <PxDefaultErrorCallback.h>
#include <PxBoxGeometry.h>
#include <PxExtensionsAPI.h>
#include <PvdConnection.h>

using namespace PhysX;

static Physics::Physics()
{
	_instantiated = false;
}
Physics::Physics(PhysX::Foundation^ foundation, [Optional] bool checkRuntimeFiles)
{
	ThrowIfNull(foundation, "foundation");
	if (checkRuntimeFiles)
		RuntimeFileChecks::Check();

	_foundation = foundation;

	Init();

	PxFoundation* f = foundation->UnmanagedPointer;
	PxTolerancesScale s;

	_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *f, s);

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

	ObjectTable::Add((intptr_t)_physics, this, owner);

	//

	// Initalize the extensions. This is required for almost anything useful in the PhysX SDK
	// The SDK errors catastrophically unless this is called
	if (!PxInitExtensions(*_physics))
		throw gcnew InvalidOperationException("Failed to initalize PhysX extensions");

	// Vehicle SDK
	_vehicleSDK = gcnew PhysX::VehicleSDK(this);

	// PVD
	{
		auto connectionManager = _physics->getPvdConnectionManager();

		// Can be NULL if the version of PhysX is not compiled with PVD support.
		if (connectionManager != NULL)
		{
			_connectionManager = gcnew PhysX::VisualDebugger::ConnectionManager(connectionManager, this);
		}
	}

	//

	// Populate objects that exist in the physics object already
	PxMaterial** materials = new PxMaterial*[_physics->getNbMaterials()];
	_physics->getMaterials(materials, _physics->getNbMaterials());
	for (PxU32 i = 0; i < _physics->getNbMaterials(); i++)
	{
		auto material = gcnew Material(materials[i], this);
	}
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
	auto sceneDesc = gcnew SceneDesc(TolerancesScale());

	return CreateScene(sceneDesc);
}
Scene^ Physics::CreateScene(SceneDesc^ sceneDesc)
{
	ThrowIfDescriptionIsNullOrInvalid(sceneDesc, "sceneDesc");

	PxScene* s = _physics->createScene(*sceneDesc->UnmanagedPointer);

	if (s == NULL)
		throw gcnew SceneCreationException("Failed to create scene");

	return gcnew Scene(s, this);
}

IEnumerable<Scene^>^ Physics::Scenes::get()
{
	return ObjectTable::GetObjectsOfOwnerAndType<Scene^>(this);
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

IEnumerable<Material^>^ Physics::Materials::get()
{
	return ObjectTable::GetObjectsOfOwnerAndType<Material^>(this);
}
#pragma endregion

#pragma region HeightField
HeightField^ Physics::CreateHeightField(HeightFieldDesc^ desc)
{
	ThrowIfDescriptionIsNullOrInvalid(desc, "desc");

	auto hf = _physics->createHeightField(HeightFieldDesc::ToUnmanaged(desc));

	if (hf == NULL)
		throw gcnew FailedToCreateObjectException("Failed to create height field object");

	return gcnew HeightField(hf, this);
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
	
		auto t = gcnew TriangleMesh(triangleMesh, this);

		//delete ms;

		return t;
	}
	finally
	{
		//delete[] ms.GetMemory();
	}
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
	
		auto cm = gcnew ConvexMesh(convexMesh, this);

		//delete ms;

		return cm;
	}
	finally
	{
		//delete[] ms.GetMemory();
	}
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

IEnumerable<RigidActor^>^ Physics::RigidActors::get()
{
	return ObjectTable::GetObjectsOfOwnerAndType<RigidActor^>(this);
}
#pragma endregion

#pragma region Particle System
ParticleSystem^ Physics::CreateParticleSystem(int maxParticles)
{
	return CreateParticleSystem(maxParticles, false);
}
ParticleSystem^ Physics::CreateParticleSystem(int maxParticles, bool perParticleRestOffset)
{
	auto s = _physics->createParticleSystem(maxParticles, perParticleRestOffset);

	if (s == NULL)
		throw gcnew FailedToCreateObjectException("Failed to create particle system");

	return gcnew ParticleSystem(s, this);
}

IEnumerable<ParticleSystem^>^ Physics::ParticleSystems::get()
{
	return ObjectTable::GetObjectsOfOwnerAndType<ParticleSystem^>(this);
}
#pragma endregion

#pragma region Particle Fluid
ParticleFluid^ Physics::CreateParticleFluid(int maximumParticles)
{
	return CreateParticleFluid(maximumParticles, false);
}
ParticleFluid^ Physics::CreateParticleFluid(int maximumParticles, bool perParticleRestOffset)
{
	PxParticleFluid* particleFluid = _physics->createParticleFluid(maximumParticles, perParticleRestOffset);

	if (particleFluid == NULL)
		throw gcnew FailedToCreateObjectException("Failed to create particle fluid");

	return gcnew ParticleFluid(particleFluid, this);
}

array<ParticleFluid^>^ Physics::ParticleFluids::get()
{
	return ObjectTable::GetObjectsOfType<ParticleFluid^>();
}
#pragma endregion

#pragma region Cooking
Cooking^ Physics::CreateCooking([Optional] CookingParams^ parameters)
{
	PxCookingParams p = (parameters == nullptr ? PxCookingParams() : CookingParams::ToUnmanaged(parameters));

	auto cooking = PxCreateCooking(PX_PHYSICS_VERSION, _physics->getFoundation(), p);

	auto c = gcnew Cooking(cooking, this->Foundation);

	return c;
}
#pragma endregion

#pragma region Collection
Collection^ Physics::CreateCollection()
{
	auto collection = _physics->createCollection();

	return gcnew Collection(collection, this);
}

void Physics::ReleaseCollection(Collection^ collection)
{
	ThrowIfNullOrDisposed(collection, "collection");

	_physics->releaseCollection(*collection->UnmanagedPointer);
}

void Physics::AddCollection(Collection^ collection, Scene^ scene)
{
	ThrowIfNullOrDisposed(collection, "collection");
	ThrowIfNullOrDisposed(scene, "scene");

	_physics->addCollection(*collection->UnmanagedPointer, *scene->UnmanagedPointer);
}
#pragma endregion

#pragma region Remote Debugger
PhysX::VisualDebugger::ConnectionManager^ Physics::PvdConnectionManager::get()
{
	return _connectionManager;
}
PhysX::VisualDebugger::ConnectionManager^ Physics::RemoteDebugger::get()
{
	return PvdConnectionManager;
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

void Physics::GetSDKMetaData(System::IO::Stream^ stream)
{
	ThrowIfNull(stream, "stream");
	if (!stream->CanWrite)
		throw gcnew ArgumentNullException("stream");

	PxDefaultMemoryOutputStream s;

	PxGetSDKMetaData(*_physics, s);

	Util::CopyIntoStream(&s, stream);
}

#pragma region Cloth
Cloth^ Physics::CreateCloth(Matrix globalPose, ClothFabric^ fabric, array<ClothParticle>^ particles, ClothCollisionData^ collisionData, ClothFlag flags)
{
	PxTransform gp = MathUtil::MatrixToPxTransform(globalPose);
	PxClothFabric* cf = fabric->UnmanagedPointer;

	PxClothParticle* cp;
	if (particles->Length == 0)
	{
		cp = NULL;
	}
	else
	{
		pin_ptr<ClothParticle> cp_pin = &particles[0];

		cp = (PxClothParticle*)cp_pin;
	}

	PxClothCollisionData cd = ClothCollisionData::ToUnmanaged(collisionData);
	PxClothFlags f = ToUnmanagedEnum2(PxClothFlags, flags);

	PxCloth* cloth = _physics->createCloth(gp, *cf, cp, cd, f);

	if (cloth == NULL)
		throw gcnew FailedToCreateObjectException("Failed to create PxCloth instance. See the error log of the Physics instance.");

	Cloth^ c = gcnew Cloth(cloth, this);

	delete[] cd.spheres;
	delete[] cd.pairIndexBuffer;

	return c;
}

IEnumerable<Cloth^>^ Physics::Cloths::get()
{
	return ObjectTable::GetObjectsOfOwnerAndType<Cloth^>(this);
}

ClothFabric^ Physics::CreateClothFabric(System::IO::Stream^ cookedStream)
{
	ThrowIfNull(cookedStream, "cookedStream");
	if (!cookedStream->CanRead)
		throw gcnew ArgumentNullException("Cannot read from cooked stream", "cookedStream");
	if (cookedStream->Length == 0)
		throw gcnew ArgumentNullException("Cooked stream is of zero length", "cookedStream");

	int n = (int)cookedStream->Length;

	// Read the data from the stream
	array<Byte>^ cookedData = gcnew array<Byte>(n);
	cookedStream->Read(cookedData, 0, n);

	// Get a pointer to the first byte
	pin_ptr<Byte> pin = &cookedData[0];

	// Create an PxInputStream around the data
	PxDefaultMemoryInputData in(pin, n);

	// Create the cloth fabric
	PxClothFabric* clothFabric = _physics->createClothFabric(in);

	if (clothFabric == NULL)
		throw gcnew FailedToCreateObjectException("Failed to create PxClothFabric instance. See your error output instance for any details");

	// Create a managed version of the cloth fabric
	ClothFabric^ cf = gcnew ClothFabric(clothFabric, this);

	return cf;
}
ClothFabric^ Physics::CreateClothFabric(int numberOfParticles, array<int>^ phases, array<ClothFabricPhaseType>^ phaseTypes, array<float>^ restValues, array<int>^ sets, array<int>^ fibers, array<int>^ indices)
{
	// TODO: Argument check

	PxU32 nbPhases = phases->Length;
	pin_ptr<int> p = &phases[0];
	pin_ptr<ClothFabricPhaseType> pt = &phaseTypes[0];
	PxU32 nbRestValues = restValues->Length;
	pin_ptr<float> rv = &restValues[0];
	PxU32 nbSets = sets->Length;
	pin_ptr<int> s = &sets[0];
	pin_ptr<int> f = &fibers[0];
	pin_ptr<int> i = &indices[0];

	PxClothFabric* clothFabric = _physics->createClothFabric
	(
		numberOfParticles,
		nbPhases,
		(PxU32*)p,
		(PxClothFabricPhaseType::Enum*)pt,
		nbRestValues,
		rv,
		nbSets,
		(PxU32*)s,
		(PxU32*)f,
		(PxU32*)i
	);

	ClothFabric^ cf = gcnew ClothFabric(clothFabric, this);

	return cf;
}

IEnumerable<ClothFabric^>^ Physics::ClothFabrics::get()
{
	return ObjectTable::GetObjectsOfOwnerAndType<ClothFabric^>(this);
}
#pragma endregion

PhysX::VehicleSDK^ Physics::VehicleSDK::get()
{
	return _vehicleSDK;
}

PxPhysics* Physics::UnmanagedPointer::get()
{
	return _physics;
}