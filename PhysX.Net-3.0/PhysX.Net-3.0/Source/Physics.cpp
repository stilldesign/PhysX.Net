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
#include "Attachment.h"
#include "Shape.h"
#include "RuntimeFileChecks.h"
#include "ParticleFluidDesc.h"
#include "ParticleFluid.h"
#include "Collection.h"
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
Physics::Physics([Optional] ErrorCallback^ errorCallback, [Optional] bool checkRuntimeFiles)
{
	if (checkRuntimeFiles)
		RuntimeFileChecks::Check();

	Init();

	_allocator = new PxDefaultAllocator();
	_errorCallback = (errorCallback == nullptr ? gcnew DefaultErrorCallback() : errorCallback);

	_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_allocator, *_errorCallback->UnmanagedPointer, PxTolerancesScale(), true);

	if (_physics == NULL)
		throw gcnew Exception("Failed to create physics instance");

	PostInit();
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

void Physics::Init()
{
	if (_instantiated)
		throw gcnew PhysicsAlreadyInstantiatedException("The physics core object has already been instantiated. Check Physics.Instantiated before calling this ctor.");

	_scenes = gcnew List<Scene^>();
	_materials = gcnew List<Material^>();
	_rigidActors = gcnew List<RigidActor^>();
	_particleSystems = gcnew List<ParticleSystem^>();
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
		InternalMemoryStream* ms = Util::StreamToUnmanagedMemoryStream(stream);

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

#pragma region Particle System
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

#pragma region Particle Fluid
ParticleFluid^ Physics::CreateParticleFluid(ParticleFluidDesc^ desc)
{
	ThrowIfDescriptionIsNullOrInvalid(desc, "desc");

	PxParticleFluidDesc d = ParticleFluidDesc::ToUnmanaged(desc);

	PxParticleFluid* particleFluid = _physics->createParticleFluid(d);

	if (particleFluid == NULL)
		throw gcnew FailedToCreateObjectException("Failed to create particle fluid");

	return gcnew ParticleFluid(particleFluid, this);
}

array<ParticleFluid^>^ Physics::ParticleFluids::get()
{
	return ObjectTable::GetObjectsOfType<ParticleFluid^>();
}
#pragma endregion

#pragma region Deformable
Deformable^ Physics::CreateDeformable(DeformableDesc^ desc)
{
	ThrowIfDescriptionIsNullOrInvalid(desc, "desc");

	PxDeformableDesc desc_ = DeformableDesc::ToUnmanaged(desc);

	auto deformable_ = _physics->createDeformable(desc_);

	if (deformable_ == NULL)
		throw gcnew FailedToCreateObjectException("Failed to create deformable");

	auto deformable = gcnew Deformable(deformable_, desc->DeformableMesh, this);

	_deformables->Add(deformable);

	return deformable;
}

DeformableMesh^ Physics::CreateDeformableMesh(System::IO::Stream^ stream)
{
	ThrowIfNull(stream, "stream");
	if (!stream->CanWrite)
		throw gcnew ArgumentException("Cannot write to stream");

	int m = (int)stream->Length;

	stream->Position = 0;

	PxU8* streamCopy = new PxU8[m];
	array<Byte>^ buffer = gcnew array<Byte>(m);
	stream->Read(buffer, 0, m);
	Util::AsUnmanagedArray(buffer, (void*)streamCopy, m);

	InternalMemoryStream s;
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

Attachment^ Physics::CreateAttachment(Deformable^ deformable, Shape^ shape, array<int>^ vertexIndices, array<Vector3>^ positions, array<int>^ flags)
{
	ThrowIfNullOrDisposed(deformable, "deformable");
	//ThrowIfNullOrDisposed(shape, "shape");
	ThrowIfNull(vertexIndices, "vertexIndices");
	ThrowIfNull(positions, "positions");
	ThrowIfNull(flags, "flags");

	//if (vertexIndices->Length != positions->Length || positions->Length != flags->Length)
	//	throw gcnew ArgumentException("The array arguments must all be the same length");

	PxShape* s = GetPointerOrNull(shape);

	int n = vertexIndices->Length;

	// TODO: Return null?
	if (n == 0)
		return nullptr;

	//pin_ptr<int> vi = &vertexIndices[0];
	//pin_ptr<Vector3> p = &positions[0];
	//pin_ptr<int> f = &flags[0];

	PxU32* vi = new PxU32[vertexIndices->Length];
	Util::AsUnmanagedArray(vertexIndices, (void*)vi, vertexIndices->Length);

	PxVec3* p = new PxVec3[positions->Length];
	Util::AsUnmanagedArray(positions, (void*)p, positions->Length);

	PxU32* f = new PxU32[flags->Length];
	Util::AsUnmanagedArray(flags, (void*)f, flags->Length);

	auto attachment = _physics->createAttachment(*deformable->UnmanagedPointer, s, n, vi, p, f);

	return gcnew Attachment(attachment, this);
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

	_physics->releaseCollection(collection->UnmanagedPointer);
}

void Physics::AddCollection(Collection^ collection, Scene^ scene)
{
	ThrowIfNullOrDisposed(collection, "collection");
	ThrowIfNullOrDisposed(scene, "scene");

	_physics->addCollection(*collection->UnmanagedPointer, scene->UnmanagedPointer);
}
#pragma endregion

PxPhysics* Physics::UnmanagedPointer::get()
{
	return _physics;
}