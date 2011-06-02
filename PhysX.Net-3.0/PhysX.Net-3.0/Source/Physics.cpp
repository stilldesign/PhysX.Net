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
#include "Stream.h"
#include "DeformableMesh.h"
#include "MemoryStream.h"
#include "DeformableDesc.h"
#include "Deformable.h"
#include "HeightFieldDesc.h"
#include "HeightField.h"
#include "ParticleSystemDesc.h"
#include "ParticleSystem.h"
#include "FailedToCreateObjectException.h"
#include "Foundation.h"
#include "CookingParams.h"
#include "Cooking.h"
#include "TriangleMesh.h"
#include "VisualDebugger/Connection.h"

#include <PxDefaultAllocator.h>
#include <PxDefaultErrorCallback.h>
#include <PxBoxGeometry.h>
#include <PxParticleSystemDesc.h> 
#include <PxExtensionsAPI.h>
#include <PvdConnection.h>

using namespace PhysX;

static Physics::Physics()
{
	_instantiated = false;
}
Physics::Physics(PxPhysics* physics)
{
	if (physics == NULL)
		throw gcnew ArgumentNullException("physics");

	Init();

	_physics = physics;

	PostInit();
}
Physics::Physics([Optional] ErrorCallback^ errorCallback)
{
	Init();

	_allocator = new PxDefaultAllocator();
	_errorCallback = (errorCallback == nullptr ? gcnew DefaultErrorCallback() : errorCallback);

	_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_allocator, *_errorCallback->UnmanagedPointer, PxTolerancesScale(), true);

	if (_physics == NULL)
		throw gcnew Exception("Failed to create physics instance");

	PostInit();
}
void Physics::Init()
{
	if (_instantiated)
		throw gcnew PhysicsAlreadyInstantiatedException("The physics core object has already been instantiated. Check Physics.Instantiated before calling this ctor.");

	_scenes = gcnew List<Scene^>();
	_materials = gcnew List<Material^>();
	_rigidActors = gcnew List<RigidActor^>();
	_particleSystems = gcnew List<ParticleSystem^>();
	_particleFluids = gcnew List<ParticleFluid^>();
	_deformables = gcnew List<Deformable^>();
	_deformableMeshes = gcnew List<DeformableMesh^>();
	_heightFields = gcnew List<HeightField^>();
	_cooks = gcnew List<Cooking^>();
	_triangleMeshes = gcnew List<TriangleMesh^>();

	_instantiated = true;
}
void Physics::PostInit()
{
	ObjectTable::Add((intptr_t)_physics, this, nullptr);

	//

	if (!PxInitExtensions(*_physics))
		throw gcnew InvalidOperationException("Failed to initalize PhysX extensions");

	_foundation = gcnew PhysX::Foundation(&_physics->getFoundation(), this);

	//
	
	// Populate objects the exist in the physics object already
	PxMaterial** materials = new PxMaterial*[_physics->getNbMaterials()];
	_physics->getMaterials(materials, _physics->getNbMaterials());
	for (PxU32 i = 0; i < _physics->getNbMaterials(); i++)
	{
		_materials->Add(gcnew Material(materials[i], this));
	}
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

	_physics->release();
	_physics = NULL;

	_instantiated = false;

	SAFE_DELETE(_allocator);

	PxCloseExtensions();

	OnDisposed(this, nullptr);
}
bool Physics::Disposed::get()
{
	return _physics == NULL;
}

VisualDebugger::Connection^ Physics::ConnectToRemoteDebugger(String^ host, [Optional] Nullable<int> port, [Optional] Nullable<TimeSpan> timeout, [Optional] Nullable<bool> checkApi, [Optional] Nullable<RemoteDebuggerConnectionFlags> flags)
{
	if (host == nullptr)
		throw gcnew ArgumentNullException("host");
	if (timeout.HasValue && timeout.Value < TimeSpan::Zero)
		throw gcnew ArgumentOutOfRangeException("Timeout cannot be less than zero", "timeout");

	int p = port.GetValueOrDefault(5425);
	int to = (int)timeout.GetValueOrDefault(TimeSpan::FromSeconds(10)).TotalMilliseconds;
	bool chkapi = checkApi.GetValueOrDefault(false);
	RemoteDebuggerConnectionFlags f = flags.GetValueOrDefault(RemoteDebuggerConnectionFlags::Unknown);

	auto h = Util::ToUnmanagedString(host);

	PVD::PvdConnection* connection = PxExtensionVisualDebugger::connect(_physics->getPvdConnectionManager(), h, p, to, chkapi, ToUnmanagedEnum2(PxDebuggerConnectionFlags, f));
	
	if (connection == NULL)
		return nullptr;

	return gcnew VisualDebugger::Connection(connection, this);
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

	Scene^ scene = gcnew Scene(s, this);

	_scenes->Add(scene);

	return scene;
}

IEnumerable<Scene^>^ Physics::Scenes::get()
{
	return _scenes;
}
#pragma endregion

#pragma region Material
Material^ Physics::CreateMaterial(float staticFriction, float dynamicFriction, float restitution)
{
	PxMaterial* m = _physics->createMaterial(staticFriction, dynamicFriction, restitution);

	if (m == NULL)
		throw gcnew Exception("Failed to create material");

	Material^ material = gcnew Material(m, this);

	_materials->Add(material);

	return material;
}

IEnumerable<Material^>^ Physics::Materials::get()
{
	return _materials;
}
#pragma endregion

#pragma region HeightField
HeightField^ Physics::CreateHeightField(HeightFieldDesc^ desc)
{
	ThrowIfDescriptionIsNullOrInvalid(desc, "desc");

	auto hf = _physics->createHeightField(HeightFieldDesc::ToUnmanaged(desc));

	if (hf == NULL)
		throw gcnew FailedToCreateObjectException("Failed to create height field object");

	auto heightField = gcnew HeightField(hf, this);

	_heightFields->Add(heightField);

	return heightField;
}
#pragma endregion

#pragma region Material
TriangleMesh^ Physics::CreateTriangleMesh(System::IO::Stream^ stream)
{
	try
	{
		// TODO: Memory leak
		MemoryStream* ms = Util::StreamToUnmanagedMemoryStream(stream);

		PxTriangleMesh* triangleMesh = _physics->createTriangleMesh(*ms);

		if (triangleMesh == NULL)
			throw gcnew FailedToCreateObjectException("Failed to create triangle mesh");
	
		auto t = gcnew TriangleMesh(triangleMesh, this);

		_triangleMeshes->Add(t);

		//delete ms;

		return t;
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

	_rigidActors->Add(actor);

	return actor;
}

RigidStatic^ Physics::CreateRigidStatic([Optional] Nullable<Matrix> pose)
{
	PxTransform p = MathUtil::MatrixToPxTransform(pose.GetValueOrDefault(Matrix::Identity));

	PxRigidStatic* a = _physics->createRigidStatic(p);

	RigidStatic^ actor = gcnew RigidStatic(a, this);

	_rigidActors->Add(actor);

	return actor;
}

IEnumerable<RigidActor^>^ Physics::RigidActors::get()
{
	return _rigidActors;
}
#pragma endregion

#pragma region Particles
ParticleSystem^ Physics::CreateParticleSystem(ParticleSystemDesc^ desc)
{
	ThrowIfDescriptionIsNullOrInvalid(desc, "desc");

	auto s = _physics->createParticleSystem(ParticleSystemDesc::ToUnmanaged(desc));

	if (s == NULL)
		throw gcnew FailedToCreateObjectException("Failed to create particle system");

	return gcnew ParticleSystem(s, this);
}

IEnumerable<ParticleSystem^>^ Physics::ParticleSystems::get()
{
	return _particleSystems;
}
#pragma endregion

#pragma region Deformable
Deformable^ Physics::CreateDeformable(DeformableDesc^ desc)
{
	ThrowIfDescriptionIsNullOrInvalid(desc, "desc");

	auto d = _physics->createDeformable(DeformableDesc::ToUnmanaged(desc));

	auto deformable = gcnew Deformable(d, desc->DeformableMesh, this);

	_deformables->Add(deformable);

	return deformable;
}

DeformableMesh^ Physics::CreateDeformableMesh(System::IO::Stream^ stream)
{
	//ThrowIfNullOrDisposed(stream, "stream");

	int m = (int)stream->Length;

	stream->Position = 0;

	PxU8* streamCopy = new PxU8[m];
	array<Byte>^ buffer = gcnew array<Byte>(m);
	stream->Read(buffer, 0, m);
	Util::AsUnmanagedArray(buffer, (void*)streamCopy, m);

	MemoryStream s;
	s.storeBuffer(streamCopy, m);
	s.ResetSeek();

	auto dm = _physics->createDeformableMesh(s);

	if (dm == NULL)
		throw gcnew FailedToCreateObjectException("Failed to create deformable mesh");

	auto deformableMesh = gcnew DeformableMesh(dm, this);

	_deformableMeshes->Add(deformableMesh);

	return deformableMesh;
}
#pragma endregion

#pragma region Cooking
Cooking^ Physics::CreateCooking([Optional] CookingParams^ parameters)
{
	PxCookingParams p = (parameters == nullptr ? PxCookingParams() : CookingParams::ToUnmanaged(parameters));

	auto cooking = PxCreateCooking(PX_PHYSICS_VERSION, &_physics->getFoundation(), p);

	auto c = gcnew Cooking(cooking, this->Foundation);

	_cooks->Add(c);

	return c;
}
#pragma endregion

PxPhysics* Physics::UnmanagedPointer::get()
{
	return _physics;
}